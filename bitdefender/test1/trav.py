#! /usr/bin/env python


import sys
import os
import hashlib


LET = "Z"
CHUNK = 1024
STR = "This file is ok"
LOG = "fisiere.log"
PATH = None


def log(string=""):
    with open(LOG, "a") as fout:
        fout.write(string + "\n")


def get_md5(path):
    md5Obj = hashlib.md5()
    try:
        fileObj = open(path, "rb")
    except IOError as err:
        print "Error: %s" % err
        return None
    readed = fileObj.read(CHUNK)
    while readed:
        md5Obj.update(readed)
        readed = fileObj.read(CHUNK)
    fileObj.close()
    # all fine
    return md5Obj.hexdigest()


def contain(path):
    try:
        with open(path) as fin:
            for line in fin:
                if STR in line:
                    return True
    except IOError as err:
        print "Error: %s" % err
    return False


def process(path):
    try:
        paths = os.listdir(path)
    except OSError as err:
        print "Error: %s" % err
        return

    # ok
    for ent in paths:
        absEnt = os.path.join(path, ent)
        if os.path.isfile(absEnt) and path != PATH:
            if not contain(absEnt):
                continue
            hexHash = get_md5(absEnt)
            if hexHash:
                logString = "%s \t {} \t %s".format(hexHash)
            else:
                logString = "%s \t <Couldn't read> \t %s"
            log(logString % (ent, absEnt))
        elif os.path.isdir(absEnt) and not os.path.islink(absEnt):
            if LET in os.path.split(absEnt)[1]:
                # contains Z in folder
                process(absEnt)


def main(argc, argv):
    if argc != 2:
        print "Usage: %s DIR" % argv[0]
        return 0

    path = os.path.abspath(argv[1])
    if not os.path.isdir(path):
        print "Error: invalid directory"
        return 1

    global PATH
    PATH = path
    process(path)

    return 0


if __name__ == "__main__":
    sys.exit(main(len(sys.argv), sys.argv))
