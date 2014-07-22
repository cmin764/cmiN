#! /usr/bin/env python


import re


fname = "cnp.txt"


def valid(cnp):
    # 1 93 04 26 39 4424
    # 0 1  3  5  7  9
    ss = cnp[0]
    aa = cnp[1:3]
    ll = cnp[3:5]
    zz = cnp[5:7]
    rr = cnp[9:]
    if not ss in (1, 2):
        return False
    # ....
    return True


def main():
    tmp = list()
    template = r"\d{13}"
    reTemp = re.compile(template)

    with open(fname) as fin:
        for line in fin:
            tmp.extend([int(cnp) for cnp in\
                reTemp.findall(line.strip())])
    
    cnps = filter(valid, tmp)
    del tmp

    for cnp in cnps:
        print cnp


if __name__ == "__main__":
    main()
