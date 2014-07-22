#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"


// definitiile prototipurilor private
static void dfs(int **, int, int *);


void graph_create(Graph * graph, char * fname)
{
    FILE * fin = fopen(fname, "r");
    if (!fin) {
        fprintf(stderr, "Eroare: fisierul \
nu a putut fi deschis\n");
        exit(EXIT_FAILURE);
    }
    // citim numarul de varfuri
    fscanf(fin, "%d", &graph->nodes);
    // citim numarul de arce
    fscanf(fin, "%d", &graph->edges);

    /* acum pentru fiecare arc citim
       perechile de noduri */
    int ** l; // lista de adiacenta
    l = (int **)malloc((graph->nodes + 1) *\
                       sizeof(int *));
    for (int i = 1; i <= graph->nodes; ++i) {
        l[i] = (int*)malloc(sizeof(int));
        l[i][0] = 0;
        /* ^ in primul element retinem mereu
           numarul de vecini ai varfului `i` */
    }

    for (int i = 0; i < graph->edges; ++i) {
        /* spre deosebire de graful orientat
           in graful neorientat `y` este vecinul
           lui `x`, dar si invers */
        int x, y;
        fscanf(fin, "%d %d", &x, &y);
        // nodului `x` ii adaugam vecinul `y`
        l[x] = (int *)realloc(l[x], sizeof(int) *\
            (1 + ++l[x][0]));
        l[x][l[x][0]] = y;
        // acelasi lucru si pentru `y`
        l[y] = (int *)realloc(l[y], sizeof(int) *\
            (1 + ++l[y][0]));
        l[y][l[y][0]] = x;
    }
    graph->list = l; // salvam lista
    fclose(fin);
}


void graph_destroy(Graph * graph)
{
    for (int i = 1; i <= graph->nodes; ++i)
        free(graph->list[i]);
    free(graph->list);
    graph->nodes = 0;
    graph->edges = 0;
}


int graph_is_tree(const Graph graph)
{
    /**
     * Functia verifica daca graful dat ca parametru
     * este un arbore.
     * Pentru a pastra lucrurile simple si ca executia
     * algoritmului sa ia un timp liniar, ajunge sa
     * verificam daca graful are N-1 muchii (unde N
     * este numarul de noduri) si sa parcurgem graful
     * pana vizitam toate nodurile posibile.
     *
     * Daca graful are mai putine muchii, atunci nu
     * are cum sa fie conex, deci nu poate fi arbore.
     * Daca graful are mai multe noduri, atunci cu
     * siguranta contine cicluri (si poate fi conex
     * sau nu), dar arborele trebuie sa fie aciclic.
     *
     * Daca nodurile sunt in regula, urmeaza sa le
     * vizitam O(M). Daca am reusit sa le vizitam
     * pe toate O(N) atunci inseamna ca avem un graf
     * neorientat conex aciclic, adica un arbore,
     * complexitatea finala fiind O(N+M).
     */
    if (graph.nodes - 1 != graph.edges)
        return 0;

    size_t size = sizeof(int) * (graph.nodes + 1);
    int * seen = (int *)malloc(size);
    memset(seen, 0, size);

    dfs(graph.list, 1, seen);

    for (int i = 1; i <= graph.nodes; ++i)
        if (!seen[i]) {
            // opa, un nod nu a fost vizitat :)
            free(seen);
            return 0;
        }

    free(seen);
    return 1; // este arbore
}


static void dfs(int ** list, int node, int * seen)
{
    seen[node] = 1;

    for (int i = 1; i <= list[node][0]; ++i)
        if (!seen[list[node][i]])
            dfs(list, list[node][i], seen);
}
