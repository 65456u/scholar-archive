import multiprocessing

import pandas as pd
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as ec
from selenium.webdriver.support.ui import WebDriverWait


# 初始化无头浏览器选项
def init_headless_driver():
    chrome_options = Options()
    chrome_options.add_argument("--headless")  # 启用无头模式
    driver = webdriver.Chrome(options = chrome_options)
    return driver


# 定义一个工作函数，用于爬取单个页面并保存到独立的.pkl文件
def scrape_page(url):
    driver = init_headless_driver()
    try:
        driver.get(url)
        # 等待页面加载完成，然后点击文章按钮
        WebDriverWait(driver, 10).until(ec.element_to_be_clickable((By.CSS_SELECTOR, "a.js-u-tab"))).click()

        # 循环加载更多文章
        data = {
            'title': [],
            'category': [],
            'link': []
        }
        while True:
            driver.execute_script("window.scrollTo(0, document.body.scrollHeight);")
            try:
                WebDriverWait(driver, 10).until(
                    ec.element_to_be_clickable((By.CSS_SELECTOR, ".u-loadmore__btn"))).click()
            except:
                break

            WebDriverWait(driver, 10).until(
                ec.presence_of_all_elements_located((By.CSS_SELECTOR, "div.user-show__article")))
            articles = driver.find_elements(By.CSS_SELECTOR, "div.user-show__article")
            for article in articles:
                title_element = article.find_element(By.CSS_SELECTOR, "a.article-item__title")
                title = title_element.text
                link = title_element.get_attribute('href')
                category_element = article.find_element(By.CSS_SELECTOR, "a.category__link")
                category = category_element.text
                data['title'].append(title)
                data['category'].append(category)
                data['link'].append(link)
                if len(data['title']) % 100 == 0:
                    print(f"Processed {len(data['title'])} articles from {url}")
        driver.quit()
        # 将数据保存到独立的.pkl文件
        post_id = url.split('/')[-1]
        filename = f"{post_id}.pkl"
        df = pd.DataFrame(data)
        df.drop_duplicates(subset = ['link'], keep = 'first').to_pickle(filename)
        return filename
    except Exception as e:
        print(f"Error processing {url}: {e}")
        driver.quit()
        return None


# 定义一个函数来处理多个URL
def process_urls(urls):
    pool = multiprocessing.Pool(processes = len(urls))
    results = pool.starmap(scrape_page, [(url,) for url in urls])
    pool.close()
    pool.join()
    return results


def main():
    urls = [
        "https://www.jiqizhixin.com/users/0db0310e-6f96-46bc-9151-a50b36421a76",
        "https://www.jiqizhixin.com/users/294c393b-25f7-45b0-bec6-33e3bd344e61",
        "https://www.jiqizhixin.com/users/f2e8c882-a163-443d-8b0c-e9f08ce5d6cb"
    ]
    saved_files = process_urls(urls)
    for file in saved_files:
        if file:
            print(f"Data saved to {file}")


if __name__ == "__main__":
    main()
