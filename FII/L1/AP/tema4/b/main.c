/*
 * main: explorarea arborelui in adancime si latime
 * compileaza cu: gcc -Wall -std=c99 -o main arbin.c queue.c main.c
 */


#include <stdio.h>
#include <stdlib.h>

#include "arbin.h"


#define N 64
#define DBG 0


void perr(int rc)
{
    if (rc) {
        puts("Eroare: memorie insuficienta");
        exit(rc);
    }
}


int main()
{
    fputs("Secventa: ", stdout);
    char str[N];
    scanf("%s", str);
    Node root = NULL;
    int rc = tree_create(&root, str);
    perr(rc);
    #if DBG
    fprintf(stderr, "root: %p\n", root);
    #endif
    do {
        puts("[1] Adancime");
        puts("[2] Latime");
        puts("[3] Oglindit");
        puts("[4] Nivel");
        puts("[5] Numarare");
        puts("[6] Numarare'");
        puts("[7] Al k-lea element");
        puts("[0] Iesire");
        fputs(">>> ", stdout);
        int ask;
        scanf("%d", &ask);
        if (ask == 0)
            break;
        else if (ask == 1)
            do {
                puts("[1] Preordine");
                puts("[2] Inordine");
                puts("[3] Postordine");
                puts("[0] Iesire");
                fputs(">>> ", stdout);
                int ask;
                scanf("%d", &ask);
                if (ask == 0)
                    break;
                else if (ask == 1)
                    tree_dfs(root, 0);
                else if (ask == 2)
                    tree_dfs(root, 1);
                else if (ask == 3)
                    tree_dfs(root, 2);
                else
                    puts("Optiune invalida");
                if (ask >= 1 && ask <= 3)
                    putchar('\n');
            } while (1);
        else if (ask == 2) {
            int rc = tree_bfs(root);
            perr(rc);
            putchar('\n');
        } else if (ask == 3)
            tree_mirror(root);
        else if (ask == 4) {
            fputs("Nivel: ", stdout);
            int lvl;
            scanf("%d", &lvl);
            tree_lvl(root, lvl, 1);
            putchar('\n');
        } else if (ask == 5)
            printf("%d\n", tree_cnt1(root));
        else if (ask == 6)
            printf("%d\n", tree_cnt2(root));
        else if (ask == 7) {
            fputs("K: ", stdout);
            int k;
            scanf("%d", &k);
            char chr = '\0';
            tree_kelem(root, k, &chr, 1);
            if (chr)
                printf("%c\n", chr);
            else
                puts("Elementul nu a fost gasit");
        } else
            puts("Optiune invalida");
    } while (1);
    // facem curatenie
    tree_destroy(&root);
    return 0;
}
