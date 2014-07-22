#! /usr/bin/env python
## generare scaderi prin calcule
## 16.10.2011 cmiN


IVAL = [10, 99] # interval compact
MOD = 10


def generare(nr):
    """ Complexitate maxima O(N^2 * (1+1/mod)/2) amortizata de 'nr' """
    tmp = None # un fel de switch ce memoreaza primul pozitiv
    vec = list() # aici pastram perechile valide
    a = IVAL[1] # max sau ce valoare vrei tu din interval
    while a > IVAL[0]:
        if a % MOD == MOD - 1:
            a -= 1 # nu putea avea perechi
        b = a - 1 # a > b
        while b >= IVAL[0]:
            if b % MOD > a % MOD:
                if tmp is None:
                    tmp = b
                if nr:
                    vec.append((a, b))
                    nr -= 1
                else:
                    return vec # returnam lista de 'nr' perechi
                b -=1
            else:
                if tmp is None:
                    b -= 1
                else:
                    b = tmp - MOD
                    tmp = None
        a -= 1
    return vec # s-au epuizat toate posibilitatile


def main():
    nr = input("Numar de elemente: ")
    vec = generare(nr)
    for el in vec: # si le afisam
        print el,

if __name__ == "__main__":
    main()
