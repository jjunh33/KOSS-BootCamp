# MongoDB와 Python 연결하기!

## pymongo와 MongoClient 설치

```bash
$ pip install pymongo
$ pip install dnspython
```

## pymongo 실습
```python
from pymongo import MongoClient

client = MongoClient("mongodb+srv://yun1211:yunbird1211@cluster0.qypul.mongodb.net/Cluster0?retryWrites=true&w=majority")

db = client['Sensor']

for d, cnt in zip(db['sensors'].find(), range(10)):
    print(d['pm1'], d['pm10'])
```
DB에 데이터 넣는 실습을 안해보신 분은 우선 제것을 사용하여 실습하셔도 좋습니다!
<br/>

[MongoDB](https://account.mongodb.com/account/login)에 로그인

<br/>
<br/>

### MongoClient url 찾기!

![img](mongodb.png)

Cluster0 옆에 있는 Connect 클릭 <br/>
-> Connect your application 클릭 <br/>
-> mongodb+srv://yun1211:\<password\>@cluster0.qypul.mongodb.net/\<dbname\>?retryWrites=true&w=majority과 같은 형태의 링크 복사<br/>
-> \<password>를 자신의 비밀번호로 수정 & \<dbname\>을 사진의 Cluster0과 같은(대소문자 주의) 데이터베이스 이름으로 수정<br/>
```python
client = MongoClient("<여기에 넣으세요!>")
```
### Database 이름과 collections 이름 찾기!

![img](database.png)

Connect의 왼쪽에 있는 Cluster0 클릭 <br/>
-> Collections 클릭 <br/>
-> 사진에 보이는 Sensor, test와 같은 것들이 데이터 베이스 이름
```python
db = client['<여기에 넣으세요!>']
```
-> 사진에 보이는 BME280, bme280, sensors와 같은 것들이 collections의 이름
```python
for d, cnt in zip(db['<여기에 넣으세요!>'].find(), range(10)):
```
