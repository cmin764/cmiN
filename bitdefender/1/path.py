#! /usr/bin/env python


import os
import sys


def exten(ent):
    ind = ent.rfind(".")
    if ind == -1:
        return None
    return ent[ind + 1:]


def explore(path):
    paths = [path]
    fls = dict()
    flsNr = 0
    drsNr = 0

    while len(paths):
        path = paths.pop(0)

        for ent in os.listdir(path):
            absEnt = os.path.join(path, ent)
            if os.path.isfile(absEnt):
                key = exten(ent)
                if not key:
                    continue
                flsNr += 1
                size = os.path.getsize(absEnt)
                fls[key] = fls.setdefault(key, 0.0) +\
                    float(size) / 1024
            elif os.path.isdir(absEnt):
                drsNr += 1
                paths.append(absEnt)

    print "Files: %d" % flsNr
    print "Directories: %d" % drsNr
    print ""
    for item in fls.iteritems():
        print "%s: %d KB" % item


def main(argc, argv):
    if argc != 2:
        print "Usage: {} PATH".format(argv[0])
        return 0
    path = os.path.abspath(argv[1])
    if not os.path.isdir(path):
        print "Error: not a directory"
        return 1
    explore(path)
    return 0


if __name__ == "__main__":
    sys.exit(main(len(sys.argv), sys.argv))
