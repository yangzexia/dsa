import sys
import requests
import json
import time
from pymongo import MongoClient


url = "http://mp.weixin.qq.com/mp/profile_ext"

# Mongo配置
conn = MongoClient("127.0.0.1", 27017)
db = conn.wx  # 连接wx数据库，没有则自动创建
mongo_wx = db.article  # 使用article集合，没有则自动创建


data = []

def get_wx_article(argv, cfg, index=0, count=10):
    offset = (index + 1) * count
    params = {
        "__biz": cfg.biz,
        "uin": cfg.uin,
        "key": cfg.key,
        "offset": offset,
        "count": count,
        "action": "getmsg",
        "f": "json",
    }

    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.131 Safari/537.36"
    }

    response = requests.get(url=url, params=params, headers=headers)
    resp_json = response.json()
    if resp_json.get("errmsg") == "ok":
        resp_json = response.json()
        # 是否还有分页数据， 用于判断return的值
        can_msg_continue = resp_json["can_msg_continue"]
        # 当前分页文章数
        msg_count = resp_json["msg_count"]
        general_msg_list = json.loads(resp_json["general_msg_list"])
        print(general_msg_list)
        print("\n\n\n\n\n\n\n\n\n")
        list = general_msg_list.get("list")
        print(list)
        print("\n\n\n\n\n\n\n\n\n")
        print(list, "**************\n")
        for i in list:
            app_msg_ext_info = i["app_msg_ext_info"]
            # 标题
            title = app_msg_ext_info["title"]
            # 文章地址
            content_url = app_msg_ext_info["content_url"]
            # 封面图
            cover = app_msg_ext_info["cover"]

            # 发布时间
            datetime = i["comm_msg_info"]["datetime"]
            datetime = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(datetime))
            # 使用数据库
            if argv[1] == '1':
                mongo_wx.insert(
                    {
                        "title": title,
                        "content_url": content_url,
                        "cover": cover,
                        "datetime": datetime,
                    }
                )
            # 使用json文件
            else:
                data.append({
                        "title": title,
                        "content_url": content_url,
                        "cover": cover,
                        "datetime": datetime,
                    
                })
        if can_msg_continue == 1:
            return True
        return False
    else:
        print("获取文章异常...")
        return False


if __name__ == "__main__":

    import cfg

    # biz = 'MzA4NTcxNjQ2Nw=='
    # uin = 'MjM2NzI1ODE0MQ=='
    # key = '6eae84a1021658c4295f9d3e63fb76eae78da3edb5e5693235c8e89c0574774ce91301b533fb17f02fc214a8b9a786eae7049c287e545bd2773b7a5195352616689531f01c13fcde20c0ef636eba5ade138bb0c66745341a8cb795d22c8192b9455dca871029ddbcb449f68e7d56e32103d81a66860935e89026b7dddc3c0f5b'
    index = 0
    while 1:
        print(f"开始抓取公众号第{index + 1} 页文章.")
        flag = get_wx_article(sys.argv, cfg, index=index)
        # 防止和谐，暂停8秒

        if sys.argv[1] != 1:
            with open('data.json', 'w') as fw:
                json.dump(data,fw)
        time.sleep(8)
        index += 1
        if not flag:
            print("公众号文章已全部抓取完毕，退出程序.")
            break

        print(f"..........准备抓取公众号第{index + 1} 页文章.")

