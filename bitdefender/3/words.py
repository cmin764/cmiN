#! /usr/bin/env python
# -*- coding: UTF-8 -*-


import sys
import os
import re
import string


def validate(word):
    cnt = word.count("'")
    if cnt > 1:
        return None
    if cnt and word.find("'") != len(word) - 1:
        return None
    if word.startswith("-") or word.endswith("-"):
        return None
    return word


def parse(path):
    words = dict()
    chars = dict()
    
    a = r"(^(?P<first>[-'a-zA-Z]+)(?=(\s+|[.?,!:;"
    b = r'")(]+))|(\s+|[.?,!:;")(]+)(?P<second>[-'
    c = r"'a-zA-Z]+)(?=(\s+|[.?,!:;"
    d = r'")(]+)))'
    pattern = a + b + c + d
    rePat = re.compile(pattern)

    fobj = open(path)
    for line in fobj:
        line = line.strip()
        for char in line:
            if char in string.ascii_letters:
                chars[char] = chars.setdefault(char, 0) + 1
        for regex in rePat.finditer(line):
            posib = regex.groupdict().values()
            word = validate(posib[0] or posib[1])
            if word:
                words[word] = words.setdefault(word, 0) + 1
    fobj.close()

    return (chars, words)



def keep_max(topCat):
    if len(topCat) < 4:
        return
    catKeys = sorted(topCat, reverse=True,
                     key=lambda arg: topCat[arg])
    topCat.pop(catKeys[-1])


def show(path, chars, words):
    keyChars = sorted(chars, reverse=True,
                      key=lambda arg: chars[arg])
    keyWords = sorted(words, reverse=True,
                      key=lambda arg: words[arg])

    catNr = 0
    topCat = dict()
    for cat in keyWords:
        for i in xrange(1, len(cat) - 1):
            first, second = cat[:i], cat[i:]
            if first in words and second in words:
                #print "%s = %s + %s" % (cat, first, second)
                catNr += 1
                topCat[cat] = words[cat]
                keep_max(topCat)

    print "File: %s" % os.path.split(path)[1]
    print "C: %s %d" % (keyChars[0], chars[keyChars[0]])
    print "W: %s %d" % (keyWords[0], words[keyWords[0]])
    print "Cat: %d" % catNr
    for key in sorted(topCat, reverse=True,
                      key=lambda arg: topCat[arg]):
        print "%s: %d" % (key, topCat[key]),
    print ""
    sys.stdout.flush()


def main(argc, argv):
    if argc == 1:
        print "Usage: %s FILE..." % argv[0]
        return 0

    for path in argv[1:]:
        if not os.path.isfile(path):
            print "Error: invalid file %s" % path
            return 1
        (chars, words) = parse(path)
        show(path, chars, words)

    return 0


if __name__ == "__main__":
    sys.exit(main(len(sys.argv), sys.argv))
