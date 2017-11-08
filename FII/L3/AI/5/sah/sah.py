#! /usr/bin/env python


import json
import re
import sys


BLACK = "b"
WHITE = "w"


class Player(object):

    """Unul din cei doi jucatori de pe tabla."""

    def __init__(self, ptype):
        self._ptype = ptype
        self.table = None

    def get_pawns(self, own=True):
        """Intoarce pionii proprii sau ai oponentului."""
        ptype = self._ptype if own else ({BLACK, WHITE} - {self._ptype}).pop()
        return self.table.get_pawns(ptype)

    def move_pawn(self, src, dest):
        """Muta un pion din sursa in destinatie."""
        self.table.remove_pawn(src)
        self.table.create_pawn(dest, self._ptype)

    def generate_move(self):
        # FIXME(cmiN): creare functie care returneaza toate posibilitatile de
        # mutari pornind de la oricare sursa data, numai in destinatii valide.

        # TODO(Mihai): creare logica ce exploreaza tot spatiul de posibilitati
        # de nivel N (2) pornind din toate sursele disponibile si returnand
        # cea mai buna mutare (pereche sursa, destinatie).

        # Pentru teste naive, muta pionul cu un singur pas pe coloana lui.
        pos_list = self.get_pawns()
        src = pos_list[0]
        dir = 1 if self._ptype == BLACK else -1
        idx = Table.pos2idx(src)
        idx = (idx[0] + dir, idx[1])
        dest = Table.idx2pos(idx)
        return src, dest


class Cell(object):

    def __init__(self, pos, label, taken):
        self.pos = pos
        self.label = label
        self.taken = taken


class Table(object):

    """Reprezentarea actuala a tablei (repartizarea pionilor)."""

    SIZE = 8
    L_LINES = map(str, range(SIZE, 0, -1))
    L_COLS = map(chr, range(ord("a"), ord("a") + SIZE))

    def __init__(self):
        # Tabla de sah colorata cu pozitia pionilor pe pozitiile lor initiale.
        self._matrix = [[None] * self.SIZE for _ in range(self.SIZE)]
        for lin in range(self.SIZE):
            for col in range(self.SIZE):
                pos = self.idx2pos((lin, col))
                label = BLACK if (lin + col) % 2 else WHITE
                self._matrix[lin][col] = Cell(pos, label, None)

    @classmethod
    def idx2pos(cls, idx):
        return cls.L_LINES[idx[0]], cls.L_COLS[idx[1]]

    @classmethod
    def pos2idx(cls, pos):
        return cls.L_LINES.index(pos[0]), cls.L_COLS.index(pos[1])

    def _set_pawn(self, pos, taken=None):
        idx = self.pos2idx(pos)
        self._matrix[idx[0]][idx[1]].taken = taken

    def create_pawn(self, pos, ptype):
        self._set_pawn(pos, taken=ptype)

    def remove_pawn(self, pos):
        self._set_pawn(pos)

    def get_pawns(self, ptype):
        pos_list = []
        for lin in range(self.SIZE):
            for col in range(self.SIZE):
                cell = self._matrix[lin][col]
                if cell.taken == ptype:
                    pos_list.append(self.idx2pos((lin, col)))
        return pos_list

    def show(self):
        print(" " + " ".join(self.L_COLS))
        for lin in range(self.SIZE):
            elems = []
            for col in range(self.SIZE):
                cell = self._matrix[lin][col]
                elems.append(cell.taken or " ")
            elems.insert(0, self.L_LINES[lin])
            print(" ".join(elems))


class Game(object):

    """Reprezentarea jocului."""

    row = lambda lin: [(lin, col) for col in Table.L_COLS]
    DEFAULT_STATE = {
        BLACK: row("7"),
        WHITE: row("2"),
    }
    STATE_FILE = "state.json"

    def __init__(self, black, white, table):
        self._black = black
        self._white = white
        self._table = table
        self._black.table = self._white.table = self._table

        self._cpu = None
        self._human = None

    def initialize(self, custom_state=None):
        """Initializeaza tabla de joc si jucatori."""
        # Configuram tabla de joc.
        if custom_state:
            with open(custom_state, "r") as stream:
                custom_state = json.load(stream)
        else:
            custom_state = self.DEFAULT_STATE

        with open(self.STATE_FILE, "w") as stream:
            json.dump(custom_state, stream, indent=4)

        for ptype, pos_list in custom_state.items():
            for pos in pos_list:
                self._table.create_pawn(pos, ptype)

        # Facem alegerea jucatorilor.
        sides = [self._black, self._white]
        ask = raw_input("[?] Choose your side (0-black, 1-white): ")
        if int(ask):
            sides.reverse()
        self._human = sides[0]
        self._cpu = sides[1]

    def _show_table(self):
        self._table.show()

    @staticmethod
    def _move_prompt():
        while True:
            ask = raw_input("[?] Enter source and destination: ")
            if re.match(r"\d\w \d\w", ask):
                break

        src, dest = map(lambda arg: tuple(list(arg)), ask.strip().split())
        return src, dest

    def _validate_move(self, src, dest):
        # Sursa si destinatia nu trebuie sa fie egale.
        if src == dest:
            return False
        # Verificam daca pozitiile sunt in interiorul tablei.
        for ent in (src, dest):
            if ent[0] not in self._table.L_LINES:
                return False
            if ent[1] not in self._table.L_COLS:
                return False
        # TODO(cmiN): validari pt. mutare inainte/inapoi, oponent, piesa
        # proprie, lungime inadecvata pt. directia aleasa etc.
        # Miscarea este valida.
        # FIXME(cmiN): functie pt. generare toate mutari valide posibile (va
        # ajuta si la algoritmul de AI care creeaza spatiul de posibilitati)
        return True

    def mainloop(self):
        """Joaca pana cineva castiga sau devine remiza."""
        stop = False
        while not stop:
            # Afiseaza tabla curenta.
            self._show_table()
            # Mutarea jucatorului.
            src, dest = self._move_prompt()
            if self._validate_move(src, dest):
                self._human.move_pawn(src, dest)
            else:
                print("[x] Invalid move.")
            # Mutarea computerului.
            src, dest = self._cpu.generate_move()
            self._cpu.move_pawn(src, dest)


def main():
    # Pre-procesare argumente intrare.
    custom_state = None
    if len(sys.argv) > 1:
        custom_state = sys.argv[1]

    # Cream entitatile.
    table = Table()
    black, white = map(Player, [BLACK, WHITE])

    # Cream si dam drumul la joc.
    game = Game(black, white, table)
    try:
        game.initialize(custom_state=custom_state)
        game.mainloop()
    except KeyboardInterrupt:
        print("[!] Exit.")


if __name__ == "__main__":
    main()
