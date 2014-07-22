#! /usr/bin/env python3.1
# 08.06.2010 <> 08.06.2010 | cmiN
# Simple Directory Comparison 4 paxnWo @ rstcenter.com

import sys, os, threading

def main(args):
    usage = """\t\t Simple Directory Comparison 1.0

\t Usage: source.ext apath bpath mode

Where apath is the first directory
      bpath is the second directory
      mode contain the operations below:
          i - intersection
          d - difference
          r - reversed difference

\t Example: sdc.py C:\\path\\a C:\\path\\b idr"""
    try:
        print("Please wait...")
        if len(args) == 4:
            process(args[1], args[2], args[3])
        else:
            print(usage)
    except Exception as message:
        print("An error occurred: {}".format(message))
    except:
        print("Unknown error.")
    else:
        print("Ready!")

def process(apath, bpath, mode):
    a = Scan(apath)
    b = Scan(bpath)
    a.start()
    b.start()
    a.join()
    b.join()
    with open("a.txt", "w") as afout, open("b.txt", "w") as bfout:
        for x in a.files:
            afout.write(x + "\n")
        for x in b.files:
            bfout.write(x + "\n")
    if "i" in mode:
        intersection = a.files.intersection(b.files)
        with open("i.txt", "w") as fout:
            for x in intersection:
                fout.write(x + "\n")
    if "d" in mode:
        difference = a.files.difference(b.files)
        with open("d.txt", "w") as fout:
            for x in difference:
                fout.write(x + "\n")
    if "r" in mode:
        rdifference = b.files.difference(a.files)
        with open("r.txt", "w") as fout:
            for x in rdifference:
                fout.write(x + "\n")

class Scan(threading.Thread):

    def __init__(self, path):
        threading.Thread.__init__(self)
        self.files = set()
        self.paths = list()
        self.paths.append(os.path.realpath(path))

    def run(self):
        while len(self.paths) > 0:
            path = self.paths.pop()
            paths = os.listdir(path)
            for x in paths:
                y = os.path.join(path, x)
                if os.path.isfile(y):
                    self.files.add(y)
                else:
                    self.paths.append(y)

if __name__ == "__main__":
    main(sys.argv)
