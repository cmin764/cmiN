#! /usr/bin/env python

import os
from flask import Flask, request

app = Flask(__name__)


def read(name):
    name = os.path.abspath(name)
    with open(name, "r") as stream:
        return stream.read()


@app.route('/')
def index():
    return read("index.html")

@app.route("/pagina")
def pagina():
    name = request.args.get("name")
    return read(name)
