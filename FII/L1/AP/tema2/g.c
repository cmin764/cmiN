// d: afisarea elementelor unei matrici in spirala


#include <stdio.h>
#include <stdlib.h>


void spirala(int nr, int** mat, int level)
{
    for (int i = level; i < nr - level; ++i)
        printf("%d ", mat[level][i]);
    for (int i = level + 1; i < nr - level; ++i)
        printf("%d ", mat[i][nr - level - 1]);
    for (int i = nr - 2 - level; i >= level; --i)
        printf("%d ", mat[nr - level - 1][i]);
    for (int i = nr - 2 - level; i >= level + 1; --i)
        printf("%d ", mat[i][level]);
    if (level < nr / 2)
        spirala(nr, mat, level + 1);
}


void test(int nr, int** mat)
{
    for (int i = 0; i < nr; ++i) {
        for (int j = 0; j < nr; ++j)
            printf("%d ", mat[i][j]);
        putchar('\n');
    }
}


int main()
{
    printf("Dimensiune: ");
    int nr;
    scanf("%d", &nr);
    int** mat = (int**)malloc(nr * sizeof(int*));
    puts("Elemente:");
    for (int i = 0; i < nr; ++i) {
        mat[i] = (int*)malloc(nr * sizeof(int));
        printf("#%d: ", i + 1);
        for (int j = 0; j < nr; ++j)
            scanf("%d", &mat[i][j]);
    }
    //test(nr, mat);
    spirala(nr, mat, 0);
    putchar('\n');
    for (int i = 0; i < nr; ++i)
        free(mat[i]);
    free(mat);
    return 0;
}
