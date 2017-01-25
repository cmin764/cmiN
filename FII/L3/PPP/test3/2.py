#! /usr/bin/env python


import sys
import code
import socket



IS_PY3 = sys.version_info >= (3,)
DEBUG = False
ADDR = sys.argv[1:3]

def read_message(client_socket):
    message = client_socket.recv(1024)
    if IS_PY3:
        message = message.decode()
    return message

def send_message(client_socket, message):
    if isinstance(message, str) and IS_PY3:
        message = message.encode()
    client_socket.send(message)

sock = socket.socket()
sock.connect((ADDR[0], int(ADDR[1])))

nr = int(read_message(sock))
if DEBUG:
    print(nr)
for i in range(2, nr):
    if nr % i == 0:
        if DEBUG:
            print(i)
        send_message(sock, str(i))
        break
sock.close()

if DEBUG:
    code.interact(local=locals())
