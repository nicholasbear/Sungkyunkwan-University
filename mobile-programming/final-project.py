from enum import unique
from unicodedata import category
from sqlalchemy import create_engine
from sqlalchemy.orm import scoped_session, sessionmaker
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Column, Integer, String

USER = "postgres"
PW = "woojin1206*"
URL = "final-project.c6j3ssgsmtcd.ap-northeast-2.rds.amazonaws.com"
PORT = "5432"
DB = "postgres"

engine = create_engine("postgresql://{}:{}@{}:{}/{}".format(USER, PW, URL,PORT, DB))
db_session = scoped_session(sessionmaker(autocommit=False, autoflush=False, bind=engine))

Base = declarative_base()
Base.query = db_session.query_property()

class Drink(Base):
    __tablename__ = 'drinks'
    id = Column(Integer, primary_key=True)
    name = Column(String(50), unique=True)
    price = Column(Integer, unique=False)
    url = Column(String(300), unique=True)
    category = Column(String(10), unique=False)
    num = Column(Integer, unique=False)

    def __init__(self, name=None, price=None, url=None, category=None, num=None):
        self.name = name
        self.price = price
        self.url = url
        self.category = category
        self.num = num

    def get_data(self):
        return { c.name: getattr(self, c.name) for c in self.__table__.columns }


#Base.metadata.drop_all(bind=engine)
Base.metadata.create_all(bind=engine)

from flask import Flask
from flask import request
from flask import jsonify
from werkzeug.serving import WSGIRequestHandler
import json

import json
WSGIRequestHandler.protocol_version = "HTTP/1.1"

app = Flask(__name__)

#리스트에 술 더하기
@app.route("/adddrink", methods=['POST'])
def add_drink():
    content = request.get_json(silent=True)
    name = content["name"]
    price = content["price"]
    url = content["url"]
    category = content["category"]
    num = content["num"]

    if db_session.query(Drink).filter_by(name=name).first() is None:
        u = Drink(name=name, price=price, url=url, category=category, num=num)
        db_session.add(u)
        db_session.commit()
        return jsonify(success=True)
    else:
        return jsonify(success=False)

#리스트에 술 뺴기
@app.route("/removedrink", methods=['POST'])
def remove_drink():
    content = request.get_json(silent=True)
    name = content["name"]

    if db_session.query(Drink).filter_by(name=name).first() is None:
        return jsonify(success=False)
    else:
        u = db_session.query(Drink).filter_by(name=name).first()
        db_session.delete(u)
        db_session.commit()
        return jsonify(success=True)


if __name__ == "__main__":
    app.run(host='localhost', port=8888)

#카트에 넣기
@app.route("/addcart", methods=['POST'])
def addcart():
    content = request.get_json(silent=True)
    name = content["name"]
   
    if db_session.query(Drink).filter_by(name=name).first().num != 0 :
        return jsonify(success=False)
    db_session.query(Drink).filter_by(name=name).first().num = 1
    return jsonify(success=True)

#카트에서 수량변경
@app.route("/plus", methods=['POST'])
def plus():
    content = request.get_json(silent=True)
    name = content["name"]
   
    db_session.query(Drink).filter_by(name=name).first().num += 1

    return jsonify(success=True)

@app.route("/minus", methods=['POST'])
def minus():
    content = request.get_json(silent=True)
    name = content["name"]
   
    db_session.query(Drink).filter_by(name=name).first().num -= 1

    return jsonify(success=True)

#카트가격 측정
@app.route("/calculate", methods=['GET'])
def calculate():

    price = 0
    list = db_session.query(Drink).all()
    length = len(list)
    num = 0
    while num < length:
        price += (list[num].price * list[num].num)
        num += 1
    return jsonify(success=price)

#수 초기화
@app.route("/init", methods=['GET'])
def init():

    list = db_session.query(Drink).all()
    length = len(list)
    num = 0
    while num < length:
        list[num].num = 0
        num += 1
    return jsonify(success=True)

#리스트 불러오기
@app.route("/list", methods=['GET'])
def list():
    result = []
    list = db_session.query(Drink).all()
    length = len(list)
    if length == 0:
        return jsonify(success=True)
    num = 0
    while num < length:
        temp = dict()
        temp["name"] = list[num].name
        temp["price"] = list[num].price
        temp["url"] = list[num].url
        temp["category"] = list[num].category
        temp["num"] = list[num].num
        result.append(temp)
        num += 1

    return jsonify(result)

#카트 리스트 불러오기
@app.route("/cart", methods=['GET'])
def cart():
    result = []
    list = db_session.query(Drink).all()
    length = len(list)
    num = 0
    while num < length:
        if list[num].num != 0:
            temp = dict()
            temp["name"] = list[num].name
            temp["price"] = list[num].price
            temp["url"] = list[num].url
            temp["category"] = list[num].category
            temp["num"] = list[num].num
            result.append(temp)
        num += 1

    return jsonify(result)


#test
@app.route("/test", methods=['POST'])
def test():
    content = request.get_json(silent=True)
    name = content["name"]
    if name == "1":
        return jsonify(success=True)
    else:
        return jsonify(success=False)
