#! /usr/bin/env python


import os
import re
import sys


STR = ""
rePat = re.compile(r"..[a-zA-Z][0-9].*", re.DOTALL)


def process(path):
    try:
        paths = os.listdir(path)
    except OSError as err:
        print "Error: %s" % err
        return
    
    for ent in paths:
        absEnt = os.path.join(path, ent)
        if os.path.isdir(absEnt):
            regex = rePat.match(ent)
            if not regex:
                continue
            global STR
            STR += ent[:2]
            process(absEnt)


def main(argc, argv):
    if argc != 2:
        print "Usage: %s DIR" % argv[0]
        return 0
    
    path = os.path.abspath(argv[1])
    if not os.path.isdir(path):
        print "Error: invalid path"
        return 1
    
    process(path)
    print STR

    return 0
    

if __name__ == "__main__":
    sys.exit(main(len(sys.argv), sys.argv))
