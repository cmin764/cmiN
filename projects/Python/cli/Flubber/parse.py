#! /usr/bin/env python
## Some parsing xD 4 Flubber
## 28.11.2011 cmiN


from sys import stdin, stdout


METHO = 1 # 1 or 2
DELIM = "**"
#stdin = "input.txt" # pot fi comentate pentru
#stdout = "output.txt" # a citi din standard


def func1():
    for line in stdin:
        stdout.write(" ".join(["{0}{1}{0}{2}".format(DELIM, group[:2], group[2:]) for group in line.strip().split()]) + "\n")


def func2():
    cargo = stdin.read(2)
    while cargo != "":
        stdout.write(DELIM + cargo)
        cargo = stdin.read(2)
        if cargo != "" and '\n' == cargo[0]:
            stdout.write('\n')
            cargo = cargo[1:] + stdin.read(1)


def main():
    global stdin, stdout
    cond = type(stdin) == str and type(stdin) == str
    if cond: # use file instead of standard
        stdin = open(stdin, "rt")
        stdout = open(stdout, "wt")
    if METHO == 1: # method
        func1()
    else:
        func2()
    stdin.close()
    stdout.close()


if __name__ == "__main__":
    main()
