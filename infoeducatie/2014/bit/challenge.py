#!/usr/bin/env python


# pylint: disable=invalid-name
import base64
import re

import roman
from pygenere import Vigenere


DEBUG = True


def debug(message):
    """Print debug message"""
    if DEBUG:
        print("[D] {}".format(message))


def encrypt1(message):
    """Transform fiecare litera in valoare ei ascii."""
    return ", ".join([str(ord(letter)) for letter in message])


def decrypt1(message):
    """Construiesc textul din valori ascii."""
    return "".join([chr(int(letter)) for letter in message.split(', ')])


def encrypt2(message, key='Nehalem'):
    """Encriptam mesajul cu Vigenere."""
    return Vigenere(message).encipher(key)


def decrypt2(message, key='Nehalem'):
    """Decriptam mesajul folosind Vigenere."""
    return Vigenere(message).decipher(key)


def encrypt3(message):
    """Reprezentarea valorii ascii in sistem roman."""
    return ", ".join([roman.toRoman(ord(letter)) if ord(letter) else "O"
                      for letter in message])


def decrypt3(message):
    """Obtinem valorile ascii din sistemul roman."""
    return "".join([chr(roman.fromRoman(letter)) if letter != "O" else chr(0)
                    for letter in message.split(', ')])


def encrypt4(message, key='Sandy Bridge'):
    """Face xor cu fiecare caracter pe baza sumei valorilor
    numerelor ASCII ale fiecarui caracter din cheie.
    """
    total = sum([ord(x) for x in key]) % 256
    return "".join(chr(ord(x) ^ total) for x in message)


def decrypt4(message):
    return encrypt4(message)


raspuns = ("Felicitari! Cauta omul cu busola si spune-i `Dude your life's an "
           "open book, don't close it before it's done`. Apoi convinge-l "
           "sa-ti dea busola si livreaz-o lui CVIA.")
raspuns = base64.b64encode(raspuns)

key1 = raspuns[0:55]
key2 = raspuns[55:110]
key3 = raspuns[110:165]
key4 = raspuns[165:220]

plain1 = "`Nehalem`: `{}`".format(key1)
#debug(plain1)
plain2 = "`Westmere`: `{}`".format(key2)
#debug(plain2)
plain3 = "`Sandy Bridge`: `{}`".format(key3)
#debug(plain3)
plain4 = "`Ivy Bridge`: `{}`".format(key4)
#debug(plain4)


T = "\n\n"
container = encrypt1(
    plain1 + T + encrypt2(plain2 + T +
                               encrypt3(plain3 + T + encrypt4(plain4))))


text = "Bine ai venit. Tot ce ai nevoie se gaseste aici:\n{}".format(container)
print(text)

values = decrypt1(container).split(T)
p1 = values[0]
e1 = T.join(values[1:])
values = decrypt2(e1).split(T)
p2 = values[0]
e2 = T.join(values[1:])
values = decrypt3(e2).split(T)
p3 = values[0]
e3 = T.join(values[1:])
p4 = decrypt4(e3)

total = "".join([re.search(r": `([^`]+)`", text).group(1) for text in [p1, p2, p3, p4]])
debug(base64.b64decode(total))
