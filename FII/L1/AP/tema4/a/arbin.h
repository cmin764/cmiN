#ifndef ARBIN_H
#define ARBIN_H


struct _Node {
    /**
     * Definitia unui nod din arbore, unde:
     * `struct _Node` se refera la structura
     * insasi iar `Node` este sinonimul lui
     * `struct _Node*`, adica un pointer la
     * structura.
     */
     char key; // aici stocam valoarea
     struct _Node * left; // fiul stang
     struct _Node * right; // fiul drept
};


typedef struct _Node * Node; // sinonimul


/// Crearea arborelui dintr-un sir.
int tree_create(Node *, const char *);


/// Distrugerea arborelui.
void tree_destroy(Node *);


/// Afisarea arborelui in adancime.
void tree_dfs(Node, int);


/// Afisarea arborelui in latime.
int tree_bfs(Node);


#endif /* ARBIN_H */
