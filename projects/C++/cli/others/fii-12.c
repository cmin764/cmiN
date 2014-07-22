/*
 * Problema 3 (III) la testul de admitere din 2012 la FII (UAIC)
 *
 * La punctul a) se raspundea cu solutia naiva: pentru fiecare
 * x0 si pentru fiecare x1 se luau valori, apoi se verifica
 * suma pentru a stabili daca perechea de numere constitue solutie.
 *
 * La b) se poate implementa destul de usor doar respectand ideea
 * sumei precizate de cerinta. Alegerea x-ului se face in functie
 * de semnul coeficientului si de conotatia functiei.
 *
 * c) poate baga putin in ceata mintea programatorului avand impresia
 * ca folosirea respectivelor functii poate duce la o complexitate
 * polinomiala (sau cu mult mai mica decat cea exponentiala) insa
 * ele reprezinta o euristica catre verificarea la fiecare pas daca
 * x-ul ales poate reprezenta un candidat bun pentru ecuatie.
 */


#include <stdio.h>
#include <stdlib.h>


typedef struct {
    /**
     * Structura pentru stabilirea minimului
     * si maximului pornind de la un index.
     *
     * De obicei utilizata intr-un tablou pentru
     * a nu calcula de fiecare data cand este nevoie.
     */
    int lo; // minim
    int hi; // maxim
} Extr;


int min(int n, int a[], int b, int inf, int sup, int k)
{
    /**
     * Functia de calculare a minimului.
     * Nu inteleg totusi la ce-mi trebuie b,
     * probabil gresesc pe undeva.
     */
    int sum = 0;
    /* calculam si adunam liniar de la k la n minimul
     * fiecarui element ce duc implicit la minimul sumei
     */
    int i;
    for (i = k; i < n; ++i) {
        int coef = a[i];
        if (!coef) continue; // nu avem ce aduna
        else if (coef > 0) {
            /* pozitiv, deci numarul cel mai mic
             * va fi dat de capatul inferior
             */
            sum += coef * inf;
        } else {
            // analog pentru capatul superior
            sum += coef * sup;
        }
    }
    /* returnam cea mai mica suma posibila pentru orice x
     * pornind de la k la n
     */
    return sum;
}


int max(int n, int a[], int b, int inf, int sup, int k)
{
    /**
     * Functia de calculare a maximului.
     * Nu inteleg totusi la ce-mi trebuie b,
     * probabil gresesc pe undeva.
     */
    int sum = 0;
    /* calculam si adunam liniar de la k la n maximul
     * fiecarui element ce duc implicit la maximul sumei
     */
    int i;
    for (i = k; i < n; ++i) {
        int coef = a[i];
        if (!coef) continue; // nu avem ce aduna
        else if (coef > 0) {
            /* pozitiv, deci numarul cel mai mare
             * va fi dat de capatul superior
             */
            sum += coef * sup;
        } else {
            // analog pentru capatul inferior
            sum += coef * inf;
        }
    }
    /* returnam cea mai mare suma posibila pentru orice x
     * pornind de la k la n
     */
    return sum;
}


int* solutie(int n, int a[], int b, int inf, int sup)
{
    /**
     * Functie ce calculeaza naiv solutia (adica pentru fiecare
     * coeficient alegem pe rand fiecare x, verificand cu functiile
     * min si max daca alegerea facuta poate ajuta la formarea solutiei,
     * si verificam la final daca are loc egalitatea).
     *
     * Aceasta returneaza un pointer la primul element din tablou,
     * tablou creat dinamic, avand in cazul unei solutii o valoare
     * diferita de NULL.
     */
    /* alocam dinamic memorie, nu mai are rost sa verificam
     * daca s-a alocat cu succes si declaram pointerul static
     * pentru ca folosim aceeasi functie in mod recursiv
     * astfel protejand integritatea continutului
     */
    static int* vec = NULL; // initial e 0
    /* la urmatorul apel vec va ramane neschimbat
     * nu va fi iar initializat cu NULL
     */
    // in sfarsit alocam memoria aia :))
    if (!vec) vec = (int*)malloc((size_t)n * sizeof(int));
    // similar procedam si pentru pozitie curenta
    static int pos = 0;
    // la fel si pentru minime si maxime
    static Extr* extr = NULL;
    if (!extr) {
        // alocam memoria si atribuim pointerului valoarea
        extr = (Extr*)malloc((size_t)n * sizeof(Extr));
        // generam sumele
        int i;
        for (i = 0; i < n; ++i) {
            extr[i].lo = min(n, a, b, inf, sup, i);
            extr[i].hi = max(n, a, b, inf, sup, i);
        }
        // acest calcul se face o singura data
    }
    static int sum = 0; // tinem cont de suma pana la pasul curent
    // si acum ceea ce functia trebuie sa faca de fiecare data
    // avem de generat pentru fiecare x
    int x;
    for (x = inf; x <= sup; ++x) {
        /* acum pentru acest x
        * calculam noul minim si maxim
        * si vedem daca rezultatul
        * final se afla intre ele
        */
        // suma curenta plus noul x * coeficientul sau
        int newSum = sum + x * a[pos];
        vec[pos] = x;
        if (pos == n - 1) {
            // am ajuns la final deci verificam ecuatia
            if (newSum == b) {
                // nu ne mai trebuiesc coeficientii
                free(extr);
                return vec; // avem solutie
            }
        } else {
            // verificam daca b se incadreaza
            if (b >= (newSum + extr[pos + 1].lo) &&
                b <= (newSum + extr[pos + 1].hi)) {
                /* actualizam suma dar pastram si
                 * vechea valoare pentru intoarcere
                 * la fel si pentru pozitie
                 */
                int tmpSum = sum;
                sum = newSum;
                ++pos;
                int* ret = solutie(n, a, b, inf, sup);
                if (ret) return ret; /* transmitem solutia mai
                                      * departe pentru ca o avem
                                      */
                --pos;
                sum = tmpSum;
            }
        }
    }
    if (!pos) {
        /* nu avem solutie si suntem pe prima pozitie
         * deci e clar ca nu avem nicio solutie,
         * asa ca eliberam
         */
        free(vec);
        free(extr);
    }
    return NULL; // nu avem solutie
}


int main()
{
    int n, b, inf, sup;
    printf("n b inf sup: ");
    scanf("%d %d %d %d", &n, &b, &inf, &sup);
    // alocam memorie pentru tabloul a
    int* a = (int*)malloc((size_t)n * sizeof(int));
    printf("Cei %d coeficienti: ", n);
    int i;
    for (i = 0; i < n; ++i) scanf("%d", &a[i]);
    int* ret = solutie(n, a, b, inf, sup); // citim tabloul
    free(a);
    if (ret) { // difera de NULL deci avem solutie
        // afisam
        puts("Solutia este...");
        int i;
        for (i = 0; i < n; ++i) printf("x%d: %d\n", i, ret[i]);
        // eliberam memoria
        free(ret);
    } else puts("Nu exista solutie.");
    fflush(stdout); // eliberam bufferul (in caz de nu apar rezultatele pe ecran)
    return 0;
}
