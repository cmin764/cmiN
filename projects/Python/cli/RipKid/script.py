#! /usr/bin/env python
# cmiN

import sys, urlparse

def main(args):
    if len(args) != 2:
        print("Please specify only the path of the URLs list.")
    else:
        fin = open(args[1], "rt")
        fout = open("links.txt", "wt")
        for line in fin:
            upobj = urlparse.urlsplit(line.strip("\n"))
            pieces = upobj.path.strip("/").split("/")
            if pieces[0].count("."):
                piece = ""
            else:
                piece = pieces[0]
            link = urlparse.urlunsplit([upobj.scheme, upobj.netloc, piece, "", ""])
            fout.write(link + "\n")
        fin.close()
        fout.close()
        print("Ready!")

if __name__ == "__main__":
    main(sys.argv)
