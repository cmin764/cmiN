import java.util.Map;
import java.util.Set;
import java.util.Iterator;
import java.util.TreeMap;
import java.util.ArrayList;


public final class Litere {

    static final boolean ZERO_RATIO = false;    // progresii cu ratia 0
    static final int CSTART = (int)'a';      // prima litera din alfabet
    static int nr, lim;    // numarul de jucatori si limita de litere
    static int winner = -1;
    static ArrayList<TreeMap<Integer, Integer>> players;    // jucatorii
    static StringBuilder word;

    /**
     * Se verifica daca jucatorul dat ca parametru are vreun
     * set de litere aflate in progresie aritmetica pozitiva.
     */
    static boolean check_player(TreeMap<Integer, Integer> player)
    {
        int ratio = -1;    // ratie invalida
        int count = -1;

        Set<Map.Entry<Integer, Integer>> pset = player.entrySet();
        Iterator<Map.Entry<Integer, Integer>> it = pset.iterator();
        Map.Entry<Integer, Integer> last = (Map.Entry<Integer, Integer>)
                it.next();

        while (it.hasNext()) {
            Map.Entry<Integer, Integer> crt =
                    (Map.Entry<Integer, Integer>)it.next();
            int first = (int)last.getKey();
            int second = (int)crt.getKey();
            int _ratio = (second - first);
            last = crt;

            if (ratio == -1) {
                ratio = _ratio;    // initializam ratia si
                count = 2;         // numarul de elemente valide
                word = new StringBuilder();
                word.append((char)(first + CSTART));
                word.append((char)(second + CSTART));
            } else {
                // verificam daca noul element respecta ratia
                if (_ratio == ratio) {
                    ++count;
                    word.append((char)((int)crt.getKey() + CSTART));
                    if (count >= lim) {
                        return true;    // avem un castigator
                    }
                } else {
                    // nu e bun
                    ratio = -1;
                }
            }
        }

        return false;
    }

    /**
     * Fiecare jucator primeste cate o litera, apoi se verifica daca
     * conditia ca cel putin un jucator sa aiba minim `nr` litere in
     * progresie aritmetica este indeplinita respectand limita impusa.
     *
     * Returneaza true daca se mai joaca runde sau false in caz contrar.
     */
    static boolean play(int round)
    {
        System.out.println("Runda " + round);
        // pentru fiecare jucator
        for (int cid = 0; cid < nr; ++cid) {
            // obtine multimea de litere sub forma de numere 0-25
            TreeMap<Integer, Integer> player = players.get(cid);
            // generam litera aleator
            int letter = (int)(Math.random() * 26);
            // modifica multimea
            int count = 0;
            if (player.containsKey(letter)) {
                count = (int)player.get(letter);
            }
            ++count;
            player.put(letter, count);
            // actualizam in vector
            players.set(cid, player);
            // afisam situatia
            System.out.print((cid + 1) + ". ");
            for (Map.Entry<Integer, Integer> entry: player.entrySet()) {
                letter = (int)entry.getKey();
                int repeat = (int)entry.getValue();
                while(repeat-- != 0) {
                    System.out.print((char)(letter + CSTART));
                }
            }
            System.out.println();
            // il verificam
            if (player.size() < lim || winner != -1) {
                continue;    // nimic de verificat, limita nu a fost atinsa
            }
            if (ZERO_RATIO) {
                // verificam progresia aritmetica nula
                for (Map.Entry<Integer, Integer> entry : player.entrySet()) {
                    letter = (int)entry.getKey();
                    int repeat = (int)entry.getValue();
                    if (repeat >= lim) {
                        // avem progresie aritmetica nula
                        word = new StringBuilder();
                        while (repeat-- != 0) {
                            word.append((char)(letter + CSTART));
                        }
                        winner = cid;
                    }
                }
            }
            // verificam si daca exista vreo progresie cu ratie pozitiva
            if (winner == -1 && check_player(player)) {
                winner = cid;
            }
        }
        if (winner != -1) {
            return false;
        }
        return true;
    }

    public static void main(String[] args)
    {
        if (args.length != 2) {
            System.out.println("Usage: Litere PLAYERS LIMIT");
            return;
        }

        // numarul de persoane respectiv limita inferioara de litere
        nr = Integer.parseInt(args[0]);
        lim = Integer.parseInt(args[1]);

        // cream un vector de seturi in care tinem minte literele
        // curente ordonate pentru fiecare jucator in parte
        players = new ArrayList<TreeMap<Integer, Integer>>();
        for (int i = 0; i < nr; ++i) {
            players.add(new TreeMap<Integer, Integer>());
        }

        // cat timp se poate juca, fiecare jucator primeste cate o litera
        int cnt = 0;
        while (play(++cnt));

        // afisam castigatorul, daca exista vreunul
        if (winner != -1) {
            System.out.println("A castigat jucatorul: #" + (winner + 1));
            System.out.println("Ce are cuvantul: " + word);
        }
    }
}
