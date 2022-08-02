# MongoDB와 Python 연결하기!

## pymongo와 MongoClient 설치

```bash
$ pip install pymongo
```
```bash
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

[MongoDB](https://account.mongodb.com/account/login)에 로그인

<br/>
<br/>

![img](mongodb.png)

Cluster0 옆에 있는 Connect 클릭 <br/>
-> Connect your application 클릭 <br/>
-> mongodb+srv://yun1211:password@cluster0.qypul.mongodb.net/<dbname>?retryWrites=true&w=majority과 같은 형태의 링크 복사<br/>
-> <password>를 자신의 비밀번호로 수정 & <dbname>을 사진의 Cluster0과 같은(대소문자 주의) 데이터베이스 이름으로 수정
-> 

