/**
 * Folosind suma lui Leibnez, se aduna progresiv fractii
 * cu numarator constant si numitor aflat in progresie aritmetica
 * pana cand numarul de zecimale, ale numarului calculat
 * la pasul anterior identice cu cele de la pasul curent,
 * devine cat numarul dat ca parametru.
 */


/// Clasa principala.
public class Leibniz {

    // pi/4 de la pasul curent si cel anterior pentru comparatie
    static double total, last;

    /**
     * Adauga fractia specifica pasului curent,
     * apoi gaseste numarul de zecimale stabile din Pi.
     */
    static int add(int step, int crt)
    {
        // semnul pasului curent
        double sign = -1.0;
        if (step % 2 == 1) {
            sign = 1.0;
        }

        // se aduna la total fractia
        total += sign / (double)(2 * step - 1);

        // se adapteaza noile sume pentru extragerea primei zecimale noi
        double mag = Math.pow(10, crt + 1);
        double _total = 4 * total * mag;
        double _last = 4 * last * mag;

        // actualizarea pasului anterior
        last = total;
        if (_last == 0) {
            return 0;
        }

        // sunt numarate zecimalele stabile
        for (int decnr = crt + 1; ; ++decnr, _total *= 10, _last *= 10) {
            long a = (long)(_total) % 10;
            long b = (long)(_last) % 10;
            if (a != b) {
                return decnr - 1;
            }
        }
    }

    // functia princpala
    public static void main(String[] args)
    {
        // asteapta un parametru, numarul de zecimale stabile ale lui Pi
        if (args.length != 1) {
            System.out.println("Usage: Leibniz NUMBER");
            return;
        }

        int target = Integer.parseInt(args[0]);
        total = last = 0;
        
        // se calculeaza pana se obtin zecimalele dorite
        int ret = 0;
        for (int step = 1; ; ++step) {
            ret = add(step, ret);
            if (ret >= target) {
                break;
            }
        }

        // se afiseaza noul Pi calculat dupa formula
        System.out.println("Pi: " + total * 4);
    }
}
