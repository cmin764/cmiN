#include <stdio.h>

#include "graph.h"


#define FLEN 32


int main()
{
    char fname[FLEN];
    fputs("Nume fisier: ", stdout);
    scanf("%s", fname);
    Graph graph;
    graph_create(&graph, fname);
    if (graph_is_tree((const Graph)graph))
        puts("Este arbore");
    else
        puts("Nu este arbore");
    graph_destroy(&graph);
    return 0;
}
