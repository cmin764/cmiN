#! /usr/bin/env python3.1
# 22.02.2010 <> 22.02.2010 | cmiN
# Text Sorter 4 Usr6 @ rstcenter.com

import sys

def sort(args):
    chunks = args[1].split("\\")
    filename = chunks[len(chunks) - 1]
    with open(args[1], "r") as fin, open("\\".join(chunks[:-1] + ["sorted_" + filename]), "w") as fout:
        for line in fin:
            if line.count(args[2]) <= int(args[3]):
                fout.write(line)

def main():
    usage = """\t\t Text Sorter 1.0

\t Usage: sortare.py path character noa

Where path is the file path
      character is the wanted character
      noa is the maximum number of apparitions

\t Example: sortare.py C:\\test.txt 1 2"""
    args = sys.argv
    if len(args) == 4:
        try:
            print("Please wait...")
            sort(args)
        except Exception as message:
            print("An error occurred: {}".format(message))
        except:
            print("Unknown error.")
        else:
            print("Ready!")
    else:
        print(usage)
    input()

if __name__ == "__main__":
    main()
