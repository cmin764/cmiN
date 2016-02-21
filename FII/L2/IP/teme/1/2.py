#! /usr/bin/env python


class NoteIP(object):

    def __init__(self):
        # Dictionar cu studenti si notele lor.
        self.studs = {}
        # Lungimea maxima a numelui.
        self.max_len = len("Nume")

    def show(self):
        # Afisam header.
        starline = "*" * (43 + self.max_len)
        print(starline)
        print(("* {:%d} * Lab * Proiect * Examen * Nota Finala *" % self.max_len).format("Nume"))
        print(starline)
        # Afisam fiecare student.
        for stud, marks in self.studs.items():
            print(("* {:%d} * {:3} * {:7} * {:6} * {:11} *" % self.max_len).format(stud, *marks))
        print(starline)

    def _check(self, marks):
        if any(map(lambda arg: not arg.isdigit(), marks)):
            raise Exception("Note invalide {}".format(marks))

    def read(self):
        # Stocam numarul de studenti si detaliile lor.
        nr = int(raw_input("Nr. studenti: "))
        for idx in range(nr):
            details = raw_input("Detalii student #{}: ".format(idx + 1))
            details = [x.strip() for x in details.split(",")]
            name, marks = details[0], details[1:]
            self._check(marks)
            self.studs[name] = marks
            self.max_len = max(self.max_len, len(name))


if __name__ == "__main__":
    note_ip = NoteIP()
    note_ip.read()
    note_ip.show()
