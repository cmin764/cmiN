#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define combin comb2


int number(char * arg)
{
    for (int i = 0; arg[i]; ++i)
        if (arg[i] < '0' || arg[i] > '9')
            return 0;
    return 1;
}


int fac(int n)
{
    if (n == 0 || n == 1)
        return 1;
    return n * fac(n - 1);
}


int comb1(int n, int k)
{
    return (fac(n) / (fac(k) * fac(n - k)));
}


int comb2(int n, int k)
{
    if (n == 0)
        return 0;
    if (k == 0 || n == k)
        return 1;
    return comb2(n - 1, k) + comb2(n - 1, k - 1);
}


void fill(int pos, int len,
          int ** mat, int * vec, int lim)
{
    static int at = 0;
    if (!pos)
        at = 0;

     if (pos == len) {
        for (int i = 0; i < len; ++i)
            mat[at][i] = vec[i];
        ++at;
        return;
    }

    int i = 1;
    if (pos)
        i = vec[pos - 1] + 1;
    for (; i <= lim; ++i) {
        vec[pos] = i;
        fill(pos + 1, len, mat, vec, lim);
    }
}


void test(int *** parts, int * partLens, int nr)
{
    for (int i = 1; i <= nr; ++i) {
        for (int j = 0; j < partLens[i]; ++j) {
            putchar('{');
            for (int k = 0; k < i - 1 ; ++k)
                printf("%d, ", parts[i][j][k]);
            printf("%d}", parts[i][j][i - 1]);
            putchar(' ');
        }
        putchar('\n');
    }
}


static inline int check_repeat(int *** sol, int len, int lim)
{
    int size = sizeof(int) * (lim + 1);
    int * nrs = (int *)malloc(size);
    memset(nrs, 0, size);

    for (int i = 0; i < len; ++i) {
        int dim = (int)sol[i][0];
        int * vec = sol[i][1];
        for (int j = 0; j < dim; ++j)
            if (nrs[vec[j]]) {
                free(nrs);
                return 1;    // same number found twice
            } else
                nrs[vec[j]] = 1;
    }

    free(nrs);
    return 0;
}


static inline int check_useall(int *** sol, int len, int lim)
{
    int size = sizeof(int) * (lim + 1);
    int * nrs = (int *)malloc(size);
    memset(nrs, 0, size);

    for (int i = 0; i < len; ++i) {
        int dim = (int)sol[i][0];
        int * vec = sol[i][1];
        for (int j = 0; j < dim; ++j)
            nrs[vec[j]] = 1;
    }

    for (int i = 1; i <= lim; ++i)
        if (!nrs[i]) {
            free(nrs);
            return 0;
        }

    free(nrs);
    return 1;
   
}


static inline void show(int *** sol, int len)
{
    putchar('{');
    for (int i = 0; i < len - 1; ++i) {
        int dim = (int)sol[i][0];
        int * vec = sol[i][1];
        putchar('{');
        for (int j = 0; j < dim - 1; ++j)
            printf("%d, ", vec[j]);
        printf("%d}, ", vec[dim - 1]);
    }
    int dim = (int)sol[len - 1][0];
    int * vec = sol[len - 1][1];
    putchar('{');
    for (int i = 0; i < dim - 1; ++i)
        printf("%d, ", vec[i]);
    printf("%d}}\n", vec[dim - 1]);
}


void bt(int pos, int lin, int col, int total, int lim,
          int *** parts, int * partLens, int *** sol)
{
    if (total == lim) {
        if (check_useall(sol, pos, lim))
            show(sol, pos);
        return;
    }

    if (col >= partLens[lin]) {
        ++lin;
        col = 0;
    }
    if (lin > lim)
        return;

    for (; lin <= lim; ++lin, col = 0) {
        if (lin + total > lim)
            continue;
        for (; col < partLens[lin]; ++col) {
            sol[pos][0] = (int *)lin;
            sol[pos][1] = parts[lin][col];
            if (check_repeat(sol, pos + 1, lim))
                continue;
            bt(pos + 1, lin, col + 1, total + lin, lim,
               parts, partLens, sol);
        }
    }
}


void process(int nr)
{
    int *** parts = (int ***)malloc(sizeof(int **) * (nr + 1));
    int * partLens = (int *)malloc(sizeof(int) * (nr + 1));

    for (int i = 1; i <= nr; ++i) {
        int size = combin(nr, i);
        parts[i] = (int **)malloc(sizeof(int *) * size);
        partLens[i] = size;
        for (int j = 0; j < size; ++j)
            parts[i][j] = (int *)malloc(sizeof(int) * i);

        int * tmp = (int *)malloc(sizeof(int) * i);
        fill(0, i, parts[i], tmp, nr);
         free(tmp);
    }

    // make combinations
    int *** sol = (int ***)malloc(sizeof(int **) * nr);
    for (int i = 0; i < nr; ++i)
        /* prima coloana = lungimea vectorului controlat
           de pointerul din a doua coloana */
        sol[i] = (int **)malloc(sizeof(int *) * 2);
    
    bt(0, 1, 0, 0, nr, parts, partLens, sol);
    //test(parts, partLens, nr);

    for (int i = 0; i < nr; ++i)
        free(sol[i]);
    free(sol);    // continutul pointerilor la pointeri
                  // se elibereaza mai jos

    // release heap
    for (int i = 1; i <= nr; ++i) {
        for (int j = 0; j < partLens[i]; ++j)
            free(parts[i][j]);
        free(parts[i]);
    }
    free(parts);
    free(partLens);
}


int main(int argc, char * argv[])
{
    if (argc != 2) {
        printf("Usage: %s NUMBER\n", argv[0]);
        return 0;
    }
    if (!number(argv[1])) {
        fputs("impossible\n", stderr);
        return 1;
    }

    // extract number from parameter
    int nr;
    sscanf(argv[1], "%d", &nr);

    process(nr);
    return 0;
}
