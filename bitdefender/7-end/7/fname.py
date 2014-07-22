#! /usr/bin/env python
# Bullshit


NUM = 1321528399
output = list()
fname = "gdt_test.exe"


def binfull(nr, length):
    return bin(nr).replace("0b", "").zfill(length)


fin = open(fname, "rb")
fin.seek(0, 2)
size = fin.tell()

while size > 0:
    bits = binfull(size * NUM, 64)
    sup = int(bits[:32], 2) / 8
    value = sup + (1 if sup < 0 else 0)
    short = binfull(value, 32)[-8:]
    short = int(short, 2) * 26
    chunk = int(binfull(size, 32)[-8:], 2) - short
    chunk += 97
    output.append(chr(chunk))
    size = value

print "".join(output)

fin.close()
