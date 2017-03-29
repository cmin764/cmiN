#! /usr/bin/env python


import math
import sys

import numpy


EPS = 10 ** -6


def check_matrix(matrix):
    """Intoarce True daca matricea este simetrica si pozitiv definita."""
    lines = len(matrix)
    if matrix.size / lines != lines:
        return False    # nu-i patratica
    status = (matrix.transpose() == matrix).all()
    if not status:
        return False    # nu-i simetrica
    return numpy.all(numpy.linalg.eigvals(matrix) > 0)    # pozitiv definita


def is_zero(nr):
    if abs(nr) < EPS:
        return True
    return False


def is_equal(first, second):
    return is_zero(first - second)


def descomp(matrix, diag, size):
    # Iteram prin cei N pasi.
    for p in range(0, size):
        total = 0
        # Calculam elementele diagonalei.
        for k in range(0, p):
            total += diag[k] * matrix[p, k] ** 2
        diag[p] = matrix[p, p] - total
        # Si acum elementele lui L de sub diagonala principala.
        if is_zero(diag[p]):
            raise Exception("Gasit element nul pe diagonala principala: "
                            "{}".format(diag))
        for i in range(p + 1, size):
            total = 0
            for k in range(0, p):
                total += diag[k] * matrix[i, k] * matrix[p, k]
            matrix[i, p] = (matrix[i, p] - total) / diag[p]


def determinant(matrix, diag, size):
    # Obtine copie pentru a crea matricea L si D.
    dmat = numpy.full((size, size), 0)
    numpy.fill_diagonal(dmat, diag)
    lmat = matrix.copy()
    for idx in range(size):
        lmat[idx, idx] = 1
        lmat[idx].put(range(idx + 1, size), 0)
    dets = map(
        numpy.linalg.det,
            [
                lmat,
                dmat,
                lmat.T
            ]
        )
    total = 1
    for det in dets:
        total *= det
    return total


def cholsol(matrix, diag, size, bvec):
    # Calculam solutia z.
    zvec = numpy.full(size, 0)
    for i in range(size):
        total = 0
        for j in range(0, i):
            total += matrix[i, j] * zvec[j]
        zvec[i] = bvec[i] - total
    # Acum solutia y.
    yvec = numpy.full(size, 0)
    for i in range(size):
        yvec[i] = zvec[i] / diag[i]
    # Si in final, solutia x.
    xvec = numpy.full(size, 0)
    for i in range(size - 1, -1, -1):
        total = 0
        for j in range(i + 1, size):
            total += matrix[j, i] * xvec[j]
        xvec[i] = yvec[i] - total
    return xvec


def norm(matrix, xchol, bvec, size):
    # Restauram matricea la forma ei initiala.
    for i in range(size):
        for j in range(0, i):
            matrix[i, j] = matrix[j, i]
    # Executam operatiile.
    res = matrix * xchol.reshape(3, 1) - bvec.reshape(3, 1)
    return math.sqrt(sum(map(lambda arg: math.pow(arg[0], 2), res)))


def main(argv):
    if len(argv) != 2:
        print("Usage: {} PREC".format(argv[0]))
        return

    global EPS
    EPS = 10 ** -int(argv[1])
    matrix = [
        [1, 2.5, 3],
        [2.5, 8.25, 15.5],
        [3, 15.5, 43],
    ]
    matrix = numpy.matrix(matrix)
    if not check_matrix(matrix):
        raise Exception(
            "Matricea trebuie sa fie patratica, simetrica si pozitiv "
            "definita."
        )

    # Facem descompunerea.
    size = len(matrix)
    diag = numpy.full(size, 1)
    descomp(matrix, diag, size)
    print("A:\n{}".format(matrix))
    print("D:\n{}".format(diag))

    # Calculam determinantul.
    det = determinant(matrix, diag, size)
    print("Det: {}".format(det))
    if is_zero(det):
        print("Programul se opreste aici, determinantul fiind nul.")
        return

    # Gasim solutia.
    bvec = numpy.full(size, 2)
    xchol = cholsol(matrix, diag, size, bvec)
    print("xChol: {}".format(xchol))

    # Facem verificarea prin norma.
    nr = norm(matrix, xchol, bvec, size)
    print("Norma: {} ({})".format(nr, "OK" if is_zero(nr) else "FAIL"))


if __name__ == "__main__":
    main(sys.argv)
