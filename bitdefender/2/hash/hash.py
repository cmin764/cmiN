#! /usr/bin/env python


import hashlib
import sys
import os
import time
import re


# constants
LOG = "log.txt"
CHUNK = 1024


def log(string=""):
    with open(LOG, "a") as fout:
        fout.write("[%s] %s\n" % (time.ctime(),
                   string))


def process(path):
    # collect .done and .nfo
    # {name: (hash, path)}
    dones = dict()
    nfos = dict()

    template = r"-([0-9a-f]{32})-\d+\.(done|nfo)"
    rePat = re.compile(template)

    for ent in os.listdir(path):
        absEnt = os.path.join(path, ent)
        if not os.path.isfile(absEnt):
            continue
        # is file, parse name
        regex = rePat.search(ent)
        if not regex:
            continue
        hashName = regex.group(1)
        ext = regex.group(2)
        if ext == "done":
            dones[ent] =\
                (hashName, absEnt)
        elif ext == "nfo":
            nfos[ent] =\
                (hashName, absEnt)
        else:
            print "Warning: found something else: %s" %\
                ext
    return (dones, nfos)


def checksum(path):
    md5Obj = hashlib.md5()
    try:
        with open(path, "rb") as fin:
            readed = fin.read(CHUNK)
            while readed != "":
                md5Obj.update(readed)
                readed = fin.read(CHUNK)
        return md5Obj.hexdigest()
    except IOError:
        return None


def status(dones, nfos):
    total = len(dones) + len(nfos)
    pairs = 0  # done+nfo
    doneNr = 0 # done only
    nfoNr = 0  # nfo only

    for key in dones.iterkeys():
        if key.replace("done", "nfo") in nfos:
            pairs += 1
        else:
            doneNr += 1

    nfoNr = total - 2 * pairs - doneNr

    # now check for md5
    for item in dones.iteritems():
        (fileName, (hashName, path)) = item
        _hashName = checksum(path)
        if not _hashName:
            log("%s -> <Permission denied>" % fileName)
            continue
        if hashName != _hashName:
            log("%s -> %s" % (fileName, _hashName))

    # log remaining statistics
    log("Pairs: %s" % pairs)
    log("Done: %s" % doneNr)
    log("Nfo: %s" % nfoNr)


def main(argc, argv):
    if argc != 2:
        print "Usage: %s DIR" % argv[0]
        return 0

    # absolute path
    path = os.path.abspath(argv[1])
    if not os.path.isdir(path):
        print "Error: not a directory"
        return 1

    ret = process(path)
    status(*ret)

    return 0


if __name__ == "__main__":
    sys.exit(main(len(sys.argv), sys.argv))
