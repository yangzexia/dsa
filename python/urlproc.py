import re
import json
import time
import requests
from pymongo import MongoClient
from bs4 import BeautifulSoup

conn = MongoClient("127.0.0.1", 27017)
db = conn.wx  # 连接wx数据库，没有则自动创建
mongo_wx = db.article  # 使用article集合，没有则自动创建


with conn:

    urls = mongo_wx.find({}, {"content_url": 1,})

    urls = list(urls)
    url = []
    for url_list in urls:
        url.append(url_list["content_url"])

pattern = "显示器"  # 支持正则表达式
url = "https://mp.weixin.qq.com/s?__biz=MzA4NTcxNjQ2Nw==&amp;mid=2650095082&amp;idx=1&amp;sn=95dbe0b48ab001d8194e363f9ff8887c&amp;chksm=87d22176b0a5a860bf753a1f2c6d37d61bbaf9795f9612a6393a9b67d5c568d6064f69ce4c5d&amp;scene=27#wechat_redirect"

res = requests.get(url)
content = res.content.decode()
soup = BeautifulSoup(content, "html.parser")
print(
    list(filter(lambda x: re.search(pattern, x) is not None, soup.stripped_strings))
)


if __name__ == '__main__':
    