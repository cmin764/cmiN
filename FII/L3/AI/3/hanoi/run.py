#! /usr/bin/env python


import random
import subprocess
import sys
import time


H_SCRIPT = "hanoi.py"
H_OUTPUT = "hanoi.txt"

R_OUTPUT = "run.txt"
#R_OUTPUT = None

ALGOS = [
    "optrand",
    "backtrack",
    "hillclimb",
    "astar",
]

RODS_RANGE = (3, 9)
DISKS_RANGE = (3, 9)


def log(string):
    string += "\n"
    stream = open(R_OUTPUT, "a") if R_OUTPUT else sys.stdout
    stream.write(string)
    stream.flush()


def main(argv):
    if len(argv) != 2:
        print("Usage: {} TESTS".format(argv[0]))
        return 1
    nr = int(argv[1])
    log(time.ctime())
    log("")

    params = []
    for _ in range(nr):
        rods = str(random.randint(*RODS_RANGE))
        disks = str(random.randint(*DISKS_RANGE))
        params.append((rods, disks))

    for algo in ALGOS:
        deltas = []
        steps_list = []
        for idx in range(nr):
            rods, disks = params[idx]
            if algo == "astar":
                rods, disks = "3", "3"
            print("Running test #{} for {!r} - {} x {}"
                    .format(idx + 1, algo, rods, disks))
            start = time.time()
            pop = subprocess.Popen(["python", H_SCRIPT, rods, disks, algo])
            rcode = pop.wait()
            delta = time.time() - start
            deltas.append(delta if not rcode else -1)
            with open(H_OUTPUT, "r") as stream:
                steps = len(stream.readlines())
            if not rcode:
                steps_list.append(steps)
        good = filter(lambda delta: delta != -1, deltas)
        log(algo)
        log("Success rate: {}/{}".format(len(good), len(deltas)))
        if len(good):
            log("Average steps: {}".format(sum(steps_list) / len(steps_list)))
            log("Average time: {}".format(sum(good) / len(good)))
        log("")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
