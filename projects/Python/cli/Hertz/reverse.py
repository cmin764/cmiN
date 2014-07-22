#! /usr/bin/env python
# 24.07.2009 <> 24.07.2009 | cmiN
# Challenge [Programare] Reverse (Hertz) @ rstcenter.com

__usage__="""
                 Usage:

                         reverse.py filename.ext method

                 Method:

                         encode

                         decode
          """

import os, sys

def reverse(filepath, mode):
    fpi=filepath.index(".")
    infile=open(filepath, "r")
    outfile=open(filepath[:fpi]+"_converted"+filepath[fpi:], "w")
    if mode=="encode":
        order={3:0, 5:1, 0:2, 6:3, 1:4, 7:5, 4:6, 2:7}
    elif mode=="decode":
        order={0:3, 1:5, 2:0, 3:6, 4:1, 5:7, 6:4, 7:2}
    else:
        raise Exception
    while True:
        array=[0, 1, 2, 3, 4, 5, 6, 7]
        source=infile.read(8)
        if len(source)!=8:
            break
        for x in order.keys():
            array[x]=source[order[x]]
        for x in array:
            outfile.write(x)
    infile.close()
    outfile.close()
    del filepath, mode, fpi, infile, outfile, order, array, source

def main():
    if len(sys.argv)!=3:
        print(__usage__)
    else:
        reverse(sys.argv[1], sys.argv[2])

if __name__=="__main__":
    try:
        main()
    except:
        print("An error occurred!")
    os.system("pause >NUL")
