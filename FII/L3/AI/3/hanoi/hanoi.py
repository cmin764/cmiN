#! /usr/bin/env python


import collections
import random
import sys


STACK = 1 << 13

FNAME = "hanoi.txt"
#FNAME = None


def _print(s, fout, score=None):
    data = "{}".format(" ".join(map(str, s)))
    if score:
        data += " - {}".format(score)
    fout.write(data + "\n")
    fout.flush()


def _final(s, n):
    return all(i == n for i in s)


def _move(s, frm, to, fout, show=True, score=None):
    fidx = tidx = 0
    for idx, rod in enumerate(s):
        if rod == frm and not fidx:
            fidx = idx + 1
        if rod == to and not tidx:
            tidx = idx + 1
        if fidx and tidx:
            break
    if tidx and fidx < tidx or not tidx:
        s[fidx - 1] = to
        if show:
            _print(s, fout, score=score)
        return True
    return False


def optrand(n, m, fout):
    # Stare initiala.
    s = [1] * m
    # Pana ajungem in stare finala.
    _print(s, fout)
    steps = 0
    while not _final(s, n):
        steps += 1
        if steps > STACK * n:
            return False
        frm = random.choice(s)
        while True:
            to = random.randint(1, n)
            if to != frm:
                break
        # Optimizare.
        move = False
        if frm == n:
            if s[-1] != frm:
                move = True
            else:
                flag = False
                for idx in range(m - 1, -1, -1):
                    if s[idx] != frm:
                        flag = True
                    if flag and s[idx] == frm:
                        move = True
                        break
        else:
            move = True
        # Executam tranzitia.
        if move:
            _move(s, frm, to, fout)
    return _final(s, n)


def _backtrack(s, n, _, fout, states):
    # Mutarile pe care vreau sa le fac.
    moves = collections.deque()
    run = True

    while run:
        # Verificare stare finala.
        if _final(s, n):
            return True    # am gasit starea finala, ne oprim de tot

        # Generam toate mutarile posibile din starea curenta.
        for frm in sorted(set(s)):
            for to in range(1, n + 1):
                if to == frm:
                    # Sarim peste starea constanta.
                    continue
                # O pereche de mutare posibila.
                moves.append((frm, to))

        # Incercam sa tranzitam intr-o stare urmatoare.
        status = False
        while not status:
            # Luam ultima mutare din coada, pe care vrem s-o facem.
            if not len(moves):
                # Am terminat toate posibilitatile, nu mai avem ce face.
                run = False
                break
            frm, to = moves.pop()
            status = _move(s, frm, to, fout)
            # Verificam statusul tranzitiei.
            if not status:
                # Nu s-a putut efectutat tranzitia, deci incercam cu
                # urmatoarea miscare.
                continue
            if tuple(s) in states:
                # Am mai fost deja in aceasta stare, deci o sarim.
                # Ne mutam inapoi de unde am plecat si cautam o alta stare
                # posibila si valida.
                _move(s, to, frm, fout)
                status = False

        # Am ajuns intr-o stare noua, o salvam si continuam cautarea.
        states.add(tuple(s))

    return False    # Nu am gasit nicio stare finala.


def backtrack(n, m, fout):
    s = [1] * m
    # Aici salvam stari anterioare pt. caching.
    states = set()
    states.add(tuple(s))
    # Printam pe cea initiala.
    _print(s, fout)
    # Incercam sa gasim o stare finala.
    # stare curenta, nr. tije, nr. discuri, output, cache
    return _backtrack(s, n, m, fout, states)


def _score(s, frm, to, states):
    try:
        state = _move(s, frm, to, None, show=False)
        if not state:
            return -1
        if tuple(s) in states:
            return 0
        return sum(rod for _, rod in enumerate(s))
    finally:
        if state:
            _move(s, to, frm, None, show=False)


def hillclimb(n, m, fout):
    s = [1] * m
    states = set()
    _print(s, fout, score=m)
    states.add(tuple(s))
    steps = 0
    while not _final(s, n):
        steps += 1
        if steps > STACK * n:
            return False
        scores = []
        for frm in set(s):
            for to in range(1, n + 1):
                if to == frm:
                    continue
                score = _score(s, frm, to, states)
                if score >= 0:
                    scores.append((frm, to, score))
        scores.sort(key=lambda arg: arg[2], reverse=True)
        frm, to, score = scores[0]
        if not score:
            return False
        _move(s, frm, to, fout, score=score)
        states.add(tuple(s))
    return _final(s, n)


def main(argv):
    if len(argv) != 4:
        print("Usage: {} RODS DISKS ALGO".format(argv[0]))
        return 1
    rods, disks = int(argv[1]), int(argv[2])
    algos = {
        "optrand": optrand,
        "backtrack": backtrack,
        "hillclimb": hillclimb,
        "astar": None,    # TODO(cmiN): implementation
    }
    algo = algos.get(argv[3])
    if not algo:
        print("[x] Invalid algorithm")
        return 2

    if FNAME:
        fout = open(FNAME, "w")
    else:
        fout = sys.stdout
    sys.setrecursionlimit(STACK)
    status = algo(rods, disks, fout)
    print(status)
    if FNAME:
        fout.close()
    if not status:
        return 3
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
