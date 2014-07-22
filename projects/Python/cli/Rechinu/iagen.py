#! /usr/bin/env python3.2
# ISK/APV Converter
# 17.01.2011 cmiN

from os import system

class IA:
    def __init__(self, string, mode):
        self.output = None
        self.ichars = list()
        for i in range(0, len(string), 2):
            self.ichars.append(string[i:i + 2])
        self.mode = mode
        self.clists = (("3", "C"), ("3", "B"), ("B", "C"), (), ("3", "6", "7"), ("1", "3", "C", "E", "F"))
        self.cstarts = ("2D", "D7", "14", "24", "5C", "00")
        self.seqlists = (((-8, -1, -2, -4), (8, 1, 2, 4)), ((8, -1, 2, -4), (-8, -1, -2, -4)),
                         ((8, 1, 2, -4), (8, -1, 2, 4)), ((8, 1, -2, -4), (8, 1, 2, 4)),
                         ((-8, 1, 2, -4), (8, -1, 2, -4)), ((8, 1, 2, 4), (8, 1, 2, 4)))
        self.hexa = lambda nr: hex(nr).replace("0x", "").upper()

    def swap(self, pos):
        if pos == "x":
            return "y"
        else:
            return "x"

    def generate_vector(self, pos, cstart, sequence):
        charset = [int(cstart, 16)]
        while True:
            length = len(charset)
            if length == 1:
                i = 0
            elif length == 2:
                i = 1
            elif length == 4:
                i = 2
                pos = self.swap(pos)
            elif length == 8:
                i = 3
                pos = self.swap(pos)
            else:
                return charset
            if pos == "x":
                nr = 16
            else:
                nr = 1
            for c in charset[:]:
                charset.append(c + sequence[i] * nr)

    def convert_char(self, mode, clist, cstart, seqlist, ichar):
        xvec = self.generate_vector("y", cstart, seqlist[0])
        yvec = self.generate_vector("x", cstart, seqlist[1])
        if mode == "ia":
            x = ichar[0]
            y = ichar[1]
            if x in clist:
                return "xx"
            else:
                return self.hexa(xvec[int(x, 16)] + yvec[int(y, 16)] - int(cstart, 16)).zfill(2)
        else:
            flag = False
            for x in range(16):
                for y in range(16):
                    if self.hexa(xvec[x] + yvec[y] - int(cstart, 16)).zfill(2) == ichar:
                        flag = True
                        break
                if flag:
                    break
            if (not flag) or (self.hexa(x) in clist):
                return "xx"
            else:
                return self.hexa(x) + self.hexa(y)
            
    def convert_string(self):
        self.output = str().join([self.convert_char(self.mode, self.clists[i], self.cstarts[i], self.seqlists[i], self.ichars[i]) for i in range(6)])
                    
def main():
    while True:
        system("cls")
        print("[1] ISK -> APV", "[2] ISK <- APV", "[0] Exit", sep="\n")
        ans = int(input("Choose: "))
        if ans in (1, 2):
            if ans == 1:
                mode = "ia"
            else:
                mode = "ai"
            string = input("In: ").upper()
            status = True
            hexlist = [hex(i).replace("0x", "").upper() for i in range(16)]
            if len(string) != 12:
                status = False
            for c in string:
                if not (c in hexlist):
                    status = False
            if status:
                aiobj = IA(string, mode)
                aiobj.convert_string()
                print("Out: " + aiobj.output)
            else:
                print("Invalid input.")
        elif ans == 0:
            return 0
        else:
            print("Invalid choice.")
        system("pause")

if __name__ == "__main__":
    main()
