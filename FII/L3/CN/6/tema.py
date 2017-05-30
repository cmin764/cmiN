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
        saved = {}
        while nr > 0:
            # Alegem o valoare, linie si coloana aleatoare.
            while True:
                value, lin, col = gen(), gen(), gen()
                pair = (lin, col)
                if pair not in saved:
                    saved[pair] = True
                    break
            stream.write("{}, {}, {}\n".format(value, lin, col))
            # Punem si valoarea simetrica.
            stream.write("{}, {}, {}\n".format(value, col, lin))
            nr -= 1


def norm_2(vec):
    total = float(sum(elem ** 2 for elem in vec))
    return total ** (1.0/2)


def exponent_method(mat):
    dim = mat.dim
    # Generam vector aleator.
    vec = [float(random.randint(1, dim)) for _ in range(dim)]
    norm = norm_2(vec)
    vec = [elem / norm for elem in vec]
    assert sparse.is_zero(norm_2(vec) - 1.0 )
    # Totul ok, incepem iteratiile de convergenta.
    wvec = sparse.mat_vec_mul(mat, vec)
    get_lmb = lambda vec1, vec2: sum([item[0] * item[1] for item in zip(vec1, vec2)])
    lmb = get_lmb(wvec, vec)
    count = 0
    last_lmb = lmb
    last_vec = vec
    while True:
        count += 1
        aux = 1.0 / norm_2(wvec)
        vec = [aux * elem for elem in wvec]
        wvec = sparse.mat_vec_mul(mat, vec)
        lmb = get_lmb(wvec, vec)
        rez = [-last_lmb * elem for elem in last_vec]
        rez = [sum(item) for item in zip(wvec, rez)]
        if norm_2(rez) < dim * EPS or count > K_MAX:
            break
        last_lmb = lmb
        last_vec = vec
    return lmb, vec, count


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
            (amat, tamat, "A"),
            (xmat, txmat, "X"),
        ]
        for mat, tmat, name in pairs:
            status = sparse.mat_equal(mat, tmat)
            if status:
                logging.info("%r este matrice simetrica.", mat)
            else:
                logging.warning("%r NU este matrice simetrica!", tmat)
            # Obtinem valoarea si vectorul propriu.
            val, vec, count = exponent_method(mat)
            print("Valoare {}: {}".format(name, val))
            print("Vector {}: {}".format(name, vec))
            print("Iteratii {}: {}".format(name, count))
            first = sparse.mat_vec_mul(mat, vec)
            second = [val * elem for elem in vec]
            assert first == second


if __name__ == "__main__":
    main()
