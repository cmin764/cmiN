#! /usr/bin/env python


import logging
import random
import sys

import sparse


LOG_LEVEL = logging.DEBUG

EPS = 10 ** -8
K_MAX = 10 ** 6

FILE_A = "generated.txt"
FILE_X = "m_rar_sim_2017.txt"

SPARSE_PROC = 0.0666


def save_random_matrix(dim):
    nr = int(dim ** 2 * SPARSE_PROC / 2)
    gen = lambda: random.randint(1, dim - 1)
    with open(FILE_A, "w") as stream:
        stream.write("{}\n\n".format(dim))
        while nr > 0:
            # Alegem o valoare, linie si coloana aleatoare.
            value, lin, col = gen(), gen(), gen()
            stream.write("{}, {}, {}\n".format(value, lin, col))
            # Punem si valoarea simetrica.
            stream.write("{}, {}, {}\n".format(value, col, lin))
            nr -= 1


def main():
    if len(sys.argv) != 3:
        print("Usage: {} LIN COL".format(sys.argv[0]))
        return

    logging.basicConfig(level=LOG_LEVEL)
    lin, col = map(int, sys.argv[1:3])

    if lin == col:
        # Generam matricea aleatoare.
        save_random_matrix(lin)
        # Citim cele doua mtrici din fisier.
        _, amat = sparse.read_vecmat(FILE_A, name="A", read_vec=False)
        _, xmat = sparse.read_vecmat(FILE_X, name="X", read_vec=False)
        # Citim din nou, insa transpus.
        _, tamat = sparse.read_vecmat(FILE_A, name="TA", read_vec=False,
                                      trans=True)
        _, txmat = sparse.read_vecmat(FILE_X, name="TX", read_vec=False,
                                      trans=True)
        # Verificam daca matricea A, respectiv X este simetrica.
        pairs = [
            (amat, tamat),
            (xmat, txmat),
        ]
        for mat, tmat in pairs:
            status = sparse.mat_equal(mat, tmat)
            if status:
                logging.info("%r este matrice simetrica.", mat)
            else:
                logging.warning("%r NU este matrice simetrica!", tmat)


if __name__ == "__main__":
    main()
