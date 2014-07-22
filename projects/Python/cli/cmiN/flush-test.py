#! /usr/bin/env python
# Testing "tool" for popen, fork, exec, system, etc
# 12.04.2012 cmiN


import sys
from time import ctime, sleep
from subprocess import call


# some miscellaneous
clear = lambda: call(["clear" if "linux" in sys.platform else "cls"])
flush = [lambda: sys.stdout.flush(), lambda: sys.stderr.flush()]


def mode1():
    """Used only for output."""
    for i in xrange(10):
        print i
        #flush[0]()
        #flush[1]()
        # as you can see there is no flush
        sleep(2)


def mode2():
    """For both input and output."""
    menu = ["1) Quit",
            "2) Show date and time"]
    data = "\n".join(menu) # preserve beauty for large lists
    while True:
        print data
        flush[0]()
        flush[1]()
        try:
            op = int(raw_input("Option: "))
        except ValueError:
            op = 0
        #print "after" # odd
        flush[0]()
        if op == 1:
            break
        elif op == 2:
            print ctime()
        else:
            sys.stderr.write("You mothafucka -,-.\n")
        # flush data right after it's printed again
        flush[0]()
        flush[1]()
        raw_input() # pause
        clear()


def main(argv):
    if len(argv) != 2:
        print "Usage: %s mode" % argv[0]
        print "\nModes:\n    1    stdout only\n    2    full i/o"
        return
    try:
        mode = int(argv[1])
    except ValueError:
        mode = 0
    if mode == 1:
        mode1()
    elif mode == 2:
        mode2()
    else:
        print "Invalid mode."


if __name__ == "__main__":
    main(sys.argv)
