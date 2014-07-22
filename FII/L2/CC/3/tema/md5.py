#! /usr/bin/env python


import math
from hashlib import md5
from binascii import hexlify, unhexlify


# generate 64 keys
KEYS = [int(math.floor(abs(math.sin(i + 1)) * 2 ** 32))
        for i in xrange(64)]

SHIFT = (
    7, 12, 17, 22, 7, 12, 17, 22,
    7, 12, 17, 22, 7, 12, 17, 22,
    5,  9, 14, 20, 5,  9, 14, 20,
    5,  9, 14, 20, 5,  9, 14, 20,
    4, 11, 16, 23, 4, 11, 16, 23,
    4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21,
    6, 10, 15, 21, 6, 10, 15, 21
)


def ovf(number, size=32):
    """Simulate an overflow."""
    nrmax = 2 ** size
    if number >= nrmax:
        number -= nrmax
    return number


def rotate(number, way, size=32):
    """Rotates a list of bits.
    negative - to the left
    positive - to the right
    """
    bitlist = list(bin(number).replace("0b", "").zfill(size))
    count = abs(way)
    if way < 0:
        for _ in xrange(count):
            bitlist.append(bitlist.pop(0))
    elif way > 0:
        for _ in xrange(count):
            bitlist.insert(0, bitlist.pop(-1))
    return int("".join(bitlist), 2)


def N(nr):
    """Unsigned int bitwise not."""
    return ~nr & 0xFFFFFFFF


def str2bit(text):
    if not text:
        return []
    size = len(text) * 8
    bstr = bin(int(hexlify(text), 16)).replace("0b", "").zfill(size)
    return list(bstr)


def lendian(number, size=32):
    """Returns the little endian representation of a number."""
    _size = size / 8 * 2
    hrepr = hex(number).rstrip("Ll").replace("0x", "").zfill(_size)
    ret = list()
    for pos in xrange(0, _size, 2):
        ret.insert(0, hrepr[pos:pos + 2])
    return int("".join(ret), 16)


class MD5(object):

    def __init__(self, msg):
        self.msghash = list()
        self._process(str2bit(msg))

    def _process(self, msg):
        # IV
        h0 = 0x67452301
        h1 = 0xefcdab89
        h2 = 0x98badcfe
        h3 = 0x10325476
        # append metadata to the message
        lgt = len(msg)
        msg.append("1")
        total = len(msg) % 512
        if total <= 448:
            total = 448 - total
        else:
            total = 448 + 512 - total
        msg.extend(["0"] * total)
        msg.extend(list(bin(lendian(lgt % 2 ** 64, size=64))
            .replace("0b", "").zfill(64)))
        # preprocess
        for mpos in xrange(0, len(msg), 512):
            chunk = msg[mpos:mpos + 512]
            # break it into 16x32 words
            words = list()
            for wpos in xrange(16):
                word = "".join(chunk[wpos * 32:(wpos + 1) * 32])
                words.append(lendian(int(word, 2)))
            # init hash values
            a = h0
            b = h1
            c = h2
            d = h3
            # 64 rounds
            for i in xrange(64):
                if i < 16:
                    f = (b & c) | (N(b) & d)
                    g = i
                elif i < 32:
                    f = (d & b) | (N(d) & c)
                    g = (5 * i + 1) % 16
                elif i < 48:
                    f = b ^ c ^ d
                    g = (3 * i + 5) % 16
                else:
                    f = c ^ (b | N(d))
                    g = (7 * i) % 16
                tmp = d
                d = c
                c = b
                b = ovf(b + rotate(ovf(ovf(a + f) + ovf(KEYS[i] + words[g])),
                                   SHIFT[i] * -1))
                a = tmp
            h0 = ovf(h0 + a)
            h1 = ovf(h1 + b)
            h2 = ovf(h2 + c)
            h3 = ovf(h3 + d)
        for dword in (h0, h1, h2, h3):
            dword = list(bin(lendian(dword)).replace("0b", "").zfill(32))
            for pos in xrange(0, 32, 8):
                byte = dword[pos:pos + 8]
                self.msghash.append(int("".join(byte), 2))
        self.msghash = "".join(map(chr, self.msghash))

    def digest(self):
        return self.msghash

    def hexdigest(self):
        return hexlify(self.digest())


def main():
    plains = [
        "Ana are mere!",
        "test",
        " ",
        "",
        "a" * 64 + "b" * 65 
    ]
    for plain in plains:
        myhash = MD5(plain).hexdigest()
        their = md5(plain).hexdigest()
        print myhash, their
        assert myhash == their


if __name__ == "__main__":
    main()
