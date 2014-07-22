// d: rearanjarea elementelor: pare -> impare


#include <stdio.h> // i/o
#include <stdlib.h> // alocare dinamica


#define OPT 1 // 1-f1 (OPTimized version)
              // 0-f2


void f1(int nr, int* vec)
{
    // timp liniar
    int* tmp = (int*)malloc(nr * sizeof(int));
    int crt = 0;
    // scrierea numerelor pare
    for (int i = 0; i < nr; ++i)
        if (!(vec[i] & 1))
            tmp[crt++] = vec[i];
    // si acum cele impare
    for (int i = 0; i < nr; ++i)
        if (vec[i] & 1)
            tmp[crt++] = vec[i];
    // vec "=" tmp
    for (int i = 0; i < nr; ++i)
        vec[i] = tmp[i];
    free(tmp);
}


void f2(int nr, int* vec)
{
    // timp patratic, dar fara vector temporar
    int moved = 0; // numere impare deja mutate
    for (int i = nr - 1; i >= 0; --i)
        if (vec[i] & 1) {
            // move the number here
            int to = nr - moved - 1;
            for (int j = i; j < to; ++j) {
                int tmp = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = tmp;
            }
            ++moved;
        }
}


int main()
{
    int* vec;
    int nr;
    printf("Numarul de numere: ");
    scanf("%d", &nr);
    vec = (int*)malloc(nr * sizeof(int));
    printf("Numerele: ");
    for (int i = 0; i < nr; ++i)
        scanf("%d", vec + i);
    if (OPT) f1(nr, vec);
    else f2(nr, vec);
    printf("Dupa rearanjare ");
    for (int i = 0; i < nr; ++i)
        printf("%d ", vec[i]);
    free(vec);
    putchar('\n');
    return 0;
}
