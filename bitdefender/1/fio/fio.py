#! /usr/bin/env python


import sys
from math import sqrt


fname = "ACKS.txt"
vowels = list("aeiou")


def f1():
    with open(fname) as fin:
        cnt =  len(fin.readlines())
    return cnt


def f2():
    with open(fname) as fin:
        for line in fin:
            if "*" in line:
                print line.strip()


def f3():
    with open(fname) as fin:
        for line in fin:
            line = line.strip()
            cnt = 0
            for vow in vowels:
                cnt += line.lower().count(vow)
            if cnt > 6:
                print line


def f4():
    length = int(raw_input("Lungime: "))
    with open(fname) as fin:
        for line in fin:
            line = line.strip()
            if len(line) == length:
                print line


def f5():
    cnt = 0
    with open(fname) as fin:
        for line in fin:
            line = line.strip()
            lineLow = line.lower()
            # numarul de consoane
            nrCons =  0
            for pad in xrange(26):
                char = chr(ord("a") + pad)
                if char in vowels:
                    continue
                nrCons += lineLow.count(char)
            # numarul de vocale
            nrVoc = 0
            for vow in vowels:
                nrVoc += lineLow.count(vow)
            # daca sunt vocale/consoane si daca e divizibil
            if nrVoc and nrCons and not nrCons % nrVoc:
                cnt += 1
                print "Consoane: %d Vocale: %d" %\
                    (nrCons, nrVoc)
                print line + "\n"
    return cnt


def prime(nr):
    if nr in (0, 1):
        return False
    if nr == 2:
        return True
    if not nr % 2:
        return False
    nrSq = int(sqrt(nr))
    for i in xrange(3, nrSq + 1, 2):
        if not nr % i:
            return False
    return True


def f6():
    with open(fname) as fin:
        for line in fin:
            if prime(len(line)):
                print line.strip()


def main(argc, argv):
    if argc != 2:
        print "Usage: %s CERINTA" % argv[0]
        return 0
    req = int(argv[1])
    if req == 1:
        print f1()
    elif req == 2:
        f2()
    elif req == 3:
        f3()
    elif req == 4:
        f4()
    elif req == 5:
        f5()
    elif req == 6:
        f6()
    else:
        print "Cerinta invalida"
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main(len(sys.argv), sys.argv))
