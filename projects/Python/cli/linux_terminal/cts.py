#! /usr/bin/env python3.1
# 06.06.2010 <> 06.06.2010 | cmiN
# Custom Text Sorter 4 linux_terminal @ rstcenter.com

import sys

def main(args):
    usage = """\t\t Custom Text Sorter 1.0

\t Usage: source.ext infile wordc

Where infile is a valid text file
      wordc is is the class that are you searching for

\t Example: cts.py words.txt 13*7**cm*N*"""
    try:
        print("Please wait...")
        if len(args) == 3:
            process(args[1], args[2])
        else:
            print(usage)
    except Exception as message:
        print("An error occurred: {}".format(message))
    except:
        print("Unknown error.")
    else:
        print("Ready!")

def process(infile, wordc):
    letters = dict()
    swords, rwords = list(), list()
    length = len(wordc)
    for x in wordc:
        if not x == "*":
            letters[wordc.index(x)] = x
    with open(infile, "rt") as fin:
        words = fin.read().split()
    for word in words:
        status = True
        if len(word) == length:
            for x in letters:
                if not letters[x] == word[x]:
                    status = False
            if status:
                swords.append(word)
            else:
                rwords.append(word)
        else:
            rwords.append(word)
    swords.sort()
    rwords.sort()
    with open(infile, "wt") as fout:
        for word in swords:
            fout.write(word + "\n")
        for word in rwords:
            fout.write(word + "\n")

if __name__ == "__main__":
    main(sys.argv)
