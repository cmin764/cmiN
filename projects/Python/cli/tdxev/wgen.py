#! /usr/bin/env python
# 09.10.2010 <> 09.10.2010 | cmiN
# wordGenerator 4 tdxev @ rstcenter.com

def main():
    charset = raw_input("Enter charset: ")
    line = int(raw_input("Line: "))
    base = len(charset)
    result = 0
    exponent = 0
    genstr = ""
    while result < line:
        exponent += 1
        result += base ** exponent
    result -= base ** exponent
    for e in xrange(exponent - 1, -1, -1):
        pos = -1
        while result < line:
            result += base ** e
            pos += 1
        result -= base ** e
        genstr += charset[pos]
    print genstr

if __name__ == "__main__":
    main()
