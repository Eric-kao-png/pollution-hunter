import pandas as pd
import requests
from datetime import datetime

# 你的 API 金鑰
api_key = "15f949b6-9701-4b1f-a6f9-4478777a9476"
url = f"https://data.moenv.gov.tw/api/v2/AQX_P_547?format=csv&api_key={api_key}"
filename = "./getPM25/AQX_P_547.csv"

print("📡 正在下載整包空氣品質資料...")
response = requests.get(url, verify=False)
if response.status_code == 200:
    with open(filename, "wb") as f:
        f.write(response.content)
    print(f"✅ 成功下載：{filename}")
else:
    print(f"❌ 錯誤，狀態碼：{response.status_code}")
    print(response.text)
    exit()

# 讀取資料
df = pd.read_csv(filename)
print("📄 欄位名稱：", df.columns.tolist())

# 處理日期格式
df['monitordate'] = pd.to_datetime(df['monitordate'], errors='coerce')

# 篩選臺南 + PM2.5 的所有資料
tainan_pm25 = df[(df['sitename'] == '觀音') & (df['itemname'] == 'PM2.5')]

if tainan_pm25.empty:
    print("❌ 資料中找不到臺南 PM2.5 測項，請稍後再試或改測站")
    exit()

# 找出最接近今天的那一筆日期
latest_date = tainan_pm25['monitordate'].max()
latest_str = latest_date.strftime('%Y/%m/%d')
print(f"📆 找到最近有資料的日期：{latest_str}")

# 再篩選這一天的資料
df_result = tainan_pm25[tainan_pm25['monitordate'] == latest_date]

# 儲存
output_file = f"./getPM25/PM25_Tainan_{latest_str.replace('/', '-')}.csv"
df_result.to_csv(output_file, index=False, encoding="utf-8-sig")
print(f"✅ 已儲存：{output_file}")


