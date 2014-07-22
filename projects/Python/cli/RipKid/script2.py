#! /usr/bin/env python
# cmiN

import sys, urllib

def main(args):
    if len(args) != 2:
        print("Please supply the path to the links list only.")
    else:
        fin = open(args[1], "rt")
        fout = open("working.txt", "wt")
        for line in fin:
            params = urllib.urlencode({"url": line.strip("\n")})
            uobj = urllib.urlopen("http://usadinspate.ro/osc.php", params)
            if uobj.read().find("nu") == -1:
                fout.write(line)
                fout.flush()
            uobj.close()
        fin.close()
        fout.close()

if __name__ == "__main__":
    main(sys.argv)
