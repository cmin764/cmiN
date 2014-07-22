#include <stdio.h>

#include "digraf.h"


#define DBG 0
#define FLEN 32


int main()
{
    char fname[FLEN];
    fputs("Nume fisier: ", stdout);
    scanf("%s", fname);
    Digraf digraf;
    #if DBG
    fprintf(stderr, "fname: %s\n", fname);
    #endif
    creeaza(&digraf, fname);
    do {
        puts("[1] Grad interior");
        puts("[2] Grad exterior");
        puts("[3] Tare conex");
        puts("[0] Iesire");
        fputs(">>> ", stdout);
        int ask;
        scanf("%d", &ask);
        if (ask == 0)
            break;
        else if (ask == 1 || ask == 2) {
            fputs("Varf: ", stdout);
            int node;
            scanf("%d", &node);
            if (ask == 1)
                printf("%d\n", grad_int(digraf, node));
            else
                printf("%d\n", grad_ext(digraf, node));
        } else if (ask == 3)
            if (este_tare_conex(digraf))
                puts("Este tare conex");
            else
                puts("Nu este tare conex");
        else
            puts("Optiune invalida");
    } while (1);
    return 0;
}
