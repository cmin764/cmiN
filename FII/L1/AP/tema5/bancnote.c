#include <stdio.h>
#include <stdlib.h>


void bt(int pos, int total, int sum,
        int * sol, int ** banc, int bancNr,
        int last)
{
    if (total == sum) {
        // avem suma creata
        for (int i = 0; i < pos - 1; ++i)
            printf("%d+", sol[i]);
        printf("%d\n", sol[pos - 1]);
        return;
    }

    // incercam sa formam suma de bani
    for (int i = last; i < bancNr; ++i) {
        if (!banc[i][1])
            continue;    // nu mai avem
        if (total + banc[i][0] > sum)
            continue;    // prea mare
        // folosim o bancnota
        sol[pos] = banc[i][0];
        --banc[i][1];
        bt(pos + 1, total + banc[i][0], sum, sol,
           banc, bancNr, i);
        ++banc[i][1];
    }
}


int main()
{
    int sum, nr;
    fputs("Suma: ", stdout);
    scanf("%d", &sum);
    fputs("Numar: ", stdout);
    scanf("%d", &nr);

    // tipurile de bancnote
    int maxSol = 0;
    int ** banc = (int **)malloc(sizeof(int *) * nr);
    for (int i = 0; i < nr; ++i) {
        int tValue, tNr;
        printf("Tip, Numar [%d]: ", i);
        scanf("%d %d", &tValue, &tNr);
        banc[i] = (int *)malloc(sizeof(int *) * 2);
        banc[i][0] = tValue;
        banc[i][1] = tNr;
        maxSol += tNr;
    }

    int * sol = (int *)malloc(sizeof(int *) * maxSol);
    bt(0, 0, sum, sol, banc, nr, 0);

    for (int i = 0; i < nr; ++i)
        free(banc[i]);
    free(banc);
    free(sol);
    return 0;
}
