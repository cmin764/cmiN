#! /usr/bin/env python

from functools import wraps
from pycnic.core import WSGI, Handler
from pycnic.errors import HTTP_401, HTTP_400
# Import our SQLAlchemy stuff
from models import User, UserSession, Session, Base, engine

db = Session()

ENCODING = "utf-8"
HOST = "0.0.0.0"
PORT = 8080

def get_user(request):
    """ Lookup a user session or return None if one doesn't exist """

    sess_id = request.cookies.get("session_id")
    if not sess_id:
        return None
    sess_id = sess_id.decode(ENCODING)
    sess = db.query(UserSession).filter(
        UserSession.session_id == sess_id).first()
    #print(sess_id, sess)
    if not sess:
        return None
    if not sess.user:
        return None
    return { "username": sess.user.username }

def requires_login():
    """ Wrapper for methods that require login """

    def wrapper(f):
        @wraps(f)
        def wrapped(*args, **kwargs):
            if not get_user(args[0].request):
                raise HTTP_401("I can't let you do that")
            return f(*args, **kwargs)
        return wrapped
    return wrapper


# Mai implementezi si alte clase ca asta, ca sa faci si alte endpointuri
class Home(Handler):
    """ Handler for a message with the user's name """

    @requires_login()
    def get(self, number="0"):
        user = get_user(self.request)
        return { "message":"Hello, %s .. you have provided %s" % (user.get("username"), number) }

    @requires_login()
    def post(self):
        return self.get()


class Login(Handler):
    """ Create a session for a user """

    def post(self):

        username = self.request.data.get("username")
        password = self.request.data.get("password")

        if not username or not password:
            raise HTTP_400("Please specify username and password")

        # See if a user exists with those params
        user = db.query(User).filter(
            User.username==username, 
            User.password==password).first()
        if not user:
            raise HTTP_401("Invalid username or password")

        # Create a new session 
        sess = UserSession(
            user_id=user.id)
        db.add(sess)
        db.commit()
        sess_id = sess.session_id.encode(ENCODING)
        self.response.set_cookie("session_id", sess_id) 
        return { "message":"Logged in", "session_id": sess_id }

class Logout(Handler):
    """ Clears a user's session """

    def post(self):

        sess_id = self.request.cookies.get("session_id")
        if sess_id:
            sess_id = sess_id.decode(ENCODING)
            # query to user sessions table
            sess = db.query(UserSession).filter(
                UserSession.session_id==sess_id).first()
            if sess:
                db.delete(sess)
                db.commit()
            self.response.delete_cookie("session_id")
            return { "message":"logged out" } 
        return { "message":"Not logged in" }


RESPONSE_HEADERS = {
    "Access-Control-Allow-Origin": "*",
    "Access-Control-Allow-Headers": ("Origin, X-Requested-With, Content-Type, "
                                     "Accept"),
    "Access-Control-Allow-Methods": "PUT, POST, GET, DELETE, OPTIONS",
}

class app(WSGI):
    debug = True
    headers = RESPONSE_HEADERS.items()

    home = Home()

    routes = [ 
        # Aici adaugi endpointurile tale :).
        ('/home', home),
        ('/home/(\d+)', home),
        ('/login', Login()),
        ('/logout', Logout())
    ]


if __name__ == "__main__":
    from wsgiref.simple_server import make_server
    try:
        print("Serving on {}:{}...".format(HOST, PORT))
        make_server(HOST, PORT, app).serve_forever()
    except KeyboardInterrupt:
        pass
    print("Done")
