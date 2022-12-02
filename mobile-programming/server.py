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
    url = Column(String(200), unique=True)
    num = Column(Integer, unique=False)

    def __init__(self, name=None, price=None, url=None, num=None):
        self.name = name
        self.price = price
        self.url = url
        self.num = num

    def __repr__(self):
        return f'<Drink {self.name!r}>'


# Base.metadata.drop_all(bind=engine)
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
    num = content[0]

    if db_session.query(Drink).filter_by(name=name).first() is None:
        u = Drink(name=name, price=price, url=url, num=num)
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
    price = content["price"]
    url = content["url"]

    if db_session.query(Drink).filter_by(name=name).first() is None:
        return jsonify(success=False)
    else:
        u = Drink(name=name, price=price, url=url, num=0)
        db_session.delete(u)
        db_session.commit()
        return jsonify(success=True)


if __name__ == "__main__":
    app.run(host='localhost', port=8888)

#카트에 넣기
@app.route("/cart", methods=['POST'])
def cart():
    content = request.get_json(silent=True)
    name = content["name"]
   
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
@app.route("/calculate", methods=['POST'])
def calculate():

    price = 0
    result = db_session.query(Drink).all()
    for i in result:
        price += i.num * i.price
    return jsonify(price)

#수 초기화
@app.route("/init", methods=['POST'])
def init():

    result = db_session.query(Drink).all()
    for i in result:
        i.num = 0
    return jsonify(success=True)