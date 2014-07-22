// f.c: I1


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
    printf("Numar de perechi: ");
    int nr;
    scanf("%d", &nr);
    int last = 3, i;
    for (i = 1; i <= nr; ++i) {
        int found = 0;
        if (prim(last + 2)) {
            found = 1;
            printf("#%d (%d, %d)\n", i, last, last + 2);
        }
        last += 2;
        if (!found) {
            while (!prim(last)) last += 2;
            --i;
        }
    }
    return 0;
}
