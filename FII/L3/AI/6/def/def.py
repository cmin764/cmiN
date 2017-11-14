#! /usr/bin/env python


import json
import logging
import re
import sys

import addict


DEBUG = True

class PATHS:
    # Expresii regulate folosite ca input pentru gasirea potrivirilor.
    REGEX = "regex.json"
    # Aici punem definitiile extrase ca output.
    DEFS = "output.txt"
    # Fisier de intrare continand cuvintele sau expresiile ce
    # trebuiesc a fi gasite.
    PHRASES = "phrases.txt"


def regex_generator():
    # Incarcam lista de cuvinte/expresii sub forma de lista.
    with open(PATHS.PHRASES, "r") as stream:
        phrases = stream.read().strip().splitlines()
        phrases.sort(key=lambda arg: len(arg), reverse=True)
    # Incarcam structura de expresii regulate.
    with open(PATHS.REGEX, "r") as stream:
        regex = addict.Dict(json.load(stream))
    # Combinam cuvintele cu expresiile de mai sus si intoarcem
    # o versiune compilata de expresie regulata pentru fiecare
    # combinatie.
    make_regex = lambda elems: r"|".join(elems)
    prefix = make_regex(phrases)
    middle = make_regex(regex.middles)
    suffix = make_regex(regex.suffixes)
    for expr in regex.expressions:
        reg_expr = expr.format(prefix=prefix, middle=middle, suffix=suffix)
        logging.debug("Regex: %r", reg_expr)
        yield re.compile(reg_expr, re.IGNORECASE)


def find_defs(text):
    # Dictionar de definitii.
    definitions = {}
    # Pentru fiecare expresie generata.
    for regex in regex_generator():
        # Vedem ce potriviri avem.
        for match in regex.finditer(text):
            # Extragem cuvantul, definitia si offsetul.
            word, defn = map(match.group, ("word", "defn"))
            offset = match.start()
            # Si le adaugam in dictionarul de definitii.
            logging.debug("Definition: %r %r %s", word, defn, offset)
            definitions.setdefault(word, set()).add((defn.strip(), offset))

    # Salvam dictionarul in fisierul de iesire.
    template = "{}: {} ({})\n"
    with open(PATHS.DEFS, "w") as stream:
        for word, defs in definitions.items():
            for defn, offset in defs:
                line = template.format(word, defn, offset)
                stream.write(line)


def main():
    level = logging.DEBUG if DEBUG else logging.INFO
    logging.basicConfig(level=level)

    if len(sys.argv) < 2:
        print("Usage: {} INPUT".format(sys.argv[0]))
        return

    with open(sys.argv[1], "r") as stream:
        text = stream.read().strip()
    find_defs(text)


if __name__ == "__main__":
    main()
