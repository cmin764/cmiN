#!/bin/python3


import math
import os

#
# Complete the 'formingMagicSquare' function below.
#
# The function is expected to return an INTEGER.
# The function accepts 2D_INTEGER_ARRAY s as parameter.
#

from itertools import permutations

MAGIC_CONSTANT = 15
MAGIC_SQUARES = [
    [[8, 1, 6], [3, 5, 7], [4, 9, 2]],
    [[6, 1, 8], [7, 5, 3], [2, 9, 4]],
    [[4, 9, 2], [3, 5, 7], [8, 1, 6]],
    [[2, 9, 4], [7, 5, 3], [6, 1, 8]],
    [[8, 3, 4], [1, 5, 9], [6, 7, 2]],
    [[4, 3, 8], [9, 5, 1], [2, 7, 6]],
    [[6, 7, 2], [1, 5, 9], [8, 3, 4]],
    [[2, 7, 6], [9, 5, 1], [4, 3, 8]],
]


def is_magic(square):
    # Check rows, columns, and diagonals
    return (
        sum(square[0:3]) == MAGIC_CONSTANT
        and sum(square[3:6]) == MAGIC_CONSTANT
        and sum(square[6:9]) == MAGIC_CONSTANT
        and sum(square[0::3]) == MAGIC_CONSTANT
        and sum(square[1::3]) == MAGIC_CONSTANT
        and sum(square[2::3]) == MAGIC_CONSTANT
        and sum(square[0::4]) == MAGIC_CONSTANT
        and sum(square[2:7:2]) == MAGIC_CONSTANT
    )


# Generate all permutations and filter for magic squares
def get_magic_squares():
    if MAGIC_SQUARES:
        return MAGIC_SQUARES

    magic_squares = []
    for perm in permutations(range(1, 10)):
        if is_magic(perm):
            matrix = [perm[idx * 3 : idx * 3 + 3] for idx in range(3)]
            magic_squares.append(matrix)
    return magic_squares


def formingMagicSquare(s):
    min_cost = math.inf
    magic_squares = get_magic_squares()
    for magic in magic_squares:
        cost = 0
        for i in range(3):
            for j in range(3):
                cost += abs(s[i][j] - magic[i][j])
        min_cost = min(min_cost, cost)

    return min_cost


if __name__ == "__main__":
    # print(get_magic_squares())

    fptr = open(os.environ["OUTPUT_PATH"], "w")

    s = []
    for _ in range(3):
        s.append(list(map(int, input().rstrip().split())))
    # s = [[5, 3, 4], [1, 5, 8], [6, 4, 2]]

    result = formingMagicSquare(s)

    fptr.write(str(result) + "\n")

    fptr.close()
