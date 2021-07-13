import re
import sys
import json
import time
import requests
from pymongo import MongoClient
from bs4 import BeautifulSoup
import cfg

pattern = cfg.pattern  # 支持正则表达式

if __name__ == "__main__":
    url_list = []
    if sys.argv[1] == "1":
        conn = MongoClient("127.0.0.1", 27017)
        db = conn.wx  # 连接wx数据库，没有则自动创建
        mongo_wx = db.weishenghuo  # 使用article集合，没有则自动创建

        with conn:
            urls = mongo_wx.find({}, {"content_url": 1,})
            urls = list(urls)
            for url in urls:
                url_list.append(url["content_url"])

    else:
        with open("data.json", "r") as fr:
            data = json.load(fr)
            for data_list in data:
                url_list.append(data_list["content_url"])

for url in url_list:
    res = ""
    try:
        # 以下except都是用来捕获当requests请求出现异常时，
        # 通过捕获然后等待网络情况的变化，以此来保护程序的不间断运行
        res = requests.get(url)
        content = res.content.decode()
        soup = BeautifulSoup(content, "html.parser")
        print(
            list(
                filter(
                    lambda x: re.search(pattern, x) is not None, soup.stripped_strings,
                )
            )
        )
    except requests.exceptions.ConnectionError:
        print("ConnectionError -- please wait 3 seconds")
        time.sleep(3)
    except requests.exceptions.ChunkedEncodingError:
        print("ChunkedEncodingError -- please wait 3 seconds")
        time.sleep(3)
    except:
        print("Unfortunitely -- An Unknow Error Happened, Please wait 3 seconds")
        time.sleep(3)
    # res = requests.get(url)

