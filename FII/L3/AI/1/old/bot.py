#! /usr/bin/env python


import random


DIM = 2
FNAME = "bot.txt"
SEP = "|"
USERS = {
    0: ("Cosmin Poieana", 23, "Programator"),
    1: ("Adrian Oprea", 22, "Student")
}
USERS = None


def detail(name, age, ocp, dnr):
    if dnr == 0:
        return name
    if dnr == 1:
        return age
    return ocp


def load():
    with open(FNAME, "r") as stream:
        data = stream.read()
    qes = {}
    for line in data.splitlines():
        line = line.strip()
        if not line:
            continue
        unr, dnr, qe = line.split(SEP)
        unr, dnr = int(unr), int(dnr)
        qes.setdefault(unr, []).append((dnr, qe))
    return qes


def main():
    if USERS:
        users = USERS
    else:
        users = {}
        print("Date pentru {} utilizatori...".format(DIM))
        for i in range(DIM):
            print("Utilizator #{}".format(i + 1))
            name = raw_input("Nume: ")
            age = int(raw_input("Varsta: "))
            ocp = raw_input("Ocupatie: ")
            users[i] = (name, age, ocp)

    qes = load()
    while True:
        unr = random.randint(0, DIM - 1)
        dnr = random.randint(0, 2)
        name, age, ocp = users[unr]
        qe = qes[unr]
        qnr = random.randint(0, len(qe) - 1)
        dnr, q = qe[qnr]
        print("#{} ".format(unr + 1) + q.format(detail(name, age, ocp, dnr)))
        raw_input("...")


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        pass
