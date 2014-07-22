#! /usr/bin/env python


# Dictionar de forma d[hash]=(numar,status),
# parsand un log.
#
# Arata statistici.


import re
from math import sqrt


fname = "log.txt"


def prime(nr):
    if nr in (0, 1):
        return False
    if nr == 2:
        return True
    if not nr % 2:
        return False
    nrSq = int(sqrt(nr))
    for i in xrange(3, nrSq + 1, 2):
        if not nr % i:
            return False
    return True


def main():
    files = dict()
    dupl = 0
    dupCln = 0
    dupInf = 0

    # parsare
    template = r"([0-9a-f]+)-([0-9]+)" +\
                "\.done[ ]+(ok|infected)"
    reComp = re.compile(template)

    fobj = open(fname)
    for line in fobj:
        regex = reComp.search(line)
        if regex:
            word = (regex.group(2), regex.group(3))
            key = regex.group(1)
            if key in files:
                dupl += 1
                #print "Warning: duplicate hash"
            files[regex.group(1)] = word

            # count clean/infected primes
            if prime(int(regex.group(2))):
                if regex.group(3) == "ok":
                    dupCln += 1
                else:
                    dupInf += 1
    fobj.close()

    # triere
    nrInf = 0
    nrCln = 0
    primInf = list()
    primCln = list()
    for item in files.iteritems():
        if item[1][1] == "ok":
            nrCln += 1
            if prime(int(item[1][0])):
                primCln.append(item[0])
        else:
            nrInf += 1
            if prime(int(item[1][0])):
                primInf.append(item[0])

    # afisare
    print "Duplicate: %d" % dupl
    print "Clean: %d" % nrCln
    print "Infected: %d" % nrInf

    print ""

    print "Cu numar prim..."

    #print "=" * 12, "Clean", "=" * 12
    print "Clean: %d" % len(primCln)
    print "Clean': %d" % dupCln
    #for name in primCln:
    #    print name

    #print "=" * 11, "Infected", "=" * 11
    print "Infected: %d" % len(primInf)
    print "Infected': %d" % dupInf
    #for name in primInf:
    #    print name


if __name__ == "__main__":
    main()
