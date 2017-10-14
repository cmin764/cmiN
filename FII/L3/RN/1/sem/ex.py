#! /usr/bin/env python

import datetime
import json
import math
import re
import urllib2
import sys

import numpy


def ex1():
    name = raw_input("Nume Prenume: ")
    age = raw_input("Varsta: ")
    chunks = name.split(" ")
    if len(chunks) != 2:
        print("[x] Doar nume prenume.")
        exit()
    last, first = [part.capitalize() for part in chunks]
    if not age.isdigit() or not int(age):
        print("[x] Varsta invalida")
        exit()
    age = int(age)

    with open("out.txt", "w") as fout:
        fout.write("{}\n".format(first))
        fout.write("{}\n".format(len(last)))
        year = datetime.datetime.now().year + (100 - age)
        fout.write("{}\n".format(year))


def prime(nr):
    if nr < 2:
        return False
    if nr == 2:
        return True
    if not nr & 1:
        return False
    crt = 3
    sq = math.sqrt(nr)
    while crt <= sq:
        if not nr % crt:
            return False
        crt += 2
    return True


def ex2():
    nr = int(sys.argv[1])
    print("{}".format(prime(nr)))


def ex3():
    url = "http://profs.info.uaic.ro/~rbenchea/rn/Latin-Lipsum.txt"
    regex = r"\w+"
    text = urllib2.urlopen(url).read()
    words = re.findall(regex, text, re.I)
    words = sorted(words, key=lambda arg: arg.lower())
    with open("out.txt", "w") as fout:
        for word in words:
            fout.write("{}\n".format(word))


def ex4():
    m = [
        [1, 2, 3, 4],
        [11, 12, 13, 14],
        [21, 22, 23, 24],
    ]
    v = [
        [2],
        [-5],
        [7],
        [10]
    ]
    md = (len(m), len(m[0]))
    vd = (len(v), len(v[0]))
    res = []
    for _ in range(md[0]):
        res.append([0] * vd[1])
    for i in range(md[0]):
        for j in range(vd[1]):
            cell = 0
            for k in range(md[1]):
                print(m[i][k], v[k][j]) ####
                cell += m[i][k] * v[k][j]
            print(i, j, cell)
            res[i][j] = cell
    print(json.dumps(res, indent=4))


def ex5():
    # 1
    m = [
        [1, 2, 3, 4],
        [11, 12, 13, 14],
        [21, 22, 23, 24],
    ]
    v = [
        [2],
        [-5],
        [7],
        [10]
    ]
    m = numpy.array(m)
    v = numpy.array(v)
    print(m.dot(v))
    print(m[:2, -2:])
    print(v[-2:])

    # 2
    dim = (1, 4)
    v1 = numpy.random.random(dim)
    v2 = numpy.random.random(dim)
    print(v1, v2)
    s1 = numpy.sum(v1)
    s2 = numpy.sum(v2)
    print("Sum", (v1 if s1 > s2 else v2))
    print("Add", v1 + v2)
    print("Mul", v1 * v2)
    print("Sqrt", numpy.sqrt(v1))
    print("Sqrt", numpy.sqrt(v2))

    # 3
    dim = (5, 5)
    m = numpy.random.random(dim)
    print(m)
    print(m.T)
    print(numpy.linalg.inv(m))
    print(numpy.linalg.det(m))

    # 4
    v = numpy.random.random((5, 1))
    print(m.dot(v))


ex1()
ex2()
ex3()
ex4()
ex5()
