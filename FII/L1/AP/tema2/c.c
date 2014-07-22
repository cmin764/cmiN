/* c: subsecventa de suma maxima
 *
 * Se construieste un vector de sume partiale
 * (sp[i] = sum(v[k], k->0,i)) cu ajutorul caruia
 * se determina subsecventa de lungime maxima,
 * cautand elementul maxim apoi pe cel minim din
 * stanga sa.
 */


#include <stdio.h> // i/o
#include <stdlib.h> // alocare dinamica
#include <limits.h> // -inf/+inf


void max_sum(int nr, int* vec, int* lo, int* hi)
{
    // vector de sume partiale
    int* parSum = (int*)malloc(nr * sizeof(int));
    parSum[0] = vec[0];
    for (int i = 1; i < nr; ++i)
        parSum[i] = vec[i] + parSum[i - 1];
    // gasirea sumei partiale minime/maxime
    int minNr = LONG_MAX, maxNr = LONG_MIN;
    int tail = nr;
    for (int i = 0; i < nr; ++i)
        if (parSum[i] > maxNr) {
            maxNr = parSum[i];
            tail = i;
        }
    // cautarea minimului in stanga maximului
    int head;
    for (int i = 0; i < tail; ++i)
        if (parSum[i] < minNr) {
            minNr = parSum[i];
            head = i;
        }
    free(parSum);
    // salvarea datelor
    *lo = head + 1;
    *hi = tail + 1;
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
    int lo = -1, hi = -1;
    max_sum(nr, vec, &lo, &hi);
    printf("Subsecventa este ");
    for (int i = lo; i < hi; ++i)
        printf("%d ", vec[i]);
    putchar('\n');
    free(vec);
    return 0;
}
