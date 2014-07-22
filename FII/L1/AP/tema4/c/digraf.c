#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "digraf.h"


void creeaza(Digraf * digraf, char * fname)
{
    FILE * fin = fopen(fname, "r");
    if (!fin) {
        fprintf(stderr, "Eroare: fisierul \
nu a putut fi deschis\n");
        exit(EXIT_FAILURE);
    }
    // citim numarul de varfuri
    fscanf(fin, "%d", &digraf->nodes);
    // citim numarul de arce
    fscanf(fin, "%d", &digraf->edges);
    /* acum pentru fiecare arc citim
       perechile de noduri */
    int ** l; // lista de adiacenta
    l = (int **)malloc((digraf->nodes + 1) *\
                       sizeof(int *));
    for (int i = 1; i <= digraf->nodes; ++i) {
        l[i] = (int*)malloc(sizeof(int));
        l[i][0] = 0;
        /* ^ in primul element retinem mereu
           numarul de vecini ai varfului `i` */
    }
    for (int i = 0; i < digraf->edges; ++i) {
        int x, y;
        fscanf(fin, "%d %d", &x, &y);
        // nodului `x` ii adaugam vecinul `y`
        l[x] = (int *)realloc(l[x], sizeof(int) *\
            (1 + ++l[x][0]));
        l[x][l[x][0]] = y;
    }
    digraf->list = l; // salvam lista
    fclose(fin);
}


int grad_int(Digraf digraf, int node)
{
    /**
     * Pentru fiecare nod, functia citeste
     * fiecare vecin si vede daca coincide
     * cu varful `node`, iar daca coincide
     * numaram ca intrare.
     */
    int grad = 0;
    for (int i = 1; i <= digraf.nodes; ++i)
        for (int j = 1; j <= digraf.list[i][0]; ++j)
            if (digraf.list[i][j] == node) {
                ++grad;
                break;
            }
    return grad;
}


int grad_ext(Digraf digraf, int node)
{
    /**
     * Returneaza numarul de vecini
     * ai varfului `node`.
     */
    return digraf.list[node][0];
}



static void dfs(int ** list, int start,
                int * seen)
{
    // vizitam varful curent
    seen[start] = 1;
    /* vizitam toti vecinii nevizitati ai
       nodului curent */
    for (int i = 1; i <= list[start][0]; ++i) {
        int node = list[start][i];
        if (seen[node]) // daca l-am vizitat deja
            continue; // verificam urmatorul vecin
        // vizitam varful `node`
        dfs(list, node, seen);
    }
}


int este_tare_conex(Digraf digraf)
{
    /**
     * Pentru oricare doua noduri `u` si `v`
     * se verifica daca exista drum de la unul
     * la celalalt si invers.
     *
     * Mai simplu, pentru fiecare varf se face o
     * explorare in adancime si se viziteaza cat
     * mai multe varfuri, de fiecare data verificandu-se
     * cate vizite unice s-au facut si pentru tare
     * conexitate trebuie ca numarul de vizite sa
     * coincida intotdeauna cu numarul de varfuri.
     */
    size_t size = sizeof(int) * (digraf.nodes + 1);
    int * seen = (int *)malloc(size);
    for (int i = 1; i <= digraf.nodes; ++i) {
        // reinitializam `seen`
        memset(seen, 0, size);
        // exploram in adancime
        dfs(digraf.list, i, seen);
        // numaram cate noduri am reusit a vizita
        int cnt = 0;
        for (int j = 1; j <= digraf.nodes; ++j)
            if (seen[j])
                ++cnt;
        if (cnt != digraf.nodes) {
            free(seen);
            return 0; // nu este tare conex
        }
    }
    free(seen);
    return 1; // este tare conex
}
