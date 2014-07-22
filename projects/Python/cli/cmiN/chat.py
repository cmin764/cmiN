#! /usr/bin/env python
## Simple Secure Chat
## 14.09.2011 cmiN
"""
This is a simple CLI low level non blocking pythonic chat server and client (v1.0).
In server mode accepts MAXC clients simultaneously and waits for reply.
As client it works similar, but it uses a 'heartbeat' and a 'watcher' (see the classes below).
Non standard modules: PyCrypto (https://www.dlitz.net/software/pycrypto/).
Known bugs: in client mode if Ctrl+C is pressed it will make server crash somehow
and the connection will remain open. I think timeout is changed automatically to None.

Contact: cmin764@gmail/yahoo.com
"""


import time                     # heartbeat + private key seed
import sys                      # some miscellaneous
from socket import *            # interprocess comunication
from threading import Thread    # multi client async behavior
from hashlib import md5         # private key from time hash
try:
    from Crypto.Cipher import AES       # symmetric encryption
    from Crypto.PublicKey import RSA    # asymmetric key exchange
except ImportError as msg:
    sys.stdout.write("[x] Error: {0}.".format(msg))
    exit()


TOUT = 5            # socket timeout in seconds
PERC = 0.9          # waiting time percentage of TOUT as a pulse
FILE = None         # you can replace this by a file name
MAXC = 512          # max clients
MAXL = 1024         # max transmitted data
BUFF = 128          # limit data per send/recv
TERM = "\r\n"       # data terminator
BITS = 1024         # asymetric key size; smaller is faster but less secure (min 1024)
NULL = '\x00'       # padding byte
NAME = "guest"      # nickname initializer
PORT = 51337
HOST = gethostbyname(gethostname())


class Logger:
    """
    Simple logging class.
    Used for writing to both stdout and file.
    """

    def __init__(self, fname):
        self.status = False    # some kind of lock/semaphore
        if fname:
            self.fobj = open(fname, "a")
        else:
            self.fobj = fname

    def write(self, data):
        while self.status:
            pass
        self.status = True    # lock and load :)
        sys.stdout.write(data + '\n')
        sys.stdout.flush()
        if self.fobj:
            self.fobj.write(data + '\n')
            self.fobj.flush()
        self.status = False

    def close(self):
        if self.fobj:
            self.fobj.close()


def write(param, data):
    """Bandwidth-friendly and no data loss."""
    data = data[:MAXL]    # limit data
    if type(param) is list:
        sock = param[0]
        while param[2]:    # while is busy
            pass
        param[2] = True    # edit globally by reference
        if param[4]:
            data = param[4].encrypt(data + NULL * (16 - len(data) % 16))    # encrypt it
    else:
        sock = param
    data += TERM    # add the terminator
    csize = 0
    dsize = len(data)
    while csize < dsize:    # split data in pieces
        chunk = data[csize:(csize + BUFF)]
        rem = len(chunk) - sock.send(chunk)    # and send it as chunks
        while rem:    # if something remains
            rem = rem - sock.send(chunk[-rem:])
        csize += BUFF    # update the offset
    if type(param) is list:
        param[2] = False    # another lock


def read(param, data):
    """Same shit like write."""
    if type(param) is list:
        sock = param[0]
    else:
        sock = param
    ind = data.find(TERM)    # set the index
    while ind == -1:
        data += sock.recv(BUFF)
        ind = data.find(TERM)
    first = data[:ind]
    rem = data[(ind + len(TERM)):]
    if type(param) is list and param[4]:
        first = param[4].decrypt(first).strip(NULL)
    return (first, rem)


class Listener(Thread):
    """
    Every client is listened by a parallel thread.
    When a message is received it's immediately processed.
    Even the user is afk the client itself sends an 'update'.
    """

    def __init__(self, ip):
        Thread.__init__(self)
        self.ip = ip
        self.detail = clients[ip]    # [sock, nick, busy, [ignore], encryption]
        self.to = ip    # who receives messages from this client (self by default)

    def run(self):
        """Process all commands received from a client until an exception."""
        data = str()    # a buffer for each client
        try:    # key exchange
            write(self.detail, full.publickey().exportKey())    # send public key as string encoded in base64 (default)
            (line, data) = read(self.detail, data)    # receive client's encrypted symmetric key
            key = full.decrypt(line)    # get the hexdigest hash
            if len(key) == 16:
                sym = AES.new(key)    # with this we encrypt/decrypt sent/received data
                self.detail[4] = sym    # store the object in client
                write(self.detail, "Hello " + self.detail[1] + ", type /help to get all available commands.\n")
                while True:
                    (line, data) = read(self.detail, data)
                    if line[0] == '/':
                        line = line[1:].split()
                        if not line:
                            write(self.detail, "Invalid command.\n")
                            continue
                        if line[0] == "help":
                            write(self.detail, "\n".join(["/quit -> shutdown", "/mass -> to all", "/list -> see who's online",
                                                          "/nick name -> change id", "/to nick -> to someone (default self)",
                                                          "/block nick -> ignore", "/unblock nick -> accept"]) + '\n')
                        elif line[0] == "quit":
                            break
                        elif line[0] == "update":
                            write(self.detail, "/update")
                        elif line[0] == "mass":
                            if self.to:
                                self.to = None
                                write(self.detail, "Now talking to all.\n")
                            else:
                                write(self.detail, "Already talking to all.\n")
                        elif line[0] == "list":
                            write(self.detail, "\n".join([cl[1][1] for cl in clients.items() if clients.has_key(cl[0])]) + '\n')
                        elif line[0] == "to":
                            if len(line) == 2:
                                ok = False
                                for cl in clients.items():
                                    if clients.has_key(cl[0]) and cl[1][1] == line[1]:
                                        ok = True
                                        if self.to == cl[0]:
                                            write(self.detail, "Already talking to {0}.\n".format(line[1]))
                                        else:
                                            self.to = cl[0]
                                            write(self.detail, "Now talking to {0}.\n".format(line[1]))
                                        break
                                if not ok:
                                    write(self.detail, "Wrong user.\n")
                            else:
                                write(self.detail, "Invalid command.\n")
                        elif line[0] == "nick":
                            if len(line) == 2:
                                ok = True
                                for cl in clients.items():
                                    if clients.has_key(cl[0]) and cl[1][1] == line[1]:
                                        ok = False
                                        break
                                if ok:
                                    self.detail[1] = line[1]
                                    write(self.detail, "You are now {0}.\n".format(line[1]))
                                else:
                                    write(self.detail, "Already in use.\n")
                            else:
                                write(self.detail, "Invalid command.\n")
                        elif line[0] == "block":
                            if len(line) == 2:
                                ok = False
                                for cl in clients.items():
                                    if clients.has_key(cl[0]) and cl[1][1] == line[1]:
                                        ok = True
                                        if cl[0] in self.detail[3]:
                                            write(self.detail, "Already blocked.\n")
                                        else:
                                            self.detail[3].add(cl[0])
                                            write(self.detail, "Added to ignore list.\n")
                                        break
                                if not ok:
                                    write(self.detail, "Wrong user.\n")
                            else:
                                write(self.detail, "Invalid command.\n")
                        elif line[0] == "unblock":
                            if len(line) == 2:
                                ok = False
                                for cl in clients.items():
                                    if clients.has_key(cl[0]) and cl[1][1] == line[1]:
                                        ok = True
                                        if cl[0] in self.detail[3]:
                                            self.detail[3].remove(cl[0])
                                            write(self.detail, "Removed from ignore list.\n")
                                        else:
                                            write(self.detail, "Isn't blocked.\n")
                                        break
                                if not ok:
                                    write(self.detail, "Wrong user.\n")
                            else:
                                write(self.detail, "Invalid command.\n")
                        else:
                            write(self.detail, "Invalid command.\n")
                    else:
                        if self.to:
                            if clients.has_key(self.to):
                                if self.ip not in clients[self.to][3]:
                                    write(clients[self.to], self.detail[1] + ": " + line)
                                else:
                                    write(self.detail, "User blocked you.\n")
                            else:
                                write(self.detail, "User not in list.\n")
                        else:
                            for cl in clients.items():
                                if clients.has_key(cl[0]) and cl[0] != self.ip and self.ip not in clients[cl[0]][3]:
                                    write(cl[1], self.detail[1] + ": " + line)
        except error:
            pass    # disconnected or timed out, so the client is dead
        finally:
            try:
                log.write("[i] Client {0} disconnected.".format(clients[self.ip][1]))
                del clients[self.ip]
                self.detail[0].shutdown(SHUT_RDWR)
                self.detail[0].close()
            except:
                pass


class Watcher(Thread):
    """
    Some kind of listener, but this time is for client.
    Runs in parallel with blocking user input.
    When something is received it's immediately printed.
    Too bad if the console is not flushed in time, it will mix up with the output.
    """

    def __init__(self, cl, data):
        Thread.__init__(self)
        self.cl = cl
        self.data = data

    def run(self):
        try:
            while True:
                (line, self.data) = read(self.cl, self.data)
                if line != "/update":
                    sys.stdout.write(line)
        except error:
            pass    # here the server is dead because the client itself sends an 'update' then server echoes it
        finally:
            try:
                self.cl[0].shutdown(SHUT_RDWR)
                self.cl[0].close()
            except:
                pass


class HeartBeat(Thread):
    """
    Parallel 'update' sender.
    In this way both client and server knows about each other.
    """

    def __init__(self, cl):
        Thread.__init__(self)
        self.cl = cl

    def run(self):
        try:
            while True:
                write(self.cl, "/update")
                time.sleep(PERC * TOUT)
        except error:
            pass    # same as above
        finally:
            try:
                self.cl[0].shutdown(SHUT_RDWR)
                self.cl[0].close()
            except:
                pass


def client():
    """Connect to a server with this protocol."""
    log.write("\n{0} {1} started as {2}.".format(time.ctime(), HOST, "client"))
    data = str()    # client's buffer
    key = md5(str(time.time())).digest()    # 128bit key
    sym = AES.new(key)    # like above, symmetric encryption (much faster)
    cl = [socket(AF_INET, SOCK_STREAM), None, False, None, sym]
    ans = raw_input("Server: ")
    try:
        log.write("[i] Connecting...")
        cl[0].connect((gethostbyname(ans), PORT))    # connect to server
        (line, data) = read(cl[0], data)    # receive a message
        if line[0] == '-':    # or the public key
            half = RSA.importKey(line)    # import it
            write(cl[0], half.encrypt(key, 32)[0])    # send that hash (symmetric key), encrypted
            (line, data) = read(cl, data)    # hello
            log.write("[i] Handshake successful.")
            sys.stdout.write(line)
            Watcher(cl, data).start()
            HeartBeat(cl).start()
            while True:
                msg = raw_input()
                write(cl, msg + '\n')
                if msg == "/quit":
                    break
        else:
            sys.stdout.write(line)
    except (error, gaierror) as msg:
        raise Exception(msg)    # timed out or invalid server
    finally:
        try:
            cl[0].shutdown(SHUT_RDWR)
            cl[0].close()
        except:
            pass


def server():
    """Listen to MAXC clients, each in a separate thread."""
    global clients, full    # extends the visibility domain
    log.write("\n{0} {1}:{2} started as {3}.".format(time.ctime(), HOST, PORT, "server"))
    full = RSA.generate(BITS)    # full key (private + public)
    log.write("[i] Asymmetric key generated.")
    clients = dict()    # with ip = [sock, nick, busy, [ignore], encryption]
    sv = socket(AF_INET, SOCK_STREAM)    # create the socket object
    sv.bind((HOST, PORT))    # open a port to local address
    sv.listen(5)    # queue not-accepted (can be 1)
    log.write("[i] Listening...")
    while True:
        try:
            conn = sv.accept()    # (sock, ip)
            if clients.has_key(conn[1][0]):
                write(conn[0], "You again ?\n")
                continue
            if len(clients) >= MAXC:
                write(conn[0], "Too many, please reconnect later.\n")
                log.write("[i] Maximum number of clients reached.")
                continue
            idnr = 1
            ids = set()
            for cl in clients.items():
                if clients.has_key(cl[0]) and cl[1][1][:len(NAME)] == NAME and cl[1][1][len(NAME):].isdigit():
                    ids.add(int(cl[1][1][len(NAME):]))
            while idnr in ids:
                idnr += 1
            clients[conn[1][0]] = [conn[0], NAME + str(idnr), False, set(), None]    # add client
            log.write("[i] Client connected as {0}.".format(NAME + str(idnr)))
            Listener(conn[1][0]).start()
        except error:
            pass    # here timeout is normal


def main():
    """Main function, not executed when module is imported."""
    global log    # extends the visibility domain
    try:
        log = Logger(FILE)
        setdefaulttimeout(TOUT)    # non blocking
        ans = int(input("1. Client\n2. Server\n"))
        if ans == 1:
            client()
        else:
            server()
    except Exception as msg:
        log.write("[x] Error: {0}.".format(msg))
    except:
        log.write("[!] Forcibly closed.")
    finally:
        log.close()


if __name__ == "__main__":
    main()
