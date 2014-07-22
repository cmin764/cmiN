#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define SEP ' '


void prime_gen(int ** primes, int * len, int nr)
{
    for (int i = 3; i <= nr; ++i) {
        int isq = sqrt(i);
        int good = 1;
        for (int j = 0; good && j < *len &&
             (*primes)[j] <= isq; ++j)
            if (!(i % (*primes)[j]))
                good = 0;
        if (good) {
            *primes = (int *)realloc(*primes, sizeof(int) *\
                                       ++(*len));
            (*primes)[*len - 1] = i;
        }
    }
}



void test(int * primes, int len)
{
    for (int i = 0; i < len; ++i)
        printf("%d ", primes[i]);
    putchar('\n');
}


void bt(int pos, int * tmp, int sum, int nr,
        int * primes, int len, int lasti)
{
    if (sum == nr) {
        for (int i = 0; i < pos - 1; ++i)
            printf("%d+", tmp[i]);
        printf("%d%c", tmp[pos - 1], SEP);
        return;
    }

    for (int i = lasti; i < len; ++i) {
        if (sum + primes[i] > nr)
            continue;
        tmp[pos] = primes[i];
        bt(pos + 1, tmp, sum + primes[i],
           nr, primes, len, i);
    }
}


void process(int nr)
{
    /* generam toate numerele prime
       mai mici sau egale cu nr */
    int * primes = (int *)malloc(sizeof(int));
    int primeLen = 1;
    primes[0] = 2;
    prime_gen(&primes, &primeLen, nr);
    //test(primes, primeLen);

    int * tmp = (int *)malloc(sizeof(int) * (nr / 2));
    bt(0, tmp, 0, nr, primes, primeLen, 0);
    putchar('\n');
    free(tmp);

    free(primes);
}


int main()
{
    int nr;
    fputs("Numar: ", stdout);
    scanf("%d", &nr);
    process(nr);
    return 0;
}
