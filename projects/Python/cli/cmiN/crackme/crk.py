#! /usr/bin/env python
# Crack-Me v1.5
# 02.05.2009 <-> 03.05.2009 | cmiN
# non-standard modules = ( Crypto )
# updated to 03.05.2009
# crk

import os, sys, hashlib
from Crypto.Cipher import ARC4

def main():
    global args
    args = sys.argv
    status = False
    if not args[0][-6:] == "crk.py" and not args[0][-7:] == "crk.exe" and not args[0][-3:] == "crk":
        status = True
    status1 = os.path.isfile("hlp.py")
    status2 = os.path.isfile("hlp.exe")
    if not status1 and not status2:
        status = True
    if status:
        bye("Please don't rename / move the executables!")
    elif len(args) == 1:
        start()
    elif args[1] == "-get_response":
        verify()
    elif args[1] == "-msg_response":
        show()

def start():
    os.system("start hlp -get")

def verify():
    password = args[2].split("*")
    hash = ""
    n = 0
    for x in password:
        if n == 0:
            n = 1
            hash = hash + chr(int(x, 16))
        else:
            n = 0
            hash = hash + chr(int(x, 10))
    ans=str(raw_input("Password: "))
    if hash == hashlib.new("sha512", ans).hexdigest():
        os.system("start hlp -msg " + ans)
    else:
        bye("Incorrect password!")

def show():
    key = args[3]
    arc4 = ARC4.new(key)
    message = args[2].split("*")
    encrypted = ""
    for x in message:
        encrypted = encrypted + chr(int(x, 16))
    decrypted = arc4.decrypt(encrypted)
    message = ""
    decrypted = decrypted.split(" ")
    for x in decrypted:
        message = message + chr(int(x, 2))
    bye(message)

def bye(msg):
    print("\n")
    print(msg)
    os.system("pause >NUL")
    exit()

try:
    main()
except:
    exit()
