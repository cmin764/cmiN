#! /usr/bin/env python


import sys
import os
import re
import time


LOG = "renamed.txt"


def log(string=""):
    with open(LOG, "a") as fout:
        fout.write("[%s] %s\n" % (time.ctime(),
                                  string))


def _rename(fileName, newName):
    if os.path.isfile(fileName):
        # if we already renamed the file
        os.rename(fileName, newName)
        fileName = os.path.split(fileName)[1]
        newName = os.path.split(newName)[1]
        log("%s\n%s" % (fileName, newName))
        return True
    else:
        fileName = os.path.split(fileName)[1]
        log("%s\n<File not found>" % fileName)
        return False


def rename(fileName, hashName):
    pattern = r"[0-9a-f]{32}"
    newName = re.sub(pattern, hashName,
                     fileName)

    ret = _rename(fileName, newName)
    if not ret: # .done not found
        return

    # also rename the .nfo
    fileName = fileName.replace(".done", ".nfo")
    newName = newName.replace(".done", ".nfo")

    _rename(fileName, newName)


def parse(dirPath, logName):
    fobj = open(logName)
    for line in fobj:

        # find fname and hashName
        line = line.strip()
        pattern = r"\[.+\] (.+\.done) -> ([0-9a-f]{32}|<Permission denied>)"
        rePat = re.compile(pattern)
        regex = rePat.search(line)

        if not regex:
            # no match -> other data
            continue

        fname = regex.group(1)
        hashName = regex.group(2)

        # check for permissions
        if hashName == "<Permission denied>":
            log("%s\n<Permission denied>" % fname)
            continue

        # rename
        rename(os.path.join(dirPath, fname),
               hashName)
    fobj.close()


def main(argc, argv):
    if argc != 3:
        print "Usage: %s DIR LOG" % argv[0]
        return 0

    dirPath = os.path.abspath(argv[1])
    logPath = os.path.abspath(argv[2])

    if not os.path.isdir(dirPath):
        print "Error: Invalid folder"
        return 1
    if not os.path.isfile(logPath):
        print "Error: Invalid log file"
        return 2

    # parse and rename
    parse(dirPath, logPath)

    return 0


if __name__ == "__main__":
    sys.exit(main(len(sys.argv), sys.argv))
