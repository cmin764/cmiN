#!/usr/bin/env python

# pylint: disable=invalid-name
import base64

import roman
from pycipher import Caesar, SimpleSubstitution
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
    return ", ".join([roman.toRoman(ord(letter)) for letter in message])


def decrypt3(message):
    """Obtinem valorile ascii din sistemul roman."""
    return "".join([chr(roman.fromRoman(letter))
                    for letter in message.split(', ')])


def encrypt4(message, key='a'):
    """."""


raspuns = ("Felicitari! Cauta omul cu busola si spunei `Dude your life's an "
           "open book, don't close it before it's done`. Apoi convinge-l"
           "sa-ti dea busola si livreaz-o lui CVIA.")
raspuns = base64.b64encode(raspuns)

key1 = raspuns[0:55]
key2 = raspuns[55:110]
key3 = raspuns[110:165]
key4 = raspuns[165:220]

plain1 = "`Nehalem`: `{}`".format(key1)
debug(plain1)
plain2 = "`Westmere`: `{}`".format(key2)
debug(plain2)
plain3 = "`Sandy Bridge`: `{}`".format(key3)
debug(plain3)
plain4 = "`Ivy Bridge`: `{}`".format(key4)
debug(plain4)
container = encrypt1(
    plain1 + "\n\n" + encrypt2(plain2 + "\n\n" +
                               encrypt3(plain3 + "\n\n" + encrypt4(plain4))))

a = encrypt4(plain4)
b = encrypt4(a)

debug(a)
debug(b)

# debug(decrypt1(container))
#text = "Bine ai venit. Tot ce ai nevoie se gaseste aici: {}".format(container)
# print(text)
