#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "digraf.h"
#include "pqueue.h"
#include "stack.h"


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


/* problema 4 */


int contine_groapa(Digraf digraf)
{
    for (int i = 1; i <= digraf.nodes; ++i)
        if (grad_int(digraf, i) == digraf.nodes - 1 &&
            grad_ext(digraf, i) == 0)
            return i;
    return -1;
}


int min_dist(Digraf digraf, int x, int y)
{
    /* vectorul de distante unde `dist[y]`
       reprezinta distanta minima de la
       sursa `x` la destinatia `y` */
    size_t size = sizeof(int) * (digraf.nodes + 1);
    int * dist = (int *)malloc(size);
    for (size_t i = 0; i < size / sizeof(int); ++i)
        dist[i] = LONG_MAX;
    dist[x] = 0;
    // cream coada si adaugam sursa
    pqueue_t pqueue;
    pqueue_create(&pqueue);
    key_t elem;
    elem.value = x;
    elem.priority = dist[x];
    pqueue_push(&pqueue, elem);
    /* cat timp coada nu este goala,
       continuam cu cea mai scurta distanta */
    while (!pqueue_empty(&pqueue)) {
        // extragem nodul
        int node = pqueue_pop(&pqueue).value;
        if (node == y)
            /* nodul scos este chiar destinatia,
               deci inseamna ca am determinat cea
               mai scurta distanta de la `x` la `y` */
            break;
        for (int i = 1; i <= digraf.list[node][0]; ++i) {
            int nbr = digraf.list[node][i]; // vecinul
            if (dist[node] + 1 < dist[nbr]) {
                dist[nbr] = dist[node] + 1;
                key_t elem;
                elem.value = nbr;
                elem.priority = dist[nbr];
                pqueue_push(&pqueue, elem);
            }
        }
    }
    pqueue_destroy(&pqueue);
    int ret = dist[y];
    free(dist);
    return ret;
}


void distruge(Digraf * digraf)
{
    for (int i = 1; i <= digraf->nodes; ++i)
        free(digraf->list[i]);
    free(digraf->list);
    digraf->nodes = 0;
    digraf->edges = 0;
}


Digraf transpus(Digraf digraf)
{
    // copie a argumentului
    Digraf ret = digraf;
    /* pentru a crea transpusul trebuie sa reconstruim
       lista de adiacenta de asa natura incat fiecare
       vecin din lista initiala sa fie un nod ce are
       ca vecin nodul initial din care am luat fiecare
       vechi vecin pentru procesare */
    // alocam memorie pentur o noua lista
    ret.list = (int **)malloc(sizeof(int *) * \
                              (ret.nodes + 1));
    for (int node = 1; node <= digraf.nodes; ++node) {
        ret.list[node] = (int *)malloc(sizeof(int));
        ret.list[node][0] = 0;
    }
    for (int node = 1; node <= digraf.nodes; ++node)
        for (int i = 1; i <= digraf.list[node][0]; ++i) {
            int nbr = digraf.list[node][i];
            // vecinul `nbr` are ca vecin pe nodul `node`
            ret.list[nbr] = (int *)realloc(ret.list[nbr],
                sizeof(int) * (1 + ++ret.list[nbr][0]));
            ret.list[nbr][ret.list[nbr][0]] = node;
        }
    return ret;
}


static inline int min(int first, int second)
{
    return first < second ? first : second;
}


static void tarjan(int node, int ** list, int * idx,
                   int * low, stack_t * pStack,
                   int * inStack)
{
    static int index = 1; // indexul de la care incepem
    // initializam nodul neatins, incrementand indexul
    idx[node] = low[node] = index++;
    // adaugam acest nod in stiva si-l marcam ca adaugat
    stack_push(pStack, (stack_key_t)node);
    inStack[node] = 1;
    /* acum pentru fiecare vecin a acestui nod verificam
       daca NU a mai fost vizitat, si daca da atunci il
       vizitam recursiv cu un nou `index` (incrementat),
       daca a mai fost vizitat inseamna ca ori face parte
       din componenta noastra conexa, ori a facut parte
       dintr-alta, astfel trecem la urmatorul vecin, fara
       sa actualizam vreun `low`, dar daca face parte din
       componenta conexa curenta, actualizam `low` ca sa
       nu cumva sa scoatem nodul curent aiurea din stiva */
    for (int i = 1; i <= list[node][0]; ++i) {
        int nbr = list[node][i]; // vecinul `i`
        if (!idx[nbr]) {
            tarjan(nbr, list, idx, low, pStack, inStack);
            low[node] = min(low[node], low[nbr]);
        } else if (inStack[nbr])
            low[node] = min(low[node], low[nbr]);
    }
    /* acum verificam daca nodul curent nu a avut vecini
       sau a fost deja atins si nu face parte din
       componenta conexa curenta */
    if (idx[node] == low[node]) {
        // avem componenta conexa
        int key;
        do {
            key = (int)stack_pop(pStack);
            printf("%d ", key);
        } while (key != node);
        putchar('\n');
    }
}


void comp_conexe(Digraf digraf)
{
    /* aplicam algoritmul lui Tarjan, dupa o paradigma
       plus-minus, ce era in timp patratic, acest
       algoritm avand un timp liniar, similar unei
       parcurgeri a digrafului */
    // indexul, slaba legatura si apartenenta la stiva
    int * idx, * low, * inStack;
    size_t size = sizeof(int) * (digraf.nodes + 1);
    idx = (int *)malloc(size);
    low = (int *)malloc(size);
    inStack = (int *)malloc(size);
    memset(idx, 0, size);
    memset(inStack, 0, size);
    /* stiva in care retinem nodurile ce
       alcatuiesc componente conexe */
    stack_t stack;
    stack_create(&stack);
    for (int i = 1; i <= digraf.nodes; ++i)
        if (!idx[i])
            tarjan(i, digraf.list, idx, low,
                   &stack, inStack);
    stack_destroy(&stack);
    free(idx);
    free(low);
    free(inStack);
}
