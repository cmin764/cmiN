#! /usr/bin/env python


import sys
import os
import re
from shutil import copyfile


def parse(html, dirList, fileList, imgList):
    with open(html, "r") as fin:
        data = fin.read()

    dirTemp = r"<h1>(.+?)</h1>"
    fileTemp = r"<li>(.+?)</li>"
    imgTemp = r'<IMG SRC="(.+?)">'

    regex = re.search(dirTemp, data)
    dirName = regex.group(1)
    dirList.append(dirName)

    for regex in re.finditer(fileTemp, data):
        fileList.append(os.path.join(dirName, regex.group(1)))
    
    for regex in re.finditer(imgTemp, data):
        imgList.append(regex.group(1))


def process(path):
    dirList = list()
    fileList = list()
    imgList = list()

    for ent in os.listdir(path):
        absEnt = os.path.join(path, ent)
        if os.path.isfile(absEnt):
            ind = absEnt.rfind(".")
            if absEnt[ind + 1:].lower() == "html":
                parse(absEnt,
                      dirList, fileList, imgList)

    dirList.sort()
    fileList.sort()
    imgList.sort()

    # Acum pe baza celor trei liste
    # creeaza mai intai folderele, apoi
    # fisierele si imaginile.

    for folder in dirList:
        if not os.path.isdir(folder):
            os.mkdir(folder)
    for fpath in fileList:
        copyfile(os.path.join(path, fpath), fpath)
    for fpath in imgList:
        copyfile(os.path.join(path, fpath), fpath)


def main(argc, argv):
    if argc != 2:
        print "Usage: %s DIRECTORY" % argv[0]
        return 0

    path = argv[1]
    if not os.path.isdir(path):
        print "Error: invalid directory"
        return 1

    process(path)


if __name__ == "__main__":
    main(len(sys.argv), sys.argv)
