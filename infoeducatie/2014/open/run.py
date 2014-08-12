#! /usr/bin/env python


import os
import time
import argparse
import subprocess


DELAY = 0.01
MAX_TIME = 2 * 60.0
INFILE = "mesaj.txt"
DELIM = "-_-"
EXT = ".txt"


def run(fpath, infile=INFILE, max_time=MAX_TIME, params=None):
    start = time.time()
    myargs = [fpath]
    if params:
        myargs.extend(params)
    pop = subprocess.Popen(myargs)
    while pop.poll() is None:
        if time.time() - start > max_time:
            pop.kill()
            print("Warning: process killed")
        time.sleep(DELAY)
    outfile = "{1}{0}{2}{0}{3}{0}{4}{5}".format(
        DELIM,
        os.path.basename(fpath),
        os.path.basename(infile),
        start, time.time(),
        EXT
    )
    try:
        with open(infile) as fin, open(outfile, "w") as fout:
            fout.write(fin.read())
    except Exception as exc:
        print("Error: {}".format(exc))


def main():
    parser = argparse.ArgumentParser(description="InfoEducatie2014 Open testing utility")
    parser.add_argument("executable", metavar="EXECUTABLE",
                        help="path to the file to run")
    parser.add_argument("-i", "--infile", metavar="PATH",
                        default=INFILE,
                        help="default file path for writing the message")
    parser.add_argument("-t", "--time", metavar="FLOAT",
                        type=float, default=MAX_TIME,
                        help="maximum allowed time for the program to run")
    parser.add_argument("-p", "--params", metavar="PARAM",
                        nargs="+", help="extra parameters")
    args = parser.parse_args()
    run(args.executable, infile=args.infile, max_time=args.time, params=args.params)


if __name__ == "__main__":
    main()
