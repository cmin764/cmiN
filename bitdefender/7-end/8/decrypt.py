#! /usr/bin/env python

from sys import argv

startValue = 8

fin = open(argv[1])
hexDump = list()
byte = fin.read(2)
while byte:
    hexDump.append(byte)
    fin.read(1)
    byte = fin.read(2)
fin.close()

fout = open("_" + argv[1], "w")
for i in xrange(len(hexDump)):
    byte = hexDump[i]
    byte = hex(int(byte, 16) ^ (startValue + i % 10))
    fout.write("%s " % byte.replace("0x", "").zfill(2).upper())
fout.close()
