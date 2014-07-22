#! /usr/bin/env python


"""qrand: creeaza variante aleatoare de teste grila

Fisierul de intrare trebuie sa respecte un format destul de simplu:
    - fiecare intrebare trebuie sa contina cel putin un raspuns
    - intrebarile sunt prefixate de un numar, apoi punct si unul sau mai multe spatii
    - raspunsurile sunt prefixate de o litera, apoi paranteza rotunda inchisa
      si unul sau mai multe spatii

Grupurile de intrebari + raspunsuri nu trebuiesc delimitate de anumite
caractere speciale, iar spatiile dintre raspunsuri sau intrebari nu sunt luate in calcul.
Pentru siguranta, se recomanda ca atat intrebarile cat si raspunsurile aflate pe
multiple linii sa fie indentate pentru a nu face confuzie.
"""


import re
import sys
import random
import argparse


if "linux" in sys.platform:
    EOL = "\n"
else:
    EOL = "\r\n"

SAMPLES = 1
SEPARATOR = "{}\n".format("*" * 10)


class QShuffle(object):

    """Q&A randomizer."""

    def __init__(self, fin, fout=sys.stdout,
                 samples=SAMPLES, separator=SEPARATOR):
        # read data and close the input buffer
        self.data = fin.read()
        fin.close()
        # save output options
        self.fout = fout
        self.samples = samples
        self.separator = separator
        # randomized samples
        self.pages = list()
        # regexps
        self.qregex = re.compile(r"[0-9]+(?=\.\s+)")
        self.aregex = re.compile(r"[a-z](?=\)\s+)", re.IGNORECASE)

    def _shuffle(self):
        # chunked question-answers groups
        bits = list()
        # question and answer parts
        qpart, apart = list(), list()
        crs = qpart    # cursor
        # split data
        addans = lambda: bits[-1][1].append(EOL.join(crs).strip())
        for line in self.data.split(EOL):
            if crs is qpart and self.aregex.match(line):
                bits.append([EOL.join(crs).strip(), list()])
                crs = apart
            elif crs is apart and self.aregex.match(line):
                addans()
                crs = apart = list()
            elif crs is apart and self.qregex.match(line):
                addans()
                qpart, apart = list(), list()
                crs = qpart
            crs.append(line)
        addans()
        # randomize it
        random.shuffle(bits)
        for group in bits:
            random.shuffle(group[1])
        # update it
        qind = 0
        for group in bits:
            group[0] = self.qregex.sub(str(qind + 1), group[0])
            qind += 1
            aind = 0
            for pos in range(len(group[1])):
                char = chr(ord("a") + aind)
                aind += 1
                group[1][pos] = self.aregex.sub(char, group[1][pos])
        # return new sample
        return (EOL * 2).join([qstr + EOL + EOL.join(astrs)
                               for qstr, astrs in bits]) + EOL

    def generate(self):
        """Split data into question and answer parts,
        then build new shuffled samples.
        """
        for _ in range(self.samples):
            self.pages.append(self._shuffle())

    def save(self):
        """Glue out together and write data to console/file."""
        self.fout.write(self.separator.join(self.pages))
        if isinstance(self.fout, file):
            self.fout.close()


def main():
    # build parser
    parser = argparse.ArgumentParser(description="Randomize questions.")

    # add options
    parser.add_argument(
        "-o", "--output",
        type=argparse.FileType("w"),
        default=sys.stdout,
        help="output file"
    )
    parser.add_argument(
        "-s", "--samples",
        type=int, default=SAMPLES,
        help="how many randomized copies to create"
    )
    parser.add_argument(
        "-S", "--separator",
        default=SEPARATOR,
        help="separator between the copies"
    )

    # add requiered positional arguments
    parser.add_argument(
        "input", metavar="INPUT",
        type=argparse.FileType("r"),
        help="input file"
    )

    # parse and process them
    args = parser.parse_args()
    qshuffle = QShuffle(args.input, fout=args.output,
                        samples=args.samples, separator=args.separator)
    qshuffle.generate()
    qshuffle.save()
    

if __name__ == "__main__":
    main()
