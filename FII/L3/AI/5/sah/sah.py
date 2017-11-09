#! /usr/bin/env python


import json
import re
import sys
import time


BLACK = "b"
WHITE = "w"

DELAY = 1


class Player(object):

    """Unul din cei doi jucatori de pe tabla."""

    def __init__(self, ptype):
        self.ptype = ptype
        self.table = None
        self.count = Table.SIZE
        self.enpassant = None
        self.opponent = None

    def get_pawns(self, own=True):
        """Intoarce pionii proprii sau ai oponentului."""
        ptype = self.ptype if own else ({BLACK, WHITE} - {self.ptype}).pop()
        return self.table.get_pawns(ptype)

    def move_pawn(self, src, dest):
        """Muta un pion din sursa in destinatie."""
        self.table.remove_pawn(src)
        self.table.create_pawn(dest, self.ptype)

    def generate_move(self):
        # FIXME(cmiN): creare functie care returneaza toate posibilitatile de
        # mutari pornind de la oricare sursa data, numai in destinatii valide.

        # TODO(Mihai): creare logica ce exploreaza tot spatiul de posibilitati
        # de nivel N (2) pornind din toate sursele disponibile si returnand
        # cea mai buna mutare (pereche sursa, destinatie).

        # Pentru teste naive, muta pionul cu un singur pas pe coloana lui.
        pos_list = self.get_pawns()
        src = pos_list[0]
        dir = 1 if self.ptype == BLACK else -1
        idx = Table.pos2idx(src)
        idx = (idx[0] + dir, idx[1])
        dest = Table.idx2pos(idx)
        return src, dest

    def has_pawn(self, pos):
        """Intoarce True daca avem vreun pion aici."""
        return self.ptype == self.table.get_pawn(pos)

    def on_start(self, pos):
        expect = "7" if self.ptype == BLACK else "2"
        return expect == pos[0]

    def delta_pos(self, pos, delta, player=None):
        """Intoarce pozitia relativa la `pos` cu `delta` modificare."""
        # Diferenta este pozitiva pt. mutare inainte (linie) si la dreapta
        # (coloana); negativa in celelalte cazuri, de aceea trebuie
        # normalizare in functie de jucatorul la care se face referire.
        if not player:
            player = self
        delta = list(delta)

        # Inversam diferenta pe linie pt. jucatorul alb fata de indecsi.
        if player.ptype == WHITE:
            delta[0] *= -1
        # Inversam diferenta pe coloana pt. jucatorul negru fata de indecsi.
        if player.ptype == BLACK:
            delta[1] *= -1

        idx = Table.pos2idx(pos)
        idx = [idx[i] + delta[i] for i in range(2)]
        return Table.idx2pos(idx)

    def at_finish(self, pos):
        """Verifica daca jucatorul in cauza a ajuns cu pionul dat ca parametru
        la prima linie a adversarului.
        """
        finish = "8" if self.ptype == WHITE else "1"
        return finish == pos[0]


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

    def get_pawn(self, pos):
        idx = self.pos2idx(pos)
        cell = self._matrix[idx[0]][idx[1]]
        return cell.taken

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
        self._current_player = None

        self._winner = None

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
            if re.match(r"\w{2} \w{2}", ask):
                src, dest = map(lambda arg: list(arg),
                                ask.strip().split())
                statuses = []
                for ent in (src, dest):
                    a, b = ent[0], ent[1]
                    status = (a.isdigit() and b.isalpha() or
                              a.isalpha() and b.isdigit())
                    statuses.append(status)
                if all(statuses):
                    for ent in (src, dest):
                        if not ent[0].isdigit():
                            ent.reverse()
                    break

        return tuple(map(tuple, (src, dest)))

    def _get_delta(self, src, dest, player):
        """Intoarce diferenta de pozitie de la sursa la destinatie relativa
        la jucatorul in cauza.
        """
        src_idx, dest_idx = map(Table.pos2idx, [src, dest])
        delta = [dest_idx[i] - src_idx[i] for i in range(2)]
        # Inversam diferenta pe linie pt. jucatorul alb fata de indecsi.
        if player.ptype == WHITE:
            delta[0] *= -1
        # Inversam diferenta pe coloana pt. jucatorul negru fata de indecsi.
        if player.ptype == BLACK:
            delta[1] *= -1
        return tuple(delta)

    def _validate_move(self, src, dest, player, opponent):
        data = {
            "enpassant": None,
            "eat": None,
        }

        # Sursa si destinatia nu trebuie sa fie egale.
        if src == dest:
            return False, data

        # Verificam daca pozitiile sunt in interiorul tablei.
        for ent in (src, dest):
            if ent[0] not in self._table.L_LINES:
                return False, data
            if ent[1] not in self._table.L_COLS:
                return False, data

        # Verificam daca sursa ne apartine si avem o piesa proprie acolo.
        if not player.has_pawn(src):
            return False, data

        # Sunt distantele si directiile ok?
        delta = self._get_delta(src, dest, player)
        # Nu avem voie sa avem deplasari negative pe linie.
        # Fara deplasare doar pe coloana sau stat pe loc.
        if delta[0] <= 0:
            return False, data
        # Fara distante dubioase pe linie sau coloana sau ambele.
        if abs(delta[1]) > 1 or delta[0] > 2 or delta[0] == 2 and delta[1]:
            return False, data
        # Salt 2x doar din linia de start.
        if delta[0] == 2:
            if not player.on_start(src):
                return False, data
            data["enpassant"] = True

        # Verificat blocaje si salt peste. Dar si atac.
        if not delta[1]:
            # Facem mutare strict inainte.
            front, far_front = [player.delta_pos(src, (step, 0))
                                for step in (1, 2)]
            if opponent.has_pawn(front) or player.has_pawn(front):
                return False, data
            if (delta[0] == 2 and
                    (opponent.has_pawn(far_front) or
                         player.has_pawn(far_front))):
                return False, data
        else:
            # Facem mutare strict pe diagonala, deci vrem sa capturam.
            if player.has_pawn(dest):
                # Ne mancam pe noi insine?
                return False, data
            if not opponent.has_pawn(dest):
                # Doar in situatie de en passant mai putem manca.
                if opponent.enpassant != dest:
                    return False, data
            data["eat"] = True

        # Miscarea este valida.
        return True, data

    def mainloop(self):
        """Joaca pana cineva castiga sau devine remiza."""
        stop = False

        while not stop:
            self._current_player = self._human
            # Verificam conditiile de oprire.
            # Stare de blocaj.
            if not self._human.generate_move():
                if self._cpu.generate_move():
                    self._winner = self._cpu
                break
            # Cineva ramane fara piese.
            if self._human.count <= 0:
                self._winner = self._cpu
                break
            if self._cpu.count <= 0:
                self._winner = self._human
                break
            # Cineva a ajuns pe ultima linie.
            for player in [self._human, self._cpu]:
                pawns = self._table.get_pawns(player.ptype)
                for pawn in pawns:
                    if player.at_finish(pawn):
                        self._winner = player
                        stop = True
                        break
                if stop:
                    break

            if stop:
                break

            # Afiseaza tabla curenta.
            self._show_table()
            # Mutarea jucatorului.
            src, dest = self._move_prompt()
            validation = self._validate_move(src, dest,
                                             self._human, self._cpu)
            status, data = validation
            if status:
                if data["eat"]:
                    # Mancam piesa adversarului.
                    self._table.remove_pawn(dest)
                    self._cpu.count -= 1
                self._human.move_pawn(src, dest)
                if data["enpassant"]:
                    front = self._human.delta_pos(src, (1, 0))
                    # Daca oponentul poate sari pe diagonala in `front`,
                    # atunci piesa poate fi mancata.
                    self._human.enpassant = front
                self._cpu.enpassant = None
            else:
                print("[x] Invalid human move.")
                continue

            # Mutarea computerului.
            self._current_player = self._cpu
            while True:
                move = self._cpu.generate_move()
                if not move:
                    if self._human.generate_move():
                        self._winner = self._human
                    stop = True
                    break
                src, dest = move
                validation = self._validate_move(src, dest,
                                                 self._cpu, self._human)
                status, data = validation
                if status:
                    if data["eat"]:
                        # Mancam piesa adversarului.
                        self._table.remove_pawn(dest)
                        self._human.count -= 1
                    self._cpu.move_pawn(src, dest)
                    if data["enpassant"]:
                        front = self._cpu.delta_pos(src, (1, 0))
                        # Daca oponentul poate sari pe diagonala in `front`,
                        # atunci piesa poate fi mancata.
                        self._cpu.enpassant = front
                    self._human.enpassant = None
                    break
                else:
                    print("[x] Invalid cpu move.")
                    time.sleep(DELAY)
                    continue

        # Intoarce culoarea castigatorului.
        return self._winner.ptype if self._winner else None


def main():
    # Pre-procesare argumente intrare.
    custom_state = None
    if len(sys.argv) > 1:
        custom_state = sys.argv[1]

    # Cream entitatile.
    table = Table()
    black, white = map(Player, [BLACK, WHITE])
    black.opponent = white
    white.opponent = black

    # Cream si dam drumul la joc.
    game = Game(black, white, table)
    try:
        game.initialize(custom_state=custom_state)
        winner = game.mainloop()
    except KeyboardInterrupt:
        print("[!] Exit.")
    else:
        if winner is None:
            status = "draw"
        else:
            status = "black" if winner == BLACK else "white"
        print("Winner: {}".format(status))


if __name__ == "__main__":
    main()
