#! /usr/bin/env python
## spoj.pl/problems/ARITH
## 31.07.2011 cmiN

from decimal import getcontext, Decimal

def init():
    #from sys import stdin
    #stdin = open("arith.in", "rt")
    getcontext().prec = 1024

def add():
    global second
    second = sub + second
    res = str(Decimal(first) + Decimal(second))
    sep1 = max(len(first), len(second))
    sep2 = max(sep1, len(res))
    pat = "%" + str(sep2) + "s"
    print pat % first
    print pat % second
    print pat % ("-" * sep1)
    print pat % res

def mul():
    res = str(Decimal(first) * Decimal(second))
    sep1 = max(len(first), len(second) + 1)
    sep2 = max(sep1, len(res))
    pat = "%" + str(sep2) + "s"
    print pat % first
    print pat % ("*" + second)
    print pat % ("-" * sep1)
    seclen = len(second)
    if seclen > 1:
        for i in xrange(1, seclen + 1):
            print ("%" + str(sep2 - i + 1) + "s") % (int(second[-i]) * Decimal(first))
        print "-" * sep2
    print pat % res

def process():
    global first, second, sub
    tests = input()
    while tests:
        var = raw_input()
        for sub in var:
            if not sub.isdigit():
                break
        (first, second) = var.split(sub)
        if sub in "+-":
            add()
        else:
            mul()
        print
        tests -= 1

def main():
    init()
    process()

if __name__ == "__main__":
    main()
