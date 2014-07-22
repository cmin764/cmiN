#! /usr/bin/env python


offset = [0, 10, 84, 85, 18, 33, 17, 3, 10, 8]
rezultat = [0]


for poz in xrange(1, len(offset)):
    rezultat.append(rezultat[poz - 1] + offset[poz])

for poz in xrange(len(rezultat)):
    rezultat[poz] += poz

if True:
    for poz in xrange(10):
        print rezultat[poz],

fname = "zambi.lica"
at = 0

with open(fname, "w") as fobj:
    for poz in xrange(400):
        if at < 10 and poz == rezultat[at]:
            fobj.write(fname[at])
            at += 1
        else:
            fobj.write("x")

