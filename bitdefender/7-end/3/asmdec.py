#! /usr/bin/env python


toDecrypt = "@rb|e} co|vud0:D"


def func(ind, char):
    nr = 0
    if not ind % 2:
        nr = 16
    return ord(char) ^ nr


def main():
    decrypted = list()
    for ind in xrange(len(toDecrypt)):
        decrypted.append(func(ind, toDecrypt[ind]))
    print "".join([chr(asc) for asc in decrypted])


if __name__ == "__main__":
    main()
