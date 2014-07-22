#! /usr/bin/env python


import os
import sys
import time


DIV = 1024 * 1024    # -> MB
LOG = "log.txt"
touched = False


def log(string=""):
    global touched
    if not touched:
        touched = True
        with open(LOG, "w") as fout:
            fout.write(time.ctime() + "\n")
    with open(LOG, "a") as fout:
        fout.write(string + "\n")


def walk(path, lvl):
    # always a directory
    fileNr = 0
    dirNr = 0
    fileSize = 0

    log("-" * lvl + "Listing %s ..." % path)
    for ent in os.listdir(path):
        absEnt = os.path.join(path, ent)
        log("-" * lvl + absEnt)
        if os.path.isfile(absEnt):
            fileNr += 1
            fileSize += os.path.getsize(absEnt)
        elif os.path.isdir(absEnt):
            dirNr += 1
            (_fileNr, _dirNr, _fileSize) =\
                walk(absEnt, lvl + 1)
            fileNr += _fileNr
            dirNr += _dirNr
            fileSize += _fileSize

    log("-" * lvl + "|%s|" % path)
    log("-" * lvl + "|F: %d|D: %d|S: %fMB|" %\
        (fileNr, dirNr, float(fileSize) / DIV))
    return (fileNr, dirNr, fileSize)


def main(argc, argv):
    if argc != 2:
        print "Usage: %s DIR" % argv[0]
        return 0

    path = os.path.abspath(argv[1])
    if not os.path.isdir(path):
        print "Error: invalid directory"
        return 1

    walk(path, 0)

    return 0


if __name__ == "__main__":
    sys.exit(main(len(sys.argv), sys.argv))
