import multiprocessing

import pandas as pd
import requests
from bs4 import BeautifulSoup
from requests.exceptions import RequestException
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as ec
from selenium.webdriver.support.ui import WebDriverWait
from tqdm import tqdm


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


# 合并数据
def combine_data(saved_files, authors):
    all_df = pd.DataFrame()
    for name, path in zip(authors['name'], saved_files):
        df = pd.read_pickle(path)
        # 创建author列，把df的author列全部设为name
        df['author'] = name
        df['author_id'] = path.split('.')[0]
        all_df = pd.concat([all_df, df])
    df = all_df.sort_values(by = 'link')
    df.to_pickle('all.pkl')
    return df


# 获取内容
def get_content(meta):
    results = []
    for index, row in tqdm(meta.iterrows(), total = meta.shape[0]):
        try:
            with requests.get(row['link']) as response:
                if response.ok:
                    soup = BeautifulSoup(response.text, 'html.parser')
                    article_content_div = soup.find('div', class_ = 'article__content')
                    if article_content_div:
                        # 初始化Markdown格式的文本
                        markdown_text = ''

                        # 提取所有段落标签
                        paragraphs = article_content_div.find_all('p')
                        for p in paragraphs:
                            # 检查段落中是否包含img标签
                            img = p.find('img')
                            if img:
                                # 提取图片的Markdown格式链接
                                img_src = img.get('data-src')
                                img_alt = img.get('alt', '图片')  # 使用alt属性，如果没有则默认为'图片'
                                markdown_text += f"![{img_alt}]({img_src})\n\n"
                            # 将段落文本添加到Markdown文本中
                            markdown_text += p.get_text(strip = True) + "\n\n"
                        results.append(markdown_text)
                    else:
                        results.append("")
                else:
                    results.append("")
                    print(f"请求失败，状态码：{response.status_code}")
        except RequestException as e:
            results.append("")
            print(f"请求链接 {row['link']} 时发生错误：{e}")

    # 在df中增加content列，内容是results
    meta['content'] = results
    meta = meta[meta['content'] != '']
    meta.reset_index(drop = True, inplace = True)
    meta.to_pickle('all_content.pkl')
    return meta


def main():
    urls = [
        "https://www.jiqizhixin.com/users/0db0310e-6f96-46bc-9151-a50b36421a76",
        "https://www.jiqizhixin.com/users/294c393b-25f7-45b0-bec6-33e3bd344e61",
        "https://www.jiqizhixin.com/users/f2e8c882-a163-443d-8b0c-e9f08ce5d6cb"
    ]
    authors = {
        'name': [
            '机器之心',
            '机器之能',
            'ScienceAI'
        ]
    }

    # Step 1: 爬取数据
    saved_files = process_urls(urls)

    # Step 2: 合并数据
    meta_df = combine_data(saved_files, authors)

    # Step 3: 获取内容
    final_df = get_content(meta_df)

    print(final_df)


if __name__ == "__main__":
    main()
