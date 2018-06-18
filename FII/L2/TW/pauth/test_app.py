#! /usr/bin/env python

import requests
import urlparse

import app

sess = requests.Session()
usr, pwd = "sketa", "fra!3r"

url = "http://{}:{}".format(app.HOST, app.PORT)
home, login, logout = map(lambda arg: urlparse.urljoin(url, arg + "/"),
                          ["home", "login", "logout"])

resp = sess.get(home)
print("not auth", resp.status_code, resp.reason, resp.json())    # da fail neautentificat

# Acum ne autentificam
resp = sess.post(login, json={"username": usr, "password": pwd})
print("make auth", resp.status_code, resp.reason, resp.json())

# Si verificam iar home-ul
resp = sess.get(home)
print("with auth", resp.status_code, resp.reason, resp.json())    # trebuie sa fie ok, pt. ca e autentificat
resp = sess.get(urlparse.urljoin(home, "23"))
print("with auth", resp.status_code, resp.reason, resp.json())    # trebuie sa fie ok, pt. ca e autentificat

# Facem logout
resp = sess.post(logout)
print("unauth", resp.status_code, resp.reason, resp.json())


# Acum home-ul ar trebui sa crape din nou
resp = sess.get(home)
print("no auth again", resp.status_code, resp.reason, resp.json())    # nu mai e autentificat
