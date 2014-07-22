#! /usr/bin/env python
# C++ Fibonacci challenge
# 10.02.2012 cmiN
# exponentiere a matricei Q fibonacci
# in timp logaritmic folosind numere mari


from decimal import getcontext, Decimal as D


class CFib:
    """
    Clasa pentru a calcula CMMDCul a 2 numere din seria Fibonacci.
    Se stie ca cmmdc(fib(a), fib(b)) e acelasi lucru cu fib(cmmdc(a, b))
    unde fib(x) este al x-lea numar din serie. Acesta poate fi calculat
    foarte rapid cu ridicarea unei matrice 2x2 specifice folosind
    ridicare la putere in logN.
    Totusi avem nevoie si de numere mari (decimal) ;].
    """
    
    def __init__(self, a, b):
        # setam precizia in zecimale
        getcontext().prec = 7000 # nici al 30k-lea nu depaseste
        self.a = a
        self.b = b
        self.qmat = ((1, 1),
                     (1, 0))
        self.res = ((D(1), D(0)), # I2
                    (D(0), D(1)))

    def cmmdc(self, a, b):
        """ Euclid cu impartiri. """
        while b != 0:
            t = a
            a = b
            b = t % b
        return a

    def multiply(self, op=False):
        if op: # op e True cand inmultim noua matrice Q cu rezultatul
            mat = self.res # doar o referinta / un sinonim catre un obiect
        else: # si False cand ridicam la patrat si retinem matricea Q
            mat = self.qmat
        # prea lenes sa bag 3 foruri
        e1 = mat[0][0] * self.qmat[0][0] + mat[0][1] * self.qmat[1][0]
        e2 = mat[0][0] * self.qmat[0][1] + mat[0][1] * self.qmat[1][1]
        e3 = mat[1][0] * self.qmat[0][0] + mat[1][1] * self.qmat[1][0]
        e4 = mat[1][0] * self.qmat[0][1] + mat[1][1] * self.qmat[1][1]
        # modificam rezultatul cu noile valori
        mat = ((e1, e2),
               (e3, e4))
        if op:
            self.res = mat
        else:
            self.qmat = mat

    def process(self):
        """ Functia principala. """
        nr = self.cmmdc(self.a, self.b)
        #print nr # debug
        # acum ridicam pe res la nr
        while nr > 0:
            if nr % 2: # putere impara
                self.multiply(True) # inmultim cu rezultatul
            self.multiply() # multiplicam qmat
            nr /= 2

    def get(self):
        return str(self.res[0][1]) # (Q^n)[0][1] == F(n)
        

def main():
    (a, b) = raw_input("Introdu 2 numere: ").split()
    obj = CFib(int(a), int(b))
    obj.process()
    print obj.get()


if __name__ == "__main__":
    main()
