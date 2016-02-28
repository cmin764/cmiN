#! /usr/bin/env python


import os
import pickle
import sys


class Angajat(object):

    def __init__(self, nume, varsta):
        super(Angajat, self).__init__()
        if not all(map(lambda args: isinstance(*args), [(nume, str),
                                                        (varsta, int)])):
            raise Exception("Nume {} si/sau varsta {} inalid(e)"
                            .format(nume, varsta))
        self.nume = nume
        self.varsta = varsta

    def __str__(self):
        return "{}: {} ({})".format(self.nume, self.varsta,
                                    type(self).__name__)


class Programator(Angajat):

    def __init__(self, limbaj, *args, **kwargs):
        super(Programator, self).__init__(*args, **kwargs)
        self.limbaj = limbaj

    def __str__(self):
        return (super(Programator, self).__str__() + 
                "\nProgrameaza in {}".format(self.limbaj))


class Tester(Angajat):

    MANUAL = "manual"
    AUTOMAT = "automat"
    ALL = (MANUAL, AUTOMAT,)

    def __init__(self, mod, *args, **kwargs):
        super(Tester, self).__init__(*args, **kwargs)
        if mod not in self.ALL:
            raise Exception("Mod {} invalid".format(tip))
        self.mod = mod

    def __str__(self):
        return (super(Tester, self).__str__() +
                "\nTesteaza {}".format(self.mod))


class SubordineMixin(object):

    def __init__(self):
        self.subordonati = []

    def adauga(self, subordonat):
        self.subordonati.append(subordonat)


class Sef(Angajat, SubordineMixin):

    ECHIPA = "echipa"
    GRUPA = "grupa"
    ALL = (ECHIPA, GRUPA,)

    def __init__(self, tip, *args, **kwargs):
        super(Sef, self).__init__(*args, **kwargs)
        if tip not in self.ALL:
            raise Exception("Tip {} invalid".format(tip))
        self.tip = tip

    def __str__(self):
        return (super(Sef, self).__str__() +
                "\nConduce {} formata din {}"
                .format(self.tip, [sub.nume for sub in self.subordonati]))


class Manager(Angajat, SubordineMixin):

    def __init__(self, subordonati=None, *args, **kwargs):
        super(Manager, self).__init__(*args, **kwargs)

    def __str__(self):
        return (super(Manager, self).__str__() +
                "\nSeful tuturor")


def create():
    programatori = map(lambda args: Programator(*args), [
                       ("Python", "Ion", 21),
                       ("Java", "Ionel", 22)])
    testeri = map(lambda args: Tester(*args), [
                  (Tester.AUTOMAT, "Gigi", 21),
                  (Tester.MANUAL, "Leonardo", 22)])
    sefp = Sef(Sef.ECHIPA, "Johnson", 30)
    [sefp.adauga(prog) for prog in programatori]
    seft = Sef(Sef.ECHIPA, "Jim", 29)
    [seft.adauga(tester) for tester in testeri]
    sefg = Sef(Sef.GRUPA, "Bionel", 40)
    [sefg.adauga(sef) for sef in (sefp, seft,)]
    subordonati = programatori + testeri + [sefp, seft, sefg]
    manager = Manager(subordonati, "Cosmin", 23)
    return [manager] + subordonati


def show(ents):
    for ent in ents:
        print(ent)
        print("")


def save(ents, fpath):
    with open(fpath, "w") as stream:
        pickle.dump(ents, stream)


def load(fpath):
    with open(fpath) as stream:
        return pickle.load(stream)


def main(argv):
    if len(argv) != 3:
        print("Usage: {} save/load PATH".format(argv[0]))
        return 1
    action = argv[1]
    fpath = argv[2]
    if action == "load":
        if not os.path.isfile(fpath):
            print("Invalid file path {!r}".format(fpath))
            return 2
        ents = load(fpath)
        show(ents)
    elif action == "save":
        ents = create()
        save(ents, fpath)
    else:
        print("Invalid action {!r}".format(action))
        return 2
    return 0


if __name__ == "__main__":
    exit(main(sys.argv))
