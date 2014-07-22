#! /usr/bin/env python


import sys
import os
import json


def process(path, tree):
    name = os.path.basename(path)
    crt = tree[name] = list()
    for ent in os.listdir(path):
        absEnt = os.path.join(path, ent)
        if os.path.isfile(absEnt):
            crt.append(ent)
        elif os.path.isdir(absEnt):
            newTree = {}
            crt.append(newTree)
            process(absEnt, newTree)


def main(argc, argv):
    if argc != 2:
        print "Usage: %s DIRECTORY" % argv[0]
        return 0

    path = argv[1]
    if not os.path.isdir(path):
        print "Error: invalid directory"
        return 1

    tree = dict()
    process(path, tree)
    with open("tree.json", "w") as fout:
        fout.write(json.dumps(tree))


if __name__ == "__main__":
    main(len(sys.argv), sys.argv)
