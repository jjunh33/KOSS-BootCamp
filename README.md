# MongoDB와 Python 연결하기!

## pymongo와 MongoClient 설치

```bash
$ pip install pymongo
```
```bash
$ pip install dnspython
```

## pymongo 실습
[MongoDB](https://account.mongodb.com/account/login)에 로그인
<br/>
<br/>
![img](mongodb.png)

Cluster0 옆에 있는 Connect 클릭 
-> Connect your application 클릭 
-> mongodb+srv://yun1211:<span style="color=red">password</span>@cluster0.qypul.mongodb.net/<span style="color=red">\<dbname\></span>?retryWrites=true&w=majority과 같은 형태의 링크 복사
-> <password>를 자신의 비밀번호로 수정 & 


```python
from pymongo import MongoClient
```
