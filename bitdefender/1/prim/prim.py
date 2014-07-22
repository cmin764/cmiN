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


def main(argc, argv):
    if argc != 2:
        print "Usage: {} INT".format(argv[0])
        return 0
    try:
        nr = int(argv[1])
    except ValueError:
        print "Error: Invalid number"
        return 1
    if prim(nr):
        print "Este prim"
    else:
        print "Nu este prim"
    return 0


if __name__ == "__main__":
    rc = main(len(sys.argv), sys.argv)
    sys.exit(rc)
