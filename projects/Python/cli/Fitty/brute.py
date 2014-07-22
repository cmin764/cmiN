#! /usr/bin/env python3.2
# Recursive Brute Force
# 25.01.2011 cmiN

import sys
from hashlib import md5
from time import time

ti = time()
flag = True

def bf(word, length):
    global flag
    if length > 0:
        for char in charset:
            bf(word + char, length - 1)
    else:
        if md5hash == md5(word.encode()).hexdigest():
            flag = False
            print("Found (%f): %s" % (time() - ti, word))
            exit(0)

def main(args):
    global md5hash, charset
    usage = "brute.py md5 charset length"
    if len(args) != 4:
        print(usage)
    else:
        md5hash = args[1]
        charset = args[2]
        bf("", int(args[3]))
        if flag:
            print("Not found (%f)." % (time() - ti))
    return 0

if __name__ == "__main__":
    main(sys.argv)
