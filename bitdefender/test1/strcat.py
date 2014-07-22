#! /usr/bin/env python


import os
import sys
import re


def get_detail(path):
    ind = None
    poz = None
    fileObj = open(path)
    for line in fileObj:
        line = line.rstrip()
        regex = re.search(r"INDEX: (\d+)", line)
        if regex:
            ind = regex.group(1)
        regex = re.search(r"POZITIE: (\d+)", line)
        if regex:
            poz = regex.group(1)
    fileObj.close()
    if ind is None or poz is None:
        return None
    return (int(ind), int(poz))


def get_info(lineStr):
    # with .txt
    pattern1 = r"([ -.a-zA-Z]+)\s+([a-f0-9]{32})\s+(.+)"
    #  without it
    pattern2 = r"([ a-zA-Z]+)\s+([a-f0-9]{32})\s+(.+)"
    rePat = re.compile(pattern1)
    
    regex = rePat.search(lineStr)
    ret = get_detail(regex.group(3))
    if ret is None:
        return None
    (ind, poz) = ret
    char = regex.group(1)[ind]
    return (char, poz)


def process(path):
    myStr = []
    fileObj = open(path)
    for line in fileObj:
        line = line.rstrip()
        ret = get_info(line)
        if ret is None:
            continue
        (char, poz) = ret
        length = len(myStr)
        if poz >= length:
            for i in xrange(poz - length + 1):
                myStr.append("-")
        myStr[poz] = char
    fileObj.close()
    return "".join(myStr)


def main(argc, argv):
    if argc != 2:
        print "Usage: %s LOG" % argv[0]
        return 0

    path = os.path.abspath(argv[1])
    if not os.path.isfile(path):
        print "Error: invalid log file"
        return 1

    procStr = process(path)
    print procStr

    return 0


if __name__ == "__main__":
    sys.exit(main(len(sys.argv), sys.argv))
