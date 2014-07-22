#! /usr/bin/env python


import re
import os
import sys
import hashlib


CHUNK = 1024
LOG = "md5dupl.log"


def log(string=""):
    with open(LOG, "a") as fout:
        fout.write(string + "\n")


def get_md5(path, dupl):
    for ent in os.listdir(path):
        ent = os.path.join(path, ent)
        if os.path.isfile(ent):
            with open(ent, "r") as fin:
                md5Obj = hashlib.md5()
                readed = fin.read(CHUNK)
                while readed:
                    md5Obj.update(readed)
                    readed = fin.read(CHUNK)
                hexHash = md5Obj.hexdigest()
                dupl.setdefault(hexHash, [])\
                    .append(ent)
        elif os.path.isdir(ent):
            get_md5(ent, dupl)


def process(paths):
    dupl = dict()
    for path in paths:
        get_md5(path, dupl)
    for item in dupl.iteritems():
        (hexHash, fnames) = item
        if len(fnames) < 2:
            continue
        log("%s: %d" % (hexHash, len(fnames)))
        for fname in fnames:
            log(" " * 34 + fname)


def parse(dirPath, logPath):
    toProcess = list()

    pattern = r"Found proper entry (.+?) \["
    rePat = re.compile(pattern)

    fobj = open(logPath)
    for line in fobj:
        line = line.strip()
        regex = rePat.search(line)
        if not regex:
            continue    # found improper
        filePath = os.path.join(dirPath,
                                regex.group(1))
        if os.path.exists(filePath):
            toProcess.append(filePath)
    fobj.close()
    return toProcess


def main(argc, argv):
    if argc != 3:
        print "Usage: %s DIR LOG" % argv[0]
        return 0

    dirPath = os.path.abspath(argv[1])
    logPath = os.path.abspath(argv[2])

    if not os.path.isdir(dirPath):
        print "Error: invalid directory"
        return 1
    if not os.path.isfile(logPath):
        print "Error: invalid log file"
        return 1

    toProcess = parse(dirPath, logPath)
    process(toProcess)

    return 0


if __name__ == "__main__":
    sys.exit(main(len(sys.argv), sys.argv))
