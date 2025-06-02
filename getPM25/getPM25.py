import pandas as pd
import requests
import numpy as np
from datetime import datetime

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

df = pd.read_csv(filename)
print("📄 欄位名稱：", df.columns.tolist())

df['monitordate'] = pd.to_datetime(df['monitordate'], errors='coerce')

# 注意：這裡以「觀音」為例，如要改請修改下行
tainan_pm25 = df[(df['sitename'] == '觀音') & (df['itemname'] == 'PM2.5')]

if tainan_pm25.empty:
    print("❌ 資料中找不到該測站 PM2.5 測項，請稍後再試或改測站")
    exit()

latest_date = tainan_pm25['monitordate'].max()
latest_data = tainan_pm25[tainan_pm25['monitordate'] == latest_date]

# 取出24小時數值並算平均
cols = [f'monitorvalue{str(i).zfill(2)}' for i in range(24)]
values = latest_data[cols].astype(float).values.flatten()
mean_value = np.nanmean(values)

year = latest_date.year
month = latest_date.month
day = latest_date.day

output_file = "./getPM25/PM25_Tainan.csv"
output_df = pd.DataFrame([[year, month, day, mean_value]])
output_df.to_csv(output_file, index=False, header=False, encoding="utf-8-sig")
print(f"✅ 已儲存（只保留數值）：{output_file}")