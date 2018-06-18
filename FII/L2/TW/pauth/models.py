#! /usr/bin/env python

from sqlalchemy import create_engine, Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship, backref
import hashlib
import time

engine = create_engine('sqlite:///pauth.db', echo=True)
Base = declarative_base()
Session = sessionmaker(bind=engine)

def get_new_session_id():
    """ Generates a sha1 session id """

    to_hash = "%s_SECRET"%(time.time())
    return hashlib.sha1(to_hash.encode('utf-8')).hexdigest()

class UserSession(Base):

    __tablename__ = "user_sessions"
    id = Column(Integer, primary_key=True)
    session_id = Column(String, 
        default=get_new_session_id, onupdate=get_new_session_id)
    user_id = Column(Integer, ForeignKey('users.id'))
    user = relationship("User", backref=backref("sessions"), order_by=id)

class User(Base):
    __tablename__ = "users"
    id = Column(Integer, primary_key=True)
    username = Column(String)
    password = Column(String)


if __name__ == "__main__":

    db = Session()

    print("DB: Creating users table in memory...")    
    Base.metadata.create_all(engine)

    print("DB: Adding users...")
    users = []
    with open("users.txt") as stream:
        for line in stream.read().strip().splitlines():
            if line.startswith("#"):
                continue
            items = line.split(":")
            users.append(items)
    db.add_all([
        User(username=usr, password=pwd)
        for usr, pwd in users
    ])
    db.commit()
