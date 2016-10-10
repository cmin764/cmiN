#! /usr/bin/env python


import sys

import numpy

import mbase


def solve(mat, vec):
    mat = numpy.array(mat)
    vec = numpy.array(vec)
    try:
        return list(numpy.linalg.inv(mat).dot(vec))
    except Exception:
        return None


if __name__ == "__main__":
    mbase.solve = solve
    exit(mbase.main(sys.argv))
