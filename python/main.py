import re
import requests
from bs4 import BeautifulSoup

if __name__ == "__main__":

    pattern = "显示器"  # 支持正则表达式
    # url = "http://mp.weixin.qq.com/s?__biz=MzA4NTcxNjQ2Nw==&amp;mid=2650093804&amp;idx=1&amp;sn=1e53280973d78b80bf29ec0e73f55678&amp;chksm=87d22470b0a5ad66c422917638bef4eca569d3948540f24afc5ec3aed6aa94e9dae892d6821e&amp;scene=27#wechat_redirect"

    res = requests.get(url)
    content = res.content.decode()
    soup = BeautifulSoup(content, "html.parser")
    print(
        list(filter(lambda x: re.search(pattern, x) is not None, soup.stripped_strings))
    )
