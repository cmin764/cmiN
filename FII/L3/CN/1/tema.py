#! /usr/bin/env python


import math
import random
import time

import numpy as np


C1 = 1.0 / math.factorial(3)
C2 = 1.0 / math.factorial(5)
C3 = 1.0 / math.factorial(7)
C4 = 1.0 / math.factorial(9)
C5 = 1.0 / math.factorial(11)
C6 = 1.0 / math.factorial(13)

def P1(x):
    x2 = x ** 2
    return x * (1 + x2 * (-C1 + C2 * x2))
def P2(x):
    x2 = x ** 2
    return x * (1 + x2 * (-C1 + x2 * (C2 - C3 * x2)))
def P3(x):
    x2 = x ** 2
    return x * (1 + x2 * (-C1 + x2 * (C2 + x2 * (-C3 + C4 * x2))))
def P4(x):
    x2 = x ** 2
    return x * (1 + x2 * (-0.166 + x2 * (0.00833 + x2 * (-C3 + C4 * x2))))
def P5(x):
    x2 = x ** 2
    return x * (1 + x2 * (-C1 + x2 * (C2 + x2 * (-C3 + x2 * (C4 - C5 * x2)))))
def P6(x):
    x2 = x ** 2
    return (x * (1 + x2 * (-C1 + x2 * (C2 + x2 * (-C3 + x2 * (C4 + x2 *
            (-C5 + C6 * x2)))))))


def prob1():
    nr = 1/10.0
    count = 0
    while nr / 10.0 != 0:
        nr /= 10.0
        count += 1
    print("Numarul {} dupa {} iteratii.".format(nr, count))
    return nr


def prob2(nr):
    # Asociativitatea adunarii.
    x = 1.0
    y = z = nr
    e1 = (x + y) + z
    e2 = x + (y + z)
    print(e1, e2, nr)
    print(e1 != e2)    # eroare corectata de interpretor
    # Asociativitatea inmultirii.
    y = z = np.float(nr)
    x = np.float(10) ** 300
    e1 = (x * y) * z
    e2 = x * (y * z)
    print(e1 != e2)


def prob3():
    count = 10000
    hi = math.pi / 2
    lo = -hi
    polys = [P1, P2, P3, P4, P5, P6]
    errs = [0.0] * len(polys)
    for _ in range(count):
        nr = random.uniform(lo, hi)
        expect = math.sin(nr)
        result = [poly(nr) for poly in polys]
        for idx, res in enumerate(result):
            errs[idx] += abs(expect - res)
    final = {polys[idx]: err for (idx, err) in enumerate(errs)}
    rank = sorted(final, key=lambda key: final[key])
    for poly in rank:
        print("{} - {}".format(poly.__name__, final[poly]))


def prob4():
    count = 100000
    hi = math.pi / 2
    lo = -hi
    polys = [P1, P2, P3, P4, P5, P6]
    times = [0.0] * len(polys)
    for _ in range(count):
        nr = random.uniform(lo, hi)
        for idx, poly in enumerate(polys):
            start = time.clock()
            poly(nr)
            delta = time.clock() - start
            times[idx] += delta
    for idx, poly in enumerate(polys):
        print("{} - {}".format(poly.__name__, times[idx]))


def main():
    print("Problema 1 - precizie")
    nr = prob1()
    print("")

    print("Problema 2 - asociativitate")
    prob2(nr)
    print("")

    print("Problema 3 - ranking polinoame")
    prob3()
    print("")

    print("Problema 4 - timp polinoame")
    prob4()
    print("")


if __name__ == "__main__":
    main()
