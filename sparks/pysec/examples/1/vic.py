#! /usr/bin/env python
#
# vic: intrusive, bad i/o example with potential security risks


import os
import random


FNAME = "secret.txt"


def save_pers(pers):
    # superuser task, needs sudo/administrator rights
    with open(FNAME, "w") as fout:
        for name in pers:
            fout.write("{} {} {}\n".format(name, pers[name],
                                           random.randint(0, 100)))
    os.chmod(FNAME, 0o600)


def main():
    pers = dict()    # people name -> age

    while True:
        # menu
        print "1. Display"
        print "2. Add"
        print "3. Save"
        print "0. Quit"

        # choose an option (this can also lead to a crash)
        qry = input(">>> ")

        if qry == 1:
            for name in pers:
                print "{}: {}".format(name, pers[name])
        elif qry == 2:
            name = raw_input("Name: ")
            age = input("Age: ")
            pers[name] = age
        elif qry == 3:
            save_pers(pers)
        elif qry == 0:
            break


if __name__ == "__main__":
    try:
        main()
    except Exception:
        pass
