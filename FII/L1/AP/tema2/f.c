// f: ordonarea diagonalei principale prin interschimbari


#include <stdio.h>
#include <stdlib.h>


typedef struct {
    /**
     * Structura ce retine valoarea
     * si pozitia elementului.
     */
    int nr;
    int lin, col;
} Elem;


void elem_set(Elem* elem, int nr, int lin, int col)
{
    elem->nr = nr;
    elem->lin = lin;
    elem->col = col;
}


static inline int compare(const void* first, const void* second)
{
    /* compara B cu A si daca A < B
       atunci B, A */
    return ((const Elem*)second)->nr -
           ((const Elem*)first)->nr;
}


int swap_line(int n, int** mat, int lin1, int lin2)
{
    if (lin1 == lin2)
        return 0; // nimic de schimbat
    int* tmp = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i)
        tmp[i] = mat[lin1][i];
    for (int i = 0; i < n; ++i)
        mat[lin1][i] = mat[lin2][i];
    for (int i = 0; i < n; ++i)
        mat[lin2][i] = tmp[i];
    free(tmp);
    return 1;
}


int swap_column(int n, int** mat, int col1, int col2)
{
    if (col1 == col2)
        return 0; // nimic de schimbat
    int* tmp = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i)
        tmp[i] = mat[i][col1];
    for (int i = 0; i < n; ++i)
        mat[i][col1] = mat[i][col2];
    for (int i = 0; i < n; ++i)
        mat[i][col2] = tmp[i];
    free(tmp);
    return 1;
}


void show(int n, int** mat, int moves,
          int where /* 0-l 1-c */, int first, int second)
{
    printf("#%2d\n", moves);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            printf("%d ", mat[i][j]);
        putchar('\n');
    }
    if (!where)
        printf("Linie: ");
    else
        printf("Coloana: ");
    printf("%d-%d\n", first + 1, second + 1);
    putchar('\n');
}


void process(int n, int** mat)
{
    /**
     * Mai intai stabilim care sunt elementele
     * diagonalei principale si le fixam pozitiile
     * pe coloane, apoi interschimbam liniile
     * pentru a aduce elementele pe linii in ordine
     * descrescatoare.
     * Analog interschimbam coloanele.
     * O(N^2)
     */
    // cream un vector cu indici pentru pozitii
    Elem* elems = (Elem*)malloc(n * sizeof(Elem));
    for (int i = 0; i < n; ++i)
        elem_set(elems + i, mat[i][i], i, i);
    /* sortam valorile dupa valoare
       prin functia `compare` */
    qsort(elems, n, sizeof(Elem), compare);
    int moves = 0; // a cata schimbare

    // interschimbam coloanele
    for (int i = 0; i < n; ++i) {
        /* aducem coloana corespunzatoare
           pe pozitia i */
        int ret = swap_column(n, mat, i, elems[i].col);
        if (!ret)
            continue; // neschimbat
        /* actualizam si pozitia elementelor
           cautand elementul ce se afla pe `i` */
        for (int j = 0; j < n; ++j)
            if (elems[j].col == i) {
                // gasit
                elems[j].col = elems[i].col;
                break;
            }
        show(n, mat, ++moves, 1, i, elems[i].col);
        elems[i].col = i;
    }
    // acelasi lucru si pentru linii
    for (int i = 0; i < n; ++i) {
        /* aducem linia corespunzatoare
           pe pozitia i */
        int ret = swap_line(n, mat, i, elems[i].lin);
        if (!ret)
            continue; // neschimbat
        /* actualizam si pozitia elementelor
           cautand elementul ce se afla pe `i` */
        for (int j = 0; j < n; ++j)
            if (elems[j].lin == i) {
                // gasit
                elems[j].lin = elems[i].lin;
                break;
            }
        show(n, mat, ++moves, 0, i, elems[i].lin);
        elems[i].lin = i;
    }
    free(elems);
}


int main()
{
    int n, ** mat;
    printf("Dimensiune: ");
    scanf("%d", &n);
    // alocam memorie pentru N pointeri
    mat = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        /* pentru fiecare pointer alocam
           memorie pentru N elemente */
        mat[i] = (int*)malloc(n * sizeof(int));
        printf("#%d: ", i + 1);
        for (int j = 0; j < n; ++j)
            scanf("%d", &mat[i][j]);
    }
    putchar('\n');
    process(n, mat);
    /* eliberam memoria fiecarui vector
       apoi a vectorului de pointeri */
    for (int i = 0; i < n; ++i)
        free(mat[i]);
    free(mat);
    return 0;
}
