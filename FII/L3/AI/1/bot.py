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
                "Buna, ce nume ai?",
                "Cum te cheama?",
                "Si lumea iti spune?",
                "Cum te striga (mamaliga)?",
                "Ai vreun nume?",
            ],
            "age": [
                "Si ce varsta ai?",
                "Cati ani ai?",
                "Varsta ta este?",
                "Cati ani ai implinit?",
                "Cate primaveri au trecut de cand traiesti?",
            ],
            "occupation": [
                "Dar ocupatia?",
                "Ce faci in timpul liber?",
                "Din ce castigi bani?",
                "Ce meserie ai?",
                "Ce-ti aduce cozonacul pe masa?",
            ]
        },
        "conversation": {
            "age": {
                10: [
                    "Cum e viata la gradinita?",
                    "Poate ai gresit varsta, totusi esti copil?",
                    "Salut micutule.",
                    "Nu mai sta la calculator, du-te si joaca-te afara.",
                    "Iti place DotA?",
                    "Stii sa citesti (de scris n-are rost)?",
                ],
                30: [
                    "Cum e viata la munca?",
                    "Inca student?",
                    "In cati ani ai terminat facultatea?",
                    "Unde lucrezi?",
                    "Daca esti somer(a), e ok.",
                ],
                80: [
                    "Cum e viata la pensie?",
                    "Ai proteza?",
                    "Is bune prunele?",
                    "Esti mai putin tanar, nu batran.",
                    "Regreti ca nu ai fost bugetar?",
                ],
                None: [
                    "Odihna placuta.",
                    "Sa te odihnesti in pace.",
                    "Iti place viata?",
                    "Vrei sa prinzi 100 de ani?",
                    "Tine-o tot asa!",
                ]
            },
            "occupation": {
                "developer": [
                    "Scrii cod din pasiune sau pentru bani?",
                    "Cati ani de experienta ai?",
                    "Nu vrei sa te reprofilezi?",
                    "Faci outsourcing?",
                ],
                None: [
                    "Nu stiu ce sa te intreb in legatura cu ocupatia ta.",
                    "Succes in viata!",
                ]
            },
        },
    },
    "users": [],
    "welcome": [
        "Salut {}, bine ai venit in primul meu chatbot la AI.",
        "Buna {}, daca nu-ti place, apasa Ctrl+C.",
        "Salutare {}!",
        "Sper sa te distrezi cu acest bot, {}.",
        "Ar trebui sa fii multumit de tema la AI, {}.",
    ],
    "annoy": [
        "Hai ca esti enervant.",
        "M-ai plictisit.",
        "La revedere!",
    ]
}

MAX_COUNT = 5


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
                ("am varsta de", "de ani"),
                ("am", "de ani"),
                ("implinesc", "de ani"),
                ("facut", "de ani"),
                ("fac", "de ani"),
                ("sunt la", "de ani"),
            ]
        ],
        "occupation": [
            re.compile(r"[A-Z][a-z]+"),
        ],
        "occupation_prefix": [
            re.compile(r"(?<={} )(\w+\s*)+".format(prefix))
            for prefix in [
                "profesez",
                "sunt",
                "ma ocup cu",
                "muncesc ca",
                "lucrez ca",
                "fac",
                "imi ocup timpul cu",
                "lucrez in",
            ]
        ],
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

        self._user = None

    def _load_config(self):
        if not os.path.isfile(self._config_path):
            self._config = copy.deepcopy(CONFIG_DICT)
            self._save_config()
        with open(self._config_path) as stream:
            self._config = json.load(stream)

    def _save_config(self):
        with open(self._config_path, "w") as stream:
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
        if not string:
            return None
        # Poate utilizatorul raspunde prompt doar cu ocupatia lui.
        chunks = string.split()
        if len(chunks) <= 2 and all(map(str.istitle, chunks)):
            return string
        # Sau raspunde formal.
        for regex in cls.REGEX["occupation_prefix"]:
            match = regex.search(string)
            if match:
                return match.group().strip()
        # Cauta dupa cuvinte cu litera mare.
        string = uncapitalize(string)
        for regex in cls.REGEX["occupation"]:
            results = regex.findall(string)
            if results:
                return " ".join(results)
        return None

    @classmethod
    def _norm_dict(cls, obj):
        for key, value in obj.items():
            if isinstance(value, dict):
                obj[key] = value = cls._norm_dict(value)
            if key == "null":
                key = None
                del obj["null"]
            obj[key] = value
        return obj

    def _get_question(self, *args, **kwargs):
        """Alege o intrebare random folosind o cale prin `args`."""
        parse_answer = kwargs.get("parse_answer", True)
        if not args:
            return None
        values = self._config[args[0]]
        for key in args[1:]:
            values = values[key]
        if values:
            domain = args[-1]
            # Filtreaza intrebarile relevante categoriilor de varsta si
            # ocupatie.
            if parse_answer is False:
                values = self._norm_dict(values)
                if domain == "age":
                    ages = map(int, filter(None, values))
                    for age in sorted(ages):
                        if self._user["age"] > age:
                            continue
                        values = values.get(age, values.get(str(age)))
                        break
                    else:
                        values = values[None]
                elif domain == "occupation":
                    for occupation, _values in values.items():
                        if (occupation and occupation.lower() in
                                self._user["occupation"].lower()):
                            values = _values
                            break
                    else:
                        values = values[None]
                else:
                    print("[x] Domeniu fara interpretare de raspuns {}"
                          " invalid.".format(domain))
                    return None
            return random.choice(values)
        return None

    def _get_answer(self, *args, **kwargs):
        """Interpreteaza raspunsul punand o intrebare."""
        parse_answer = kwargs.get("parse_answer", True)
        question = self._get_question(*args, **kwargs)
        if not question:
            return None
        answer = raw_input("[?] {} ".format(question)).strip()
        if not parse_answer:
            return answer
        subject = args[-1]
        func = self._parse[subject]
        return func(answer)

    def _get_welcome(self):
        return random.choice(self._config["welcome"])

    @staticmethod
    def _build_user(**kwargs):
        return kwargs

    def _create_user(self, name, age, occupation):
        """Creaza un nou utilizator."""
        print("[*] Cream utilizator nou: {} {} {}".format(
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
            print("[!] Am gasit mai multi ca tine, o sa avem nevoie de date"
                  " aditionale...")

        if put_questions:
            # Trebuie sa punem intrebari cu privire la varsta si ocupatie
            # pentru a identifica mai bine utilizatorul gasit sau pentru a
            # crea unul nou.
            get_answer = functools.partial(self._get_answer,
                                           "questions", "init")
            ask = ["age", "occupation"]
            age = occupation = None
            while ask:
                # Ne asiguram ca obtinem tot ce ne intereseaza.
                if "age" in ask:
                    age = get_answer("age")
                    if age:
                        ask.remove("age")
                if "occupation" in ask:
                    occupation = get_answer("occupation")
                    if occupation:
                        ask.remove("occupation")
            create_user = lambda: self._create_user(name, age, occupation)
            get_user = lambda: self._get_user(
                name, age=age, occupation=occupation)
            if create:
                # Trebuie sa cream unul nou.
                create_user()
            # Indiferent ca l-am creat sau nu, in baza intrebarilor complete,
            # identificam utilizatorul in cauza.
            users = get_user()
            if not users:
                # Nu am gasit persoana dorita, asa ca o cream.
                create_user()
                users = get_user()
        # Orice ar fi, aici se alege utilizatorul corect dintr-o lista cu un
        # singur rezultat.
        self._user = users[0]

    def welcome(self):
        """Intampina utilizatorul cu un mesaj."""
        template = self._get_welcome()
        print("[i] " + template.format(self._user["name"]))

    def _test_annoy(self, count):
        if count <= MAX_COUNT:
            return False
        reply = random.choice(self._config["annoy"])
        print("[!] " + reply)
        return True

    def talk_with_user(self):
        """Vorbeste cu utilizatorul ales."""
        ask = self._config["questions"]["conversation"].keys()
        get_answer = functools.partial(
            self._get_answer, "questions", "conversation", parse_answer=False)
        answers = {}
        is_annoying = False
        while not is_annoying:
            # Intreaba la infinit, pana utilizatorul apasa Ctrl+C sau devine
            # enervant.
            domain = random.choice(ask)
            answer = get_answer(domain)
            count = answers.setdefault(answer, 0) + 1
            answers[answer] = count
            is_annoying = self._test_annoy(count)


def main():
    bot = Bot(CONFIG_PATH)
    bot.adduse_user()
    bot.welcome()
    bot.talk_with_user()


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\n[!] Iesire.")
