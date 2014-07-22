#! /usr/bin/env python
# 20.07.2009 <> 20.07.2009 | cmiN
# Challenge 4 Hertz @ rstcenter.com

__doc__="""
    This library encodes / decodes a file by reversing the bytes read from it.\n
        """
__usage__="""
                Usage:
                        byte.py filename.ext method lineswitch type

                Method:

                        b - reverse bytes: A3 C4 5D -> 3A 4C D5
                        
                        l - reverse lines: A3 C4 5D -> 5D C4 A3

                        r - reverse rows : A3 C4 5D    6B 2C 3F
                                           2E D3 1A -> 2E D3 1A
                                           6B 2C 3F    A3 C4 5D

                Lineswitch:

                        ON  - Reverse also the LineFeed byte (new line)
                        OFF - Don't change the LineFeed position

                Type:

                        A - ASCII
                        B - BINARY
          """

import os, sys

def reverse(filepath, mode, switch, flag):
    if flag=="A":
        flag=""
    else:
        flag="b"
    infile=open(filepath, "r"+flag)               #0x03  Deschidem fisierul din locatia citita si
    inbytes=infile.readlines()                    #     ii citim octetii linie cu linie.
    infile.close()
    for x in range(len(inbytes)):                 #0x04  Spargem fiecare linie in lista, apoi
        l=[]                                      #     convertim octetii, obtinand in final
        l[:]=inbytes[x]                           #     o lista ce contine liste ce contin
        inbytes[x]=l                              #     string-uri cu reprezentarea hexadecimala a fiecarui octet.
        for y in range(len(inbytes[x])):
            z=hex(ord(inbytes[x][y]))[2:]
            while len(z)<2:
                z="0"+z
            inbytes[x][y]=z
    if switch=="OFF":
        for x in inbytes:
            try:
                x.remove("0a")
            except:
                status=True
            else:
                status=False
    if "r" in mode:                               #0x05  In functie de modul ales inversam
        inbytes.reverse()                         #     pozitia si rasturnam octeti.
    if "l" in mode:
        for x in inbytes:
            x.reverse()
    if "b" in mode:
        for x in inbytes:
            for y in range(len(x)):
                x[y]=x[y][::-1]
    if switch=="OFF":
        for x in inbytes:
            x.append("0a")
        if status:
            inbytes[len(inbytes)-1].remove("0a")
    outbytes=""
    for x in inbytes:                             #0x06  Convertim fiecare string inapoi in octet,
        for y in x:                               #     apoi ii scriem pe toti intr-un fisier
            outbytes+=chr(int(y, 16))             #     cu nume si extensie inversata.
    outfile=open(infile.name[::-1], "w"+flag)
    outfile.write(outbytes)
    outfile.close()
    print("Ready! Check %s" % outfile.name)
    del filepath, mode, switch, flag, infile, inbytes, x, y, z, outbytes, outfile

def main():
    if len(sys.argv)!=5:                          #0x02  Citim argumentele furnizate de user si
        print(__doc__)                            #     daca avem suficiente apelam functia reverse()
        print(__usage__)                          #     cu argumentele ce contin locatia unui fisier si modul preferat.
    else:
        reverse(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])

if __name__=="__main__":
    try:                                          #0x01  Executam functia main(), exceptand orice erroare
        main()                                    #     poate aparea pe parcurs.
    except WindowsError:
        print("An error occurred!")
    os.system("pause >NUL")                       #0x00  Pauza de final pentru citirea output-ului.
