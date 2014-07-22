/* e: existenta unui element majoritar
 *
 * Se considera primul element majoritar si
 * la fiecare aparitie a lui se incrementeaza
 * un contor, iar in caz contrar acesta se
 * decrementeaza. De fiecare data cand contorul
 * devine 0 se alege ca posibil element majoritar
 * termenul curent si se continua procesul in timp
 * liniar pana la finalul vectorului.
 * Se mai verifica o data daca ultimul element majoritar
 * chiar apare de n/2+1 ori in caz de contorul difera de 0.
 */


#include <stdio.h>
#include <stdlib.h>


int ismaj(int len, int* vec, int* maj)
{
    /**
     * Intoarce 0/1 si in cazul
     * lui 1 stocheaza in parametru
     * valoarea elementului majoritar.
     */
    int tmp, ctr = 0;
    for (int i = 0; i < len; ++i)
        if (!ctr) {
            // setam un nou element ca majoritar
            tmp = vec[i];
            ctr = 1;
        } else // verificam daca apare
               // sau nu
            if (vec[i] == tmp)
                ++ctr;
            else
                --ctr;
    if (!ctr)
        return 0;
    ctr = 0;
    for (int i = 0; i < len; ++i)
        if (vec[i] == tmp)
            ++ctr;
    if (ctr > len / 2) {
        *maj = tmp;
        return 1;
    }
    return 0;
}


int main()
{
    // crearea vectorului
    int len, * vec;
    printf("Numar elemente: ");
    scanf("%d", &len);
    vec = (int*)malloc(len * sizeof(int));
    // completarea lui
    printf("Elemente: ");
    for (int i = 0; i < len; ++i)
        scanf("%d", vec + i);
    // procesarea lui
    int ret, maj;
    ret = ismaj(len, vec, &maj);
    free(vec);
    if (ret)
        printf("Element majoritar %d\n", maj);
    else
        printf("Nu exista element majoritar\n");
    return 0;
}
