#! /usr/bin/env python

import os

def main():
    paths = list()
    paths.append(os.getcwd())
    while len(paths) > 0:
        path = paths.pop()
        subpaths = os.listdir(path)
        for x in subpaths:
            y = os.path.join(path, x)
            if os.path.isfile(y):
                print("Renaming file: " + y)
                os.rename(y, y.rstrip(";1"))
            else:
                print("Adding path: " + y)
                paths.append(y)

if __name__ == "__main__":
    main()
