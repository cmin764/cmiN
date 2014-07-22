#include <stdio.h>


#define N 100 /* unde compilatorul gaseste N
                 inlocuieste cu valoarea definita */
#define PAD 3 /* spatiere la afisaj pentru fiecare numar al celulei
                 daca afisajul e "inghesuit" mai mareste valoarea */
#define DBG 0 // pentru debug


int mat[N][N]; // matricea patratica
char format[4]; // formatarea fiecarei celule


void show(int mat[][N], int dim, FILE *where)
{
    /// Functie pentru afisarea matricei.
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j)
            fprintf(where, format, mat[i][j]);
        fputc('\n', where);
    }
}


void build(int mat[][N], int dim)
{
    /**
     * Functie iterativa ce completeaza matricea in spirala.
     * Se pleaca din "centru" si se fac cate 2 miscari
     * din ciclul sus -> dreapta -> jos -> stanga, apoi
     * daca mai raman muchii de afisat se depaseste cu 1
     * muchia curenta si se afiseaza inca 2 muhcii s.a.m.d.
     */
    int nr = 1; // cu ce incepem completarea
    /* stabilim centrul
       si daca dimensiunea este para
       atunci scadem 1 pentru a incepe
       din coltul corect */
    int cen = dim / 2 - !(dim % 2);
    // initializam valoarea din centru
    mat[cen][cen] = nr++;
    #if DBG
    fprintf(stderr, "cen: %d\n", cen);
    #endif
    /* plecand din coltul stanga sus, trebuie sa facem
     * jos, stanga, asta inseamna sa setam ca
     * ultima miscare pe "dreapta" */
    char last = 'r'; // ultima mutare
    int i = cen, j = cen + 1, level = 1; // linia, coloana, nivelul
    // cat timp suntem inauntrul matricei
    while (0 <= i && i < dim && 0 <= j && j < dim) {
        // facem 2 miscari
        for (int k = 0; k < 2; ++k)
            switch (last) {
                /* cazul in care ultima miscare a fost: */
                case 'u': // in sus
                // deci mergem la dreapta `level` celule
                for (int pad = 0; pad < level; ++pad)
                    mat[i][j++] = nr++;
                last = 'r'; // actualizam ultima miscare
                break;

                case 'r': // la dreapta
                // deci mergem in jos `level` celule
                for (int pad = 0; pad < level; ++pad)
                    mat[i++][j] = nr++;
                last = 'd'; // actualizam ultima miscare
                break;

                case 'd': // in jos
                // deci mergem la stanga `level` celule
                for (int pad = 0; pad < level; ++pad)
                    mat[i][j--] = nr++;
                last = 'l'; // actualizam ultima miscare
                break;

                case 'l': // la stanga
                // deci mergem in sus `level` celule
                for (int pad = 0; pad < level; ++pad)
                    mat[i--][j] = nr++;
                last = 'u'; // actualizam ultima miscare
                break;
            }
        /* acum dupa fiecare 2 miscari trebuie sa:
           - completam celula curenta
           - mai parcurgem o celula (in directia `last`)
           - crestem nivelul */
        mat[i][j] = nr++;
        switch (last) {
            case 'u':
            --i;
            break;

            case 'r':
            ++j;
            break;

            case 'd':
            ++i;
            break;

            case 'l':
            --j;
            break;
        }
        ++level;
        #if DBG
        show(mat, dim, stderr);
        fputc('\n', stderr);
        #endif
    }
}


int main()
{
    /* stabilim formatul
       mai exact pe cate spatii sa fie
       printat fiecare numar */
    format[0] = '%';
    format[1] = '0' + PAD;
    format[2] = 'd';
    format[3] = 0;
    #if DBG // nu lua in calcul directivele de genul asta :)
    fprintf(stderr, "format: %s\n", format);
    #endif
    printf("Dimensiune: ");
    int dim;
    scanf("%d", &dim);
    putchar('\n');
    build(mat, dim);
    show(mat, dim, stdout);
    return 0;
}
