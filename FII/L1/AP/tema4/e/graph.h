#ifndef GRAPH_H
#define GRAPH_H


typedef struct {
    /**
     * Structura unui graf (graf neorientat).
     * Aceasta contine numarul entitatilor si
     * o lista (sub forma de vectori) cu vecinii
     * fiecarui nod.
     */
    int nodes; // numarul de varfuri
    int edges; // numarul de arce
    int ** list; // lista de adiacenta
} Graph;


// creeaza structura folosind fisierul
void graph_create(Graph *, char *);


// distruge graful
void graph_destroy(Graph *);


// verifica daca este arbore
int graph_is_tree(const Graph);


#endif /* GRAPH_H */
