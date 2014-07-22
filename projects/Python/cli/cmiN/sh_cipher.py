#! /usr/bin/env python
# 14.07.2009 <> 14.07.2009 | cmiN
# Challenge [Programare] Misiunea 1: Evadarea (cmiN) @ rstcenter.com
# Rezolvare: Felicitari! Ai trecut de primul nivel. Parola pentru a debloca usa este: PadLock15853


__doc__="""  This library encodes a string to a numeric string
and decodes a numeric string to a string."""
__usage__="""        Usage:
                 [+] Encode a string:
                         sh_cipher.py encode "string"
                 [+] Decode an encoded string:
                         sh_cipher.py decode "7956...532"
"""


import os, random, sys


def encode(instr):
    outstr, aenstr="", ""
    for x in instr:
        aenstr+=str(ord(x))+" "
    z=" "
    for x in aenstr:
        numbers=["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]
        if not x==" ":
            numbers.remove(x)
        random.shuffle(numbers)
        while z==numbers[0]:
            random.shuffle(numbers)
        z=x
        for x in numbers:
            outstr+=x
    del instr, aenstr, numbers, x, z
    return outstr


def decode(outstr):
    l=[]
    aenstr, instr="", ""
    l[:]=outstr
    while len(l)!=0:
        if l[9] in l[:9]:
            numbers=["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]
            for x in l[:9]:
                numbers.remove(x)
            aenstr+=numbers[0]
            l[:9]=[]
        else:
            aenstr+=" "
            l[:10]=[]
    aenstr=aenstr.strip(" ")
    for x in aenstr.split(" "):
        instr+=chr(int(x))
    del outstr, aenstr, numbers, x, l
    return instr


def main():
    args=sys.argv
    if len(args)!=3:
        print(__doc__)
        print(__usage__)
    else:
        if args[1]=="encode":
            print(encode(args[2]))
        elif args[1]=="decode":
            print(decode(args[2]))
        else:
            raise Exception
    del args
    

if __name__=="__main__":
    try:
        main()
    except:
        print("An error occurred!")
    os.system("pause >NUL")
