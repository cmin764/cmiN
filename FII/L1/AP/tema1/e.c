// e.c: I1


#include <stdio.h>
#include <math.h>


int prim(int nr)
{
    int hi, lo;
    hi = sqrt(nr);
    for (lo = 2; lo <= hi; ++lo) {
        if (!(nr % lo)) return 0;
    }
    return 1; // prim
}


int main()
{
    printf("Numar: ");
    int nr;
    scanf("%d", &nr);
    if (prim(nr)) puts("Numarul este prim.");
    else puts("Numarul nu este prim.");
    return 0;
}
