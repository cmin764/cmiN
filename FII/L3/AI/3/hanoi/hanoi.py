#! /usr/bin/env python


import collections
import random
import sys
from queue import PriorityQueue


STACK = 1 << 13

FNAME = "hanoi.txt"
#FNAME = None


def _print(s, fout, score=None):
    data = "{}".format(" ".join(map(str, s)))
    if score:
        data += " - {}".format(score)
    fout.write(data + "\n")
    fout.flush()


def _final(s, n, final=None):
    if final:
        return s == final
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


def optrand(n, m, fout, init=None, final=None):
    # Stare initiala.
    s = init if init else [1] * m
    # Pana ajungem in stare finala.
    _print(s, fout)
    steps = 0
    while not _final(s, n, final=final):
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
    return _final(s, n, final=final)


def _backtrack(s, n, _, fout, states, final=None):
    # Mutarile pe care vreau sa le fac.
    moves = collections.deque()
    run = True
    count = 0

    while run:
        # Verificare stare finala.
        if _final(s, n, final=final):
            return True    # am gasit starea finala, ne oprim de tot

        # Generam toate mutarile posibile din starea curenta.
        for frm in sorted(set(s), reverse=True):
            for to in range(1, n + 1):
                if to == frm:
                    # Sarim peste starea constanta.
                    continue
                # O pereche de mutare posibila.
                moves.append((s[:], frm, to))

        # Incercam sa tranzitam intr-o stare urmatoare.
        status = False
        while not status:
            # Luam ultima mutare din coada, pe care vrem s-o facem.
            if not len(moves):
                # Am terminat toate posibilitatile, nu mai avem ce face.
                run = False
                break
            s, frm, to = moves.pop()
            status = _move(s, frm, to, fout)
            # Verificam statusul tranzitiei.
            if not status:
                # Nu s-a putut efectutat tranzitia, deci incercam cu
                # urmatoarea miscare.
                continue
            count += 1    # s-a efectuat
            if tuple(s) in states:
                # Am mai fost deja in aceasta stare, deci o sarim.
                # Ne mutam inapoi de unde am plecat si cautam o alta stare
                # posibila si valida.
                _move(s, to, frm, fout)
                count += 1    # mutarea inapoi
                status = False
            if count > STACK:
                return False

        # Am ajuns intr-o stare noua, o salvam si continuam cautarea.
        states.add(tuple(s))

    return False    # Nu am gasit nicio stare finala.


def backtrack(n, m, fout, init=None, final=None):
    s = init if init else [1] * m
    # Aici salvam stari anterioare pt. caching.
    states = set()
    states.add(tuple(s))
    # Printam pe cea initiala.
    _print(s, fout)
    # Incercam sa gasim o stare finala.
    # stare curenta, nr. tije, nr. discuri, output, cache
    return _backtrack(s, n, m, fout, states, final=final)


def _score(s, frm, to, states):
    try:
        state = _move(s, frm, to, None, show=False)
        if not state:
            return -1
        if tuple(s) in states:
            return 0
        return sum(idx + rod for idx, rod in enumerate(s))
    finally:
        if state:
            _move(s, to, frm, None, show=False)


def hillclimb(n, m, fout, init=None, final=None):
    s = init if init else [1] * m
    states = set()
    _print(s, fout, score=m)
    states.add(tuple(s))
    steps = 0
    while not _final(s, n, final=final):
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


def heuristic_estimation(state1,pegs,final_state):
    sum_final_state = sum([(i+1)*final_state[i] for i in range(len(final_state)-1)])
    sum_current_state = sum([(i + 1) * state1[i] for i in range(len(state1) - 1)])
    return (sum_final_state - sum_current_state)


def find_occurence(state,element):
    for i in state:
        if i == element:
            return state.index(i)
    return 0


def generate_neighbours(current_state,nr_rods):
    neighbour_list = []
    for disc in range(len(current_state)):
        for peg in range(1, nr_rods + 1):
            aux_state = []
            if current_state[disc] == peg:
                continue
            aux_state = list(current_state)
            aux_state[disc] = peg
            index_of_first = find_occurence(aux_state, peg)
            if disc > index_of_first:
                # print("discul :",disc,"mutare invalida :",current_state," to -> ",aux_state)
                continue
            else:
                 if aux_state not in neighbour_list:
                     neighbour_list.append(aux_state)
    # print("vecinii configuratiei : ",current_state," sunt:",neighbour_list)
    return neighbour_list


def equal_states(state1,state2):
    for i in range(len(state1)):
        if state1[i]<state2[i]:
            return -1
        else:
            return 1
    return 0


def a_star_main(start,goal,nr_rods, fout=None):
    # open_set = PriorityQueue()
    #set of nodes already evaluated
    closed_set = []
    goal_tuple = (0,[0,goal,None])

    current_state = (0,[0,start,None])
    # open_set.put(current_state)
    # closed_set.append(current_state)

    while current_state[1][1] != goal_tuple[1][1]:
        starts = current_state
        if equal_states(current_state[1],goal_tuple[1]) ==0:
            return closed_set
            # return open_set

        list_neighbours = generate_neighbours(current_state[1][1],nr_rods)
        secondary_set = PriorityQueue()
        for neighbour in list_neighbours:
            n_g = current_state[1][0]+1
            n_h = heuristic_estimation(neighbour,nr_rods,goal)
            n_f = n_g+n_h
            if neighbour in closed_set:
                continue
            else:
                secondary_set.put((n_h,[n_g,neighbour,current_state[1][1]]))
        current_state = secondary_set.get()
        state = current_state[1][1]
        closed_set.append(state)
        _print(state, fout)
        # print(" --am ales vecinul :",current_state," avand closed set :",closed_set,"\n")
        if current_state[1][0] > STACK:
            return None

    state = current_state[1][1]
    closed_set.append(state)
    _print(state, fout)
    return closed_set


def astar(n, m, fout, init=None, final=None):
    if m > n:
        n = m
    init = init or [1] * m
    final = final or [n] * m
    states = a_star_main(init, final, n, fout=fout)
    if not states:
        return False
    return True


def main(argv):
    if len(argv) not in range(4, 7):
        print("Usage: {} RODS DISKS ALGO [INIT [FINAL]]".format(argv[0]))
        return 1
    rods, disks = int(argv[1]), int(argv[2])
    algos = {
        "optrand": optrand,
        "backtrack": backtrack,
        "hillclimb": hillclimb,
        "astar": astar,
    }
    algo = algos.get(argv[3])
    if not algo:
        print("[x] Invalid algorithm")
        return 2

    init = final = None
    if len(argv) > 4:
        init = map(int, list(argv[4]))
    if len(argv) > 5:
        final = map(int, list(argv[5]))

    if FNAME:
        fout = open(FNAME, "w")
    else:
        fout = sys.stdout
    sys.setrecursionlimit(STACK)
    status = algo(rods, disks, fout, init=init, final=final)
    print(status)
    if FNAME:
        fout.close()
    if not status:
        return 3
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
