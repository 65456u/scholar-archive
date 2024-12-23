import pandas as pd
import requests
from bs4 import BeautifulSoup
from requests.exceptions import RequestException
from tqdm import tqdm

meta = pd.read_pickle('all.pkl')

results = []
for index, row in tqdm(meta.iterrows()):
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
                    print("没有找到文章内容。")
            else:
                print(f"请求失败，状态码：{response.status_code}")
    except RequestException as e:
        print(f"请求链接 {row['link']} 时发生错误：{e}")

# 在df中增加content列，内容是results
meta['content'] = results
meta = meta[meta['content'] != '']
meta.reset_index(drop = True, inplace = True)
meta.to_pickle('all_content.pkl')
