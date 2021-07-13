import re
import requests
from bs4 import BeautifulSoup

if __name__ == "__main__":
    pattern = "显示器"  # 支持正则表达式
    url = "https://mp.weixin.qq.com/s?__biz=MzA4NTcxNjQ2Nw==&amp;mid=2650095082&amp;idx=1&amp;sn=95dbe0b48ab001d8194e363f9ff8887c&amp;chksm=87d22176b0a5a860bf753a1f2c6d37d61bbaf9795f9612a6393a9b67d5c568d6064f69ce4c5d&amp;scene=27#wechat_redirect"

    res = requests.get(url)
    content = res.content.decode()
    soup = BeautifulSoup(content, "html.parser")
    print(
        list(filter(lambda x: re.search(pattern, x) is not None, soup.stripped_strings))
    )
