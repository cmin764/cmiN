#! /usr/bin/env python


import os
import sys
import time
import hashlib


DELAY = 2
CHUNK = 1024
LOG = "out.log"


def log(string=""):
    string = "[%s] %s\n" % (time.ctime(),
                            string)
    print string
    with open(LOG, "a") as fout:
        fout.write(string)
        fout.flush()


def get_details(relEnt):
    size = os.path.getsize(relEnt)

    try:
        md5Obj = hashlib.md5()
        with open(relEnt, "rb") as fin:
            readed = fin.read(CHUNK)
            while readed:
                md5Obj.update(readed)
                readed = fin.read(CHUNK)
    except IOError as err:
        csum = None
    else:
        csum = md5Obj.hexdigest()
    return (size, csum)


def fill(fils, dirs, path):
    try:
        paths = os.listdir(path)
    except OSError:
        dirs[path] = False
    else:
        for ent in paths:
            relEnt = os.path.join(path, ent)
            if os.path.isfile(relEnt):
                fils[relEnt] = get_details(relEnt)
            elif os.path.isdir(relEnt) and not\
                 os.path.islink(relEnt):
                     dirs[relEnt] = True
                     fill(fils, dirs, relEnt)


def compare(fils, _fils, dirs, _dirs):
    # check directories
    for item in dirs.iteritems():
        (key, stat) = item
        _stat = _dirs.get(key)
        if _stat is None:
            log("D: %s deleted" % key)
        elif not _stat and stat:
            log("D: %s couldn't read" % key)
        elif _stat and not stat:
            log("D: %s content may changed" % key)
    for item in _dirs.iteritems():
        (key, stat) = item
        if key not in dirs:
            log("D: %s created" % key)

    # check files
    for item in fils.iteritems():
        (path, (size, csum)) = item
        other = _fils.get(path)
        if other is None:
            log("F: %s deleted" % path)
        else:
            # was modified ?
            (_size, _csum) = other
            if _size != size:
                log("F: %s %d -> %d" %\
                    (path, size, _size))
            elif _csum != csum:
                if _csum is None and csum:
                    log("F: %s couldn't read" % path)
                elif csum is None:
                    log("F: %s content may changed" % path)
                elif _csum and csum:
                    log("F: %s content changed" % path)
    for item in _fils.iteritems():
        (path, (size, csum)) = item
        other = fils.get(path)
        if other is None:
            log("F: %s created" % path)


def watch(path):
    fils = dict()
    dirs = dict()
    fill(fils, dirs, path)

    while True:
        if not os.path.isdir(path):
            log("Main folder not" +\
                "found, nothing to watch for")
            return
        try:
            os.listdir(path)
        except OSError:
            log("Could not read main folder, exiting")
            return
        _fils = dict()
        _dirs = dict()
        fill(_fils, _dirs, path)
        compare(fils, _fils,
                dirs, _dirs)
        fils = _fils
        dirs = _dirs
        time.sleep(DELAY)


def main(argc, argv):
    if argc != 2:
        print "Usage: %s DIR" % argv[0]
        return 0
    if not os.path.isdir(argv[1]):
        print "Error: invalid directory"
        return 1

    log("Started")
    try:
        watch(argv[1])
    except KeyboardInterrupt:
        log("Stopped")

    return 0


if __name__ == "__main__":
    sys.exit(main(len(sys.argv), sys.argv))
