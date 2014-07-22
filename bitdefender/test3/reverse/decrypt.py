#! /usr/bin/env python


fin = open("out.crypt", "rb")
vector = list(fin.read())
fin.close()
vector = map(ord, vector)

#4
vector.reverse()
#3
for i in xrange(0, len(vector), 2):
    tmp = vector[i]
    vector[i] = vector[i + 1]
    vector[i + 1] = tmp
#2
value = 142
for i in xrange(len(vector)):
    vector[i] ^= (i % 142)

#1
vector2 = list()
for i in xrange(0, len(vector), 2):
    x = vector[i]
    y = vector[i + 1]
    b = (x - y) / 2
    a = x - b
    if a < 0:
        a += 256
    if b < 0:
        b += 256
    vector2.append(a)
    vector2.append(b)

vector2 = map(chr, vector2)
toWrite = "".join(vector2)

#print len(toWrite)
fout = open("in.txt", "wb")
fout.write(toWrite)
fout.close()
