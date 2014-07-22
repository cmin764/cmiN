#! /usr/bin/env python


from sys import argv
from time import ctime, sleep
from random import randint


def log(string=""):
    with open("log.txt", "a") as fout:
        fout.write("[%s] %s\n" %\
            (ctime(), string))


if __name__ == "__main__":
    for arg in argv[1:]:
        log(arg)
        sleep(randint(0, 4))
