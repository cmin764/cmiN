#! /usr/bin/env python


import copy
import functools
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
            "age": [
                "Si ce varsta ai?",
            ],
            "occupation": [
                "Dar ocupatia?",
            ]
        },
    },
    "users": [],
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
        ],
        "age": [
            re.compile(r"\d+"),
        ],
        "age_brace": [
            re.compile(r"(?<={} )\d+( ?={})".format(prefix, suffix))
            for prefix, suffix in [
                ("am varsta de", "ani"),
                ("am", "ani"),
                ("implinesc", "ani"),
                ("facut", "ani"),
                ("fac", "ani"),
                ("sunt la", "ani"),
            ]
        ]
    }

    def __init__(self, config_path):
        self._config_path = config_path
        self._config = None
        self._load_config()

        self._parse = {
            "name": self._parse_name,
            "age": self._parse_age,
            "occupation": self._parse_occupation,
        }

    def _load_config(self):
        if not os.path.isfile(self._config_path):
            self._config = copy.deepcopy(CONFIG_DICT)
            self._save_config()
        with open(self._config_path) as stream:
            self._config = json.load(stream)

    def _save_config(self):
        with open(config_path, "w") as stream:
            json.dump(self._config, stream, indent=4)

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

    @classmethod
    def _parse_age(cls, string):
        """Scoatem varsta dintr-un raspuns."""
        if not string:
            return None
        # Raspuns prompt.
        try:
            age = int(string)
            return age
        except ValueError:
            pass    # a esuat, deci avem si litere (propozitie)
        # Raspuns formal.
        for regex in cls.REGEX["age_brace"]:
            match = regex.search(string)
            if match:
                return int(match.group().strip())
        # Cauta dupa siruri de cifre.
        for regex in cls.REGEX["age"]:
            results = regex.findall(string)
            if len(results) != 1:
                return None    # 0 sau mai mult de 1 rezulat
            return int(results[0])
        return None

    @classmethod
    def _parse_occupation(cls, string):
        """Scoatem ocupatia dintr-un raspuns."""
        pass

    def _get_question(self, *args):
        """Alege o intrebare random folosind o cale prin `args`."""
        if not args:
            return None
        values = self._config[args[0]]
        for key in args[1:]:
            values = values[key]
        if values:
            return random.choice(values)
        return None

    def _get_answer(self, *args):
        """Interpreteaza raspunsul punand o intrebare."""
        question = self._get_question(*args)
        if not question:
            return None
        answer = raw_input("[?] {} ".format(question))
        subject = args[-1]
        func = self._parse[subject]
        return func(answer.strip())

    @staticmethod
    def _build_user(**kwargs):
        return kwargs

    def _create_user(self, name, age, occupation):
        """Creaza un nou utilizator."""
        print("[i] Cream utilizator nou: {} {} {}".format(
            name, age, occupation))
        user = self._build_user(name=name, age=age, occupation=occupation)
        self._config["users"].append(user)
        self._save_config()

    @staticmethod
    def _match_users(given, candidate):
        matches = []
        for key, value in given.items():
            if value is None:
                continue    # nu suntem interesati de aceasta cheie
            _value = candidate.get(key)
            matches.append(value == _value)
        return all(matches)

    def _get_user(self, name, age=None, occupation=None):
        user = self._build_user(name=name, age=age, occupation=occupation)
        users = self._config["users"]
        candidates = []
        for _user in users:
            if self._match_users(user, _user):
                candidates.append(_user)
        return candidates

    def adduse_user(self):
        """Adauga utilizator nou sau foloseste unul existent deja."""
        # Pune o intrebare random in legatura cu numele acestuia pana cand
        # intelegem raspunsul.
        while True:
            name = self._get_answer("questions", "init", "name")
            if name:
                break

        # Acum ca avem numele, verifica daca persoana exista deja sau pune
        # intrebari complete pentru a adauga o persoana noua sau a gasi-o pe
        # cea cautata.
        users = self._get_user(name)
        count = len(users)
        if count == 0:
            # Cream un nou utilizator.
            create = put_questions = True
        elif len(users) == 1:
            # Am gasit utilizatorul si nu suntem in dubii.
            create = put_questions = False
        else:
            # Am gasit mai multi, asa ca punem intrebari aditionale.
            create = False
            put_questions = True

        if put_questions:
            # Trebuie sa punem intrebari cu privire la varsta si ocupatie
            # pentru a identifica mai bine utilizatorul gasit sau pentru a
            # crea unul nou.
            get_answer = functools.partial(self._get_answer,
                                           "questions", "init")
            while True:
                age, occupation = map(get_answer, ["age", "occupation"])
                print(age, occupation) ####
                if all([age, occupation]):
                    # Ne asiguram ca obtinem tot ce ne intereseaza.
                    break
            if create:
                # Trebuie sa cream unul nou.
                self._create_user(name, age, occupation)
            # Indiferent ca l-am creat sau nu, in baza intrebarilor complete,
            # identificam utilizatorul in cauza.
            users = self._get_user(name, age=age, occupation=occupation)
            if not users:
                # Nu am gasit persoana dorita, asa ca o cream.
                self._create_user(name, age, occupation)
                users = self._get_user(name, age=age, occupation=occupation)
        # Orice ar fi, aici se alege utilizatorul corect dintr-o lista cu un
        # singur rezultat.
        user = users[0]
        print(user) ####


def main():
    bot = Bot(CONFIG_PATH)
    bot.adduse_user()


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\n[!] Iesire.")
