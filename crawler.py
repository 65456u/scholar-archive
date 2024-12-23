import logging
from datetime import datetime

import pandas as pd
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.ui import WebDriverWait

# Set up logging
logging.basicConfig(level = logging.INFO, format = '%(asctime)s - %(levelname)s - %(message)s')


def init_headless_driver():
    chrome_options = Options()
    chrome_options.add_argument("--headless")
    driver = webdriver.Chrome(options = chrome_options)
    return driver


class NewsFlashScraper:
    def __init__(self, url):
        self.url = url
        self.driver = init_headless_driver()

    def scrape_page(self):
        try:
            self.driver.get(self.url)

            data = {
                'title': [],
                'time': [],
                'content': [],
                'link': []
            }
            click_count = 0
            max_clicks = 1000  # 根据实际情况调整

            # 先下拉100次
            while click_count < max_clicks:
                try:
                    # 等待 "加载更多" 按钮可点击
                    load_more_button = WebDriverWait(self.driver, 10).until(
                        EC.element_to_be_clickable((By.CSS_SELECTOR, ".kr-loading-more-button.show"))
                    )
                    self.driver.execute_script("arguments[0].scrollIntoView(true);", load_more_button)

                    # 等待滚动完成
                    WebDriverWait(self.driver, 10).until(
                        EC.element_to_be_clickable((By.CSS_SELECTOR, ".kr-loading-more-button.show"))
                    )

                    self.driver.execute_script("arguments[0].click();", load_more_button)

                    # 等待新内容加载
                    WebDriverWait(self.driver, 10).until(
                        EC.presence_of_all_elements_located((By.CSS_SELECTOR, "div.newsflash-item"))
                    )

                    click_count += 1
                    logging.info(f"Handled {click_count} clicks.")

                except Exception as e:
                    logging.error(f"Error loading more news: {e}")
                    break

            # 开始读取和解析信息
            news_items = self.driver.find_elements(By.CSS_SELECTOR, "div.newsflash-item")
            for item in news_items:
                try:
                    title_element = item.find_element(By.CSS_SELECTOR, "a.item-title")
                    title = title_element.text
                    link = title_element.get_attribute('href')
                    time_element = item.find_element(By.CSS_SELECTOR, "div.item-related span.time")
                    news_time = time_element.text
                    content_element = item.find_element(By.CSS_SELECTOR, "div.item-desc span")
                    content = content_element.text
                    if news_time:
                        try:
                            news_time_parsed = datetime.strptime(news_time, "%Y-%m-%d %H:%M:%S")
                            if news_time_parsed < datetime(2023, 6, 1):
                                logging.info(f"Processed {len(data['title'])} news flashes from {self.url}")
                                return data
                        except ValueError:
                            continue
                    data['title'].append(title)
                    data['time'].append(news_time)
                    data['content'].append(content)
                    data['link'].append(link)
                    if len(data['title']) % 100 == 0:
                        logging.info(f"Processed {len(data['title'])} news flashes from {self.url}")
                        logging.info(f"Earliest news time: {news_time}")
                except Exception as e:
                    logging.error(f"Error processing news item: {e}")
                    continue

                click_count += 1
                logging.info(f"Handled {click_count} clicks.")

            logging.info(f"Processed {len(data['title'])} news flashes from {self.url}")

            return data

        except Exception as e:
            logging.error(f"Error scraping page: {e}")
            return {}

    def scrape(self):
        data = self.scrape_page()
        if not data:
            return pd.DataFrame()

        df = pd.DataFrame(data)
        return df


def main():
    urls = ["https://www.36kr.com/newsflashes/catalog/2"]  # Your list of URLs
    scraper = NewsFlashScraper(urls[0])
    df = scraper.scrape()
    df.to_pickle('news.pkl')


if __name__ == "__main__":
    main()
