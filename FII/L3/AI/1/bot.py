#! /usr/bin/env python


import json
import os
import random
import re


CONFIG_PATH = "bot.json"
CONFIG_DICT = {
    "questions": {
        "init": {
            "name": [
                "Salut! Cum te numesti?",
            ],
        },
    },
}


def uncapitalize(string):
    if not string:
        return string
    return string[0].lower() + string[1:]


class Bot(object):

    REGEX = {
        "name": [
            re.compile(r"[A-Z][a-z]+"),
        ],
        "name_prefix": [
            re.compile(r"(?<={} )([A-Z][a-z]+\s*)+".format(prefix))
            for prefix in [
                "ma numesc",
                "ma cheama",
                "numele meu este",
                "sunt",
                "ma intitulez",
                "lumea imi spune",
                "spune-mi",
                "cheama-ma",
            ]
        ]
    }

    def __init__(self, config_path):
        self._config = self._load_config(config_path)
        self._parse = {
            "name": self._parse_name,
        }

    @staticmethod
    def _load_config(config_path):
        if not os.path.isfile(config_path):
            with open(config_path, "w") as stream:
                json.dump(CONFIG_DICT, stream)
        with open(config_path) as stream:
            return json.load(stream)

    @classmethod
    def _parse_name(cls, string):
        """Incearca sa scoata un nume dintr-un sir de caractere."""
        if not string:
            return None
        # Poate utilizatorul raspunde prompt doar cu numele lui.
        chunks = string.split()
        if len(chunks) <= 3 and all(map(str.istitle, chunks)):
            return string
        # Sau raspunde formal.
        for regex in cls.REGEX["name_prefix"]:
            match = regex.search(string)
            if match:
                return match.group().strip()
        # Cauta dupa cuvinte cu litera mare.
        string = uncapitalize(string)
        for regex in cls.REGEX["name"]:
            results = regex.findall(string)
            if results:
                return " ".join(results)
        return None

    def _qget(self, *args):
        """Alege o intrebare random folosind o cale prin `args`."""
        if not args:
            return None
        values = self._config[args[0]]
        for key in args[1:]:
            values = values[key]
        if values:
            return random.choice(values)
        return None

    def _aget(self, *args):
        """Interpreteaza raspunsul punand o intrebare."""
        question = self._qget(*args)
        if not question:
            return None
        answer = raw_input("[?] {} ".format(question))
        subject = args[-1]
        func = self._parse[subject]
        return func(answer.strip())

    def adduse_user(self):
        """Adauga utilizator nou sau foloseste unul existent deja."""
        # Pune o intrebare random in legatura cu numele acestuia pana cand
        # intelegem raspunsul.
        while True:
            name = self._aget("questions", "init", "name")
            if name:
                break
        # Acum ca avem numele, verifica daca persoana exista deja sau pune
        # urmatoarele intrebari pentru o persoana noua.
        print(name)


def main():
    bot = Bot(CONFIG_PATH)
    bot.adduse_user()


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\n[!] Iesire.")
