#! /usr/bin/env python3.1
# 05.04.2010 <> 06.04.2010 | cmiN
# Text In Bmp (console)

import sys
from hashlib import md5

class Image:

    def load(self, path):
        with open(path, "rb") as file:
            buffer = file.read()
        self.bfType = buffer[0:2]
        if self.bfType != b"BM":
            raise Exception("not a bitmap")
        self.bfSize = buffer[2:6]
        self.bfReserved1 = buffer[6:8]
        self.bfReserved2 = buffer[8:10]
        self.bfOffBits = buffer[10:14]
        self.biSize = buffer[14:18]
        self.biWidth = buffer[18:22]
        self.biHeight = buffer[22:26]
        self.biPlanes = buffer[26:28]
        self.biBitCount = buffer[28:30]
        if baconvert(self.biBitCount) != 24:
            raise Exception("not 24-bit")
        self.biCompression = buffer[30:34]
        self.biSizeImage = buffer[34:38]
        self.biXPelsPerMeter = buffer[38:42]
        self.biYPelsPerMeter = buffer[42:46]
        self.biClrUsed = buffer[46:50]
        self.biClrImportant = buffer[50:54]
        self.bHeader = buffer[:54]
        self.bMatrix = list(buffer[54:])

    def create(self, path, buffer):
        with open(path, "wb") as file:
            file.write(buffer)

def process(digsig, mode, infile, outfile=None, string=None):
    bmp = Image()
    bmp.load(infile)
    bmp.width = baconvert(bmp.biWidth)
    bmp.height = baconvert(bmp.biHeight)
    bmp.index = 0
    bmp.count = 0
    rem = (bmp.width * 3) % 4
    if rem:
        bmp.padding = 4 - rem
    else:
        bmp.padding = 0
    if mode == "write":
        bits = str()
        for char in md5(bytes(digsig, "ascii")).digest():
            bits += bin(char).replace("0b", "").zfill(8)
        bits += bin(len(string)).replace("0b", "").zfill(16)
        for char in string:
            bits += bin(ord(char)).replace("0b", "").zfill(8)
        if len(bits) > bmp.width * bmp.height * 3:
            raise Exception("string too long")
        for bit in bits:
            char = bin(bmp.bMatrix[bmp.index])
            char = int(char[:-1] + bit, 2)
            bmp.bMatrix[bmp.index] = char
            bmp.index += 1
            bmp.count += 1
            if bmp.count == (bmp.width * 3):
                bmp.count = 0
                bmp.index += bmp.padding
        bmp.create(outfile, bmp.bHeader + bytes(bmp.bMatrix))
    elif mode == "read":
        bits = bitjoin(bmp, 128)
        if bytes([int(bits[i:i + 8], 2) for i in range(0, 128, 8)]) == md5(bytes(digsig, "ascii")).digest():
            nr = int(bitjoin(bmp, 16), 2) * 8
            bits = bitjoin(bmp, nr)
            string = "".join([chr(int(bits[i:i + 8], 2)) for i in range(0, nr, 8)])
            print(string)
        else:
            raise Exception("invalid signature")
    else:
        raise Exception("invalid mode")

def bitjoin(bmp, nr):
    bits = str()
    for i in range(nr):
        bits += bin(bmp.bMatrix[bmp.index])[-1]
        bmp.index += 1
        bmp.count += 1
        if bmp.count == (bmp.width * 3):
            bmp.count = 0
            bmp.index += bmp.padding
    return bits
        
def baconvert(buffer):
    return int("".join([hex(char).replace("0x", "").zfill(2) for char in reversed(buffer)]), 16)

def main(args):
    usage = """\t\t Text In Bmp 1.0

\t Usage: source.ext digsig mode infile [outfile text]

Where digsig is a digital signature string
      mode can be write or read
      infile is a valid 24-bit bitmap image
      outfile is the output image name (used with write mode)
      text is the string that will be written in image (used with write mode)

\t Example: tib.py cmiN write image1.bmp image2.bmp http://rstcenter.com
\t          tib.py cmiN read image2.bmp"""
    try:
        print("Please wait...")
        if len(args) == 4:
            process(args[1], args[2], args[3])
        elif len(args) == 6:
            process(args[1], args[2], args[3], args[4], args[5])
        else:
            print(usage)
    except Exception as message:
        print("An error occurred: {}".format(message))
    except:
        print("Unknown error.")
    else:
        print("Ready!")

if __name__ == "__main__":
    main(sys.argv)
