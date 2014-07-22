// a.c: I1


#include <stdio.h>


int palin(int nr)
{
    /**
     * Functie ce returneaza:
     * 1 - daca numarul este palindrom
     * 0 - in caz contrar
     */
    int tmp = nr, newNr = 0;
    while (tmp) {
        newNr = newNr * 10 + tmp % 10;
        tmp /= 10;
    }
    if (newNr == nr) return 1; // palindrom
    return 0;
}


int main()
{
    printf("Introduceti un numar: ");
    int nr;
    scanf("%d", &nr);
    if (palin(nr)) puts("Este palindrom.");
    else puts("Nu este palindrom");
    return 0;
}
