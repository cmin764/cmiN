#! /usr/bin/env python
## Listen your md5
## 02.08.2011 cmiN

from sys import argv
from winsound import Beep
from hashlib import md5

def init():
    global notes
    N, L = 100, 150 # frequency coefficient and period (N between 40 and 1300)
    chars = filter(str.isalnum, [chr(i) for i in xrange(ord("0"), ord("F") + 1)])
    notes = dict([(k, "Beep(%d, %d)" % ((ord(k) - ord("0")) * N + N, L)) for k in chars])

def process(param):
    for i in md5(param).hexdigest().upper():
        eval(notes[i])

def main():
    if len(argv) != 2:
        print "Usage: ./lymd.py string"
    else:
        init()
        process(argv[1])

if __name__ == "__main__":
    main()
