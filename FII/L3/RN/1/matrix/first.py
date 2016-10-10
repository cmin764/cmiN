#! /usr/bin/env python


import sys

import mbase


DIM = 3


def solve(mat, vec):
    # Compute inverse.
    l = range(DIM)
    # 1 - matrix of minors
    minors = []
    for i in l:
        mrow = []
        for j in l:
            det = []
            for im in l:
                if im == i:
                    continue
                row = []
                for jm in l:
                    if jm == j:
                        continue
                    row.append(mat[im][jm])
                det.append(row)
            det = det[0][0] * det[1][1] - det[0][1] * det[1][0]
            mrow.append(det)
        minors.append(mrow)
    # 2 - cofactoring
    for i in l:
        for j in l:
            minors[i][j] = minors[i][j] * pow(-1, i + j)
    # 3 - adjugate
    _minors = []
    for i in l:
        _minors.append([0] * len(l))
    for i in l:
        for j in l:
            _minors[j][i] = minors[i][j]
    minors = _minors
    # 4 - determinant
    det = 0
    for i in l:
        det += mat[0][i] * minors[i][0]
    if not det:
        print("[!] Null determinant")
        return None
    # 5 - inverse
    d = 1.0 / det
    inv = minors    # just changing tag
    for i in l:
        for j in l:
            inv[i][j] *= d
    # Multiply inverse with vector to get results.
    res = []
    for i in l:
        z = zip(inv[i], vec)
        t = sum([a * b for a, b in z])
        res.append(t)

    return res


if __name__ == "__main__":
    mbase.solve = solve
    exit(mbase.main(sys.argv))
