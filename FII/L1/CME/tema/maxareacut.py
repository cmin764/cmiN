#! /usr/bin/env python


import sys


def area(topLeft, botRight):
    return (botRight[0] - topLeft[0] + 1) *\
           (botRight[1] - topLeft[1] + 1)


def process(topLeft, botRight, holes):
    """Functie ce cauta si gaseste coordonatele suprafetei
    de are maxima.
    
    Cauta recursiv in jumatatea de sus/jos apoi in cea din
    stanga si din dreapta si in momentul in care nu se mai
    gasesc gauri in interiorul ariei curente, atunci
    avem un posibil candidat pentru aria maxima.
    """

    noHoles = True    # nu sunt gauri
    maxRet = (0, None, None)

    # testam daca este posibila suprafata curenta
    if topLeft[0] > botRight[0] or\
       topLeft[1] > botRight[1]:
           return maxRet

    for hole in holes:
        # gaura se afla in interior
        if hole[0] >= topLeft[0] and hole[0] <= botRight[0] and\
           hole[1] >= topLeft[1] and hole[1] <= botRight[1]:
               noHoles = False
               # mergem in N
               ret = process(topLeft,
                             (botRight[0], hole[1] - 1),
                             holes)
               if ret[0] > maxRet[0]:
                   maxRet = ret
               # mergem in S
               ret = process((topLeft[0], hole[1] + 1),
                             botRight,
                             holes)
               if ret[0] > maxRet[0]:
                   maxRet = ret
               # mergem in W
               ret = process(topLeft,
                             (hole[0] - 1, botRight[1]),
                             holes)
               if ret[0] > maxRet[0]:
                   maxRet = ret
               # mergem in E
               ret = process((hole[0] + 1, topLeft[1]),
                             botRight,
                             holes)
               if ret[0] > maxRet[0]:
                   maxRet = ret

    if noHoles:
        # nu avem nicio gaura, returnam aria curenta
        maxRet = (area(topLeft, botRight), topLeft, botRight)
    return maxRet


def main(argc, argv):
    if argc < 3:
        print "Usage: %s LENGTH WIDTH [X Y]..."
        return 0

    length = int(argv[1])
    width = int(argv[2])
    holes = list()
    for i in xrange(3, argc, 2):
        holes.append((int(argv[i]), int(argv[i + 1])))

    (topLeft, botRight) = ((0, 0), (length - 1, width - 1))
    maxRet = process(topLeft, botRight, holes)
    print "Coordonate colt stanga sus: %d %d" % (maxRet[1][0], maxRet[1][1])
    print "Coordonate colt dreapta jos: %d %d" % (maxRet[2][0], maxRet[2][1])
    print "Arie: %d" % maxRet[0]

    return 0


if __name__ == "__main__":
     sys.exit(main(len(sys.argv), sys.argv))
