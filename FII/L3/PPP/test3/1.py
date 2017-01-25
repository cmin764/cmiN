#! /usr/bin/env python


PATH_IN = "input6.txt"
PATH_OUT = "output6.txt"
TRACE = "pYthOn"
DEBUG = False


idx = 0

lines = []


def is_fact(nr):
    n = 1
    s = 1
    while True:
        if nr == n:
            return True
        if n > nr:
            return False 
        n *= s
        s += 1


with open(PATH_IN, "r") as stream:
    for line in stream:
        if TRACE in line:
            if is_fact(idx):
                lines.append(line)
                if DEBUG:
                    print(idx, line)
        idx += 1

with open(PATH_OUT, "w") as stream:
    stream.writelines(lines)
