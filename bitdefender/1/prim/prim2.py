#! /usr/bin/env python


import sys
from math import sqrt


def prim(nr):
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


def pow(base, exp):
    return base ** exp


def pow2(base, exp):
    if exp == 0:
        return 1
    return base * pow2(base, exp - 1)


def main(argc, argv):
    if argc != 3:
        print "Usage: {} FIRST SECOND".format(argv[0])
        return 0
    try:
        first = int(argv[1])
        second = int(argv[2])
    except ValueError as err:
        print "Error:", err
        return 1
    first = pow2(10, first)
    second = pow2(10, second)
    if not first % 2:
        first += 1
    for nr in xrange(first, second + 1, 2):
        if prim(nr):
            print nr,
    return 0


if __name__ == "__main__":
    rc = main(len(sys.argv), sys.argv)
    sys.exit(rc)
