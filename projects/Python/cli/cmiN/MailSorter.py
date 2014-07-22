#! /usr/bin/env python3.1
# 12.09.2009 <> 12.09.2009 | cmiN
# This script sorts e-mails from all files in a path


import os, sys


def sort(args):
    os.chdir(args[2])
    ext = list()
    if args[3] == "*":
        ext.append(".")
    else:
        for x in args[3].split(","):
            ext.append("." + x)
    visited_paths, paths_to_visit = list(), os.listdir(os.getcwd())
    while len(paths_to_visit) != 0:
        x = paths_to_visit.pop()
        if os.path.isfile(x):
            visited_paths.append(x)
        else:
            for y in os.listdir(x):
                paths_to_visit.append(x + "\\" + y)
    for x in visited_paths:
        y = x.split("\\")
        y[len(y) - 1] = "sorted_" + y[len(y) - 1]
        with open(x, "r") as infile, open("\\".join(y), "w") as outfile:
            for z in ext:
                if z in x:
                    lines = infile.readlines()
                    if args[1] == "d":
                        for domain in args[4]:
                            for line in lines:
                                if domain in line:
                                    outfile.write(line)
                                    lines.remove(line)
                    outfile.writelines(sorted(lines))


def main():
    usage = """\t\t Mail Sorter 1.0

\t Usage: MailSorter.py sort_mode directory extensions [domains]

Where sort_mode tells how to sort the mails
                a - in alphabetical order
                d - by domains in the given order
      directory is the path from the text files are read
      extensions is a list of text files extensions separated by comma
                only files with the specified extensions will be read
                put a * if you want to read all files
      domains is a list of domains separated by comma
                domains is required only with "d" sort mode

\t Example: MailSorter.py d C:\\test * yahoo.com,gmail.com,kappa.ro"""
    args = sys.argv
    if len(args) in range(4, 6):
        try:
            print("Please wait ...")
            sort(args)
        except Exception as message:
            print("An error occurred: {}".format(message))
        except:
            print("Unknown error.")
        finally:
            print("Ready !")
    else:
        print(usage)
    input()


if __name__ == "__main__":
    main()
