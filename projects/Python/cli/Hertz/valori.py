#! /usr/bin/env python
# 09.08.2009 <> 09.08.2009 | cmiN
# Challenge [Programare] Valori (Hertz) @ rstcenter.com


def main():
    string = "93752xxx746x27x1754xx90x93xxxxx238x44x75xx08750912738x8461x8759383xx328x4x4935903x6x5550360535004x0xx945958961296x267x8842xxx5x6xx61x4x48482x80xxx83316843x7x4x83x9521731xxx25x51xx457x6x5x9698222x771237745034x5133592x27xx8x87xx35221x36x0x50x23x7x63x998418xx"
    strlist = list(string)
    strsum, x = 0, 0
    while True:
        try:
            item = strlist[x]
        except:
            break
        if item == "x":
            strlist.remove("x")
            x -= 2
        else:
            strsum += int(item)
            x += 1
    input("The string value is %s." % str(strsum))


if __name__=="__main__":
    main()
