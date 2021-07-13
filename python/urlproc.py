import json
import time
from pymongo import MongoClient

conn = MongoClient("127.0.0.1", 27017)
db = conn.wx  # 连接wx数据库，没有则自动创建
mongo_wx = db.article  # 使用article集合，没有则自动创建


with conn:

    urls = mongo_wx.find({}, {"content_url": 1,})

    urls = list(urls)
    url = []
    for url_list in urls:
        url.append(url_list["content_url"])

print(url)
