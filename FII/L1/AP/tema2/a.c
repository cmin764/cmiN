// a: diferenta maxima intre oricare doua numere


#include <stdio.h> // i/o
#include <math.h> // modul
#include <stdlib.h> // alocare dinamica
#include <limits.h> // -inf/+inf


int max_diff(int len, int* vec)
{
    int lo = LONG_MAX, hi = LONG_MIN;
    for (int i = 0; i < len; ++i) {
        // actualizarea minimului si
        // a maximului
        if (vec[i] < lo) lo = vec[i];
        if (vec[i] > hi) hi = vec[i];
    }
    // diferenta maxima in modul
    return abs(hi - lo);
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
    int diff = max_diff(nr, vec);
    free(vec);
    printf("Diferenta maxima este %d\n", diff);
    return 0;
}
