#! /usr/bin/env python


import logging
import math
import sys

import numpy as np


LOG_LEVEL = logging.DEBUG

K_MAX = 10000
NORM_MAX = 10 ** 8
EPS = 10 ** -8

imat = None

S_CONT = 0
S_CONV = 1
S_DIV = 2
S_ITER = 3


def iter_x(amat, vmat, expr):
    count = 0
    while True:
        count += 1
        next_vmat = expr(amat, vmat)
        yield count, vmat, next_vmat
        vmat = next_vmat


def iter_1(_amat, _vmat):
    expr = lambda amat, vmat: vmat.dot(2 * imat - amat.dot(vmat))
    return iter_x(_amat, _vmat, expr)


def iter_2(_amat, _vmat):
    expr = (lambda amat, vmat:
        vmat.dot(3 * imat - amat.dot(vmat.dot(3 * imat - amat.dot(vmat))))
    )
    return iter_x(_amat, _vmat, expr)


def iter_3(_amat, _vmat):
    expr = (lambda amat, vmat:
        (imat + (1.0 / 4) * (imat - vmat.dot(amat))).dot(
            (3 * imat - vmat.dot(amat))
        ).dot(vmat)
    )
    return iter_x(_amat, _vmat, expr)


ALGORITHMS = {
    1: ("Schultz", iter_1),
    2: ("LiLi1", iter_2),
    3: ("LiLi2", iter_3),
}


def norm_1(amat):
    dim = len(amat)
    sums = []
    for jdx in range(dim):
        sums.append(sum(amat[:,jdx]))
    return max(sums)


def norm_inf(amat):
    dim = len(amat)
    sums = []
    for idx in range(dim):
        sums.append(sum(amat[idx,:]))
    return max(sums)


def all_vmats(amat):
    dim = len(amat)
    # 1
    vmat1 = amat.T / (norm_1(amat) * norm_inf(amat))
    # 2
    vmat2 = np.diag([1.0 / nr for nr in amat.diagonal()])
    # 3
    af = 0
    for idx in range(dim):
        for jdx in range(dim):
            af += amat[idx, jdx] ** 2
    af = af ** (1.0 / 2)
    vmat3 = (1 / af) * imat
    # 4
    vmat4 = imat
    # 5
    vmat5 = imat
    return vmat1, vmat2, vmat3, vmat4, vmat5


def choose_vmat(amat):
    for idx, vmat in enumerate(all_vmats(amat)):
        if norm_1(amat.dot(vmat) - imat) < 1:
            logging.info("Choosing V matrix #{} as:\n{}".format(
                idx + 1, vmat
            ))
            return vmat


def check(count, vmat, next_vmat):
    if count > K_MAX:
        return S_ITER
    norm = norm_1(next_vmat - vmat)
    if norm < EPS:
        return S_CONV
    if norm > NORM_MAX:
        return S_DIV
    return S_CONT


def main():
    global imat
    logging.basicConfig(level=LOG_LEVEL)

    # Obtinem dimensiunea dorita a matricii si algoritmul iterativ ales.
    if len(sys.argv) != 3:
        print("Usage: {} DIM ALG".format(sys.argv[0]))
        return
    dim, alg = map(int, sys.argv[1:3])

    # Cream matricea si alegem functia pentru interatii.
    amat, imat = map(np.identity, [dim] * 2)
    for idx in range(dim - 1):
        amat[idx, idx + 1] = 2
    iter_name, iter_func = ALGORITHMS[alg]
    logging.info("A:\n%s", amat)
    logging.info("Algorithm: %s", iter_name)

    # Alegem convenabil matricea V.
    vmat = choose_vmat(amat)

    # Incepem iteratiile si ne oprim la convergenta/divergenta.
    iter_gen = iter_func(amat, vmat)
    status = None
    for count, vmat, next_vmat in iter_gen:
        status = check(count, vmat, next_vmat)
        if status != S_CONT:
            break
    if status == S_CONV:
        print("Converge:\n{}".format(next_vmat))
        print("Norma: {}".format(norm_1(amat.dot(next_vmat) - imat)))
    else:
        what = "valoare" if status == S_DIV else "numar de iteratii"
        print("Diverge prin {}.".format(what))


if __name__ == "__main__":
    main()
