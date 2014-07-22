#! /usr/bin/env python


import sys


def check(edge, cycles):
    if cycles[edge[0]] == cycles[edge[1]]:
        return False    # creeaza ciclu
    return True    # uneste apm-uri diferite


def update(edge, cycles):
    # Fiecare nod ce are eticheta mare
    # primeste eticheta mica, unde etichetele
    # se determina din capetele muchiei introduse.

    little = min(cycles[edge[0]], cycles[edge[1]])
    big = max(cycles[edge[0]], cycles[edge[1]])

    for item in cycles.iteritems():
        if item[1] == big:
            cycles[item[0]] = little


def kruskal(edges):
    # sortam muchiile
    edgesKeys = sorted(edges, reverse=True,
                       key=lambda arg: edges[arg])

    # cream structura de ciclicitate
    cycles = dict()
    for edge in edgesKeys:
        cycles[edge[0]] = edge[0]
        cycles[edge[1]] = edge[1]

    apm = dict()
    for edge in edgesKeys:
        if not check(edge, cycles):
            continue    # creeaza ciclu
        # o selectam
        apm[edge] = edges[edge]
        update(edge, cycles)

    return apm


def main(argc, argv):
    if argc < 4 or (argc - 1) % 3:
        print "Usage: %s (NODEA NODEB COST)..." % argv[0]
        return 0

    edges = dict()
    for i in xrange(1, argc, 3):
        edges[(int(argv[i]), int(argv[i + 1]))] = float(argv[i + 2])

    apm = kruskal(edges)
    totalCost = sum(apm.itervalues())
    print "Cost total: %.2f" % totalCost
    print "Muchiile: %s" % ", ".join(["%d %d" % edge\
                                      for edge in apm.iterkeys()])

    return 0


if __name__ == "__main__":
    sys.exit(main(len(sys.argv), sys.argv))
