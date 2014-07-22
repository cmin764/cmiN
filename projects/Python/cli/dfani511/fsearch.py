#! /usr/bin/env python
## Search in ascii files
## 16.10.2011 cmiN


import os, sys


def main():
    kwords = ["facebook", "yahoo"]
    vec = list()
    files = os.listdir(os.getcwd())
    ind = sys.argv[0].rfind("\\")
    if ind == -1:
        ind = sys.argv.rfind("/")
    files.remove(sys.argv[0][ind + 1:])
    for path in files:
        if os.path.isfile(path):
            with open(path, "rt") as fin:
                cur = 0
                for line in fin:
                    cur += 1
                    for kw in kwords:
                        if line.find(kw) != -1:
                            vec.append("In %s found %s at line %d." % (path, kw, cur))
    for res in vec:
        print res


if __name__ == "__main__":
    main()
