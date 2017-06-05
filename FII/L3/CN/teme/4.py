#! /usr/bin/env python


import logging
import math

import sparse


LOG_LEVEL = logging.DEBUG

_TEMPLATE = "m_rar_2017_{}.txt"
FILE_1, FILE_2, FILE_3, FILE_4 = map(_TEMPLATE.format,
                                     (1, 2, 3, 4))

K_MAX = 10000
NORM_MAX = 10 ** 8
EPS = 10 ** -8


def get_norm(res):
    total = 0
    for elem in res:
        nr = math.pow(elem[0] - elem[1], 2)
        total += nr
    return math.sqrt(total)


def gauss(vec, mat):
    dim = len(vec)
    res = [(0, 0)] * dim
    count = 0
    while True:
        # Copiere xc in xp.
        for idx, elem in enumerate(res):
            res[idx] = (elem[0], elem[0])
        # Calculare nou xc.
        for lin in range(dim):
            csum = psum = 0
            line = mat.get_line(lin, sparse=True)
            for col, val in line.items():
                if col < lin:
                    csum += line[col] * res[col][0]
                elif col > lin:
                    psum += line[col] * res[col][1]
            old = res[lin]
            res[lin] = ((vec[lin] - csum - psum) / line[lin], old[1])
        # Calculam norma pentru verificare conditii.
        norm = get_norm(res)
        if norm < EPS or count > K_MAX or norm > NORM_MAX:
            break
        count += 1

    logging.debug("Iterations: %d", count)
    if norm < EPS:
        return [elem[0] for elem in res]    # convergenta
    return None    # divergenta


def main():
    logging.basicConfig(level=LOG_LEVEL)

    # Citim toate cele 4 matrici.
    vec1, mat1 = sparse.read_vecmat(FILE_1, name="1")
    vec2, mat2 = sparse.read_vecmat(FILE_2, name="2")
    vec3, mat3 = sparse.read_vecmat(FILE_3, name="3")
    vec4, mat4 = sparse.read_vecmat(FILE_4, name="4")

    # Verificam ca toate cele 4 diagonale sunt nenule,
    # petru a avea matrici nesingulare (det != 0).
    assert all(mat1.diagonal)
    assert all(mat2.diagonal)
    assert all(mat3.diagonal)
    assert all(mat4.diagonal)

    pairs = [
        (vec1, mat1),
        (vec2, mat2),
        (vec3, mat3),
        (vec4, mat4),
    ]
    idx = 1
    for vec, mat in pairs:
        ret = gauss(vec, mat)
        if ret:
            logging.info("Convergenta: %f", ret[-1])
            res = sparse.mat_vec_mul(mat, ret)
            verif = [(res[idx], vec[idx]) for idx in range(mat.dim)]
            norm = get_norm(verif)
            #logging.debug("Norma: %f", norm)
            assert sparse.is_zero(norm)
        else:
            logging.warn("Divergenta.")
        idx += 1


if __name__ == "__main__":
    main()
