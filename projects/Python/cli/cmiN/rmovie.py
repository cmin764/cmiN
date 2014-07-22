#! /usr/bin/env python


import os
import sys
import time
import random
import argparse


DELAY = 1    # sleep time in seconds for each round (with verbose)
CLEAR = "clear" if "linux" in sys.platform else "cls"


clear = lambda: os.system(CLEAR)


def process(fin, count, shuffle, verbose):
    # read all lines
    lines = list()
    for line in fin:
        lines.append(line.strip())
    fin.close()
    # shuffle them
    for ind in range(shuffle):
        clear()
        print("Shuffle #{}".format(ind + 1))
        random.shuffle(lines)
        if verbose:    # show them for each round
            for line in lines:
                print(line)
            time.sleep(1)
    # extract the first `count` lines
    if count > 1:
        frm = ("s", "are")
    else:
        frm = ("", "is")
    clear()
    print("And the winner{} {}:".format(*frm))
    for ind in range(1, min(count, len(lines)) + 1):
        print("#{} {}".format(ind, lines[ind - 1]))


def main():
    parser = argparse.ArgumentParser(description="Random movie selector.")
    parser.add_argument("-c", "--count", type=int, default=1,
                        help="how many movies to select")
    parser.add_argument("-s", "--shuffle", type=int, default=1,
                        help="how many shuffles to make")
    parser.add_argument("-v", "--verbose", action="store_true",
                        help="show each round")
    parser.add_argument("infile", nargs="?", type=argparse.FileType("r"),
                        default=sys.stdin, help="input file")

    args = parser.parse_args()
    process(args.infile, args.count, args.shuffle, args.verbose)


if __name__ == "__main__":
    main()
