#! /usr/bin/env python

import sys

N = 10
range1 = xrange(ord("A"), ord("Z") + 1)
range2 = xrange(ord("a"), ord("z") + 1)
rez = [0] * N
#found = False


def bt(poz, at):
    global found
    if found:
        return
    if (at == total):
        print "".join([chr(nr) for nr in rez])
        found = True
        return
    if (poz >= N):
        return
    for x in range1:
        if x + at > total:
            continue
        rez[poz] = x
        bt(poz + 1, at + x)
    for x in range2:
        if x + at > total:
            continue
        rez[poz] = x
        bt(poz + 1, at + x)


for arg in sys.argv[1:]:
    found = False
    total = int(arg)
    bt(0, 0)
