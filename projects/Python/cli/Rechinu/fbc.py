#! /usr/bin/env python3.1
# 21.11.2009 <> 21.11.2009 | cmiN
# Float Base Converter (console) 4 Rechinu @ rstcenter.com


import sys, decimal


def main():
    usage = """\t\t Float Base Converter 1.0

\t Usage: fbc.py float from to precision

Where float is a floating point number
      from is an integer [2, 36] representing the current base
      to is an integer [2, 36] representing the destination base
      precision is an integer

\t Example: fbc.py 1337.7331 10 2 100"""
    args = sys.argv
    if len(args) == 5:
        try:
            instance = Converter(args[1], args[2], args[3], args[4])
            instance.compute()
            print(instance.result)
        except Exception as message:
            print("An error occurred: {}".format(message))
        except:
            print("Unknown error.")
    else:
        print(usage)
    input()


class Converter:

    def __init__(self, number, current_base, destination_base, precision):
        self.result = ""
        self.nr = number
        self.cb = int(current_base)
        self.db = int(destination_base)
        self.pn = int(precision)
        self.charset = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                        "A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
                        "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
                        "U", "V", "W", "X", "Y", "Z"]

    def compute(self):
        decimal.getcontext().prec = self.pn
        parts = self.nr.split(".")
        wn = parts[0]
        if len(parts) > 1:
            point = True
            fn = parts[1]
        else:
            point = False
            fn = "0"
        if wn[0] == "-":
            negative = True
        else:
            negative = False
        wn = wn.strip("-").strip("+")
        wdn = decimal.Decimal("0")
        fdn = decimal.Decimal("0")
        p = 0
        for x in reversed(wn):
            wdn += decimal.Decimal(str(self.charset.index(x) * (self.cb ** p)))
            p += 1
        p = -1
        for x in fn:
            fdn += decimal.Decimal(str(self.charset.index(x) * (self.cb ** p)))
            p -= 1
        while int(wdn) != 0:
            r = int(wdn % self.db)
            wdn /= self.db
            self.result = self.charset[r] + self.result
        if point:
            self.result += "."
        while fdn != 0 and len(self.result) < self.pn + 1:
            fdn *= self.db
            self.result += str(int(fdn))
            fdn -= int(fdn)
        if negative:
            self.result = "-" + self.result


if __name__ == "__main__":
    main()
