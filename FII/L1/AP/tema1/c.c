// c.c: I1


#include <stdio.h>


int cdigit(int nr)
{
    while (nr / 10) {
        int tmp = nr;
        nr = 0;
        while (tmp) {
            nr += tmp % 10;
            tmp /= 10;
        }
    }
    return nr;
}


int main()
{
    printf("Numar: ");
    int nr;
    scanf("%d", &nr);
    printf("Cifra de control este %d.\n",
           cdigit(nr));
    return 0;
}
