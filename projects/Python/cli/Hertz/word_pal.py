#! /usr/bin/env python3.1


import sys


def main(words):
    for word in words[1:]:
        if word == word[::-1]:
            print(True)
        else:
            print(False)


if __name__ == "__main__":
    main(sys.argv)
