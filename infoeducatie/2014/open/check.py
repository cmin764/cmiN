#! /usr/bin/env python


import os
import argparse

import Levenshtein


MAX_TIME = 2 * 60.0
TEST = "tests"
TOTAL = "total.txt"
EXT = ".txt"
DELIM = "-_-"

TP1 = 0.2
TP2 = 0.3
TP3 = 0.5
TPS = [TP1, TP2, TP3]

DATA_P = 0.8
TIME_P = 0.2


def get_score(data, test, start, end):
    data_s = 0
    time_s = 0
    diff = Levenshtein.distance(data, test)
    ip = float(diff) / len(test)
    data_s = 100 - ip * 100
    ival = end - start
    ip = float(ival) / MAX_TIME
    time_s = 100 - ip * 100
    return data_s * DATA_P + time_s * TIME_P


def compute(dpath, tests):
    print("Processing {}...".format(os.path.basename(dpath)))
    capts = dict()
    for fname in sorted(os.listdir(dpath)):
        fpath = os.path.join(dpath, fname)
        with open(fpath) as fin:
            capts[fname] = fin.read().strip()
    scores = list()
    ind = 0
    for fname in sorted(capts):
        if not fname.endswith(EXT):
            print("Warning: skip data in {}".format(fname))
            continue
        _, _, start, end = fname.replace(EXT, "").split(DELIM)
        start, end = map(float, [start, end])
        score = get_score(capts[fname], tests[ind], start, end)
        scores.append(score)
        ind += 1
    cscores = list()
    for ind in range(len(scores)):
        score = scores[ind] * TPS[ind]
        cscores.append(score)
    return sum(cscores)


def process(scan, test):
    tests = list()
    for fname in sorted(os.listdir(test)):
        fpath = os.path.join(test, fname)
        with open(fpath) as fin:
            tests.append(fin.read().strip())
    scores = dict()
    for dname in sorted(os.listdir(scan)):
        dpath = os.path.join(scan, dname)
        if not os.path.isdir(dpath):
            print("Warning: skip files in {}".format(dpath))
            continue
        scores[dname] = compute(dpath, tests)
    with open(TOTAL, "w") as fout:
        for name in sorted(scores):
            fout.write("{}: {}\n".format(name, scores[name]))


def main():
    parser = argparse.ArgumentParser(description="InfoEducatie2014 Open evaluator")
    parser.add_argument("input", metavar="INPUT",
                        help="input directory with captures per project")
    parser.add_argument("-t", "--test", metavar="TEST",
                        default=TEST,
                        help="jury official tests directory")
    args = parser.parse_args()
    process(args.input, args.test)


if __name__ == "__main__":
    main()
