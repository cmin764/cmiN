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


/* problema doi */


/// Transformarea in oglinda.
void tree_mirror(Node);


/// Afisarea nodurilor de pe un nivel.
void tree_lvl(Node, int, int);


/// Numararea nodurilor.
int tree_cnt1(Node);


/// Numararea nodurilor cu un descendent.
int tree_cnt2(Node);


/// Gasirea celui de-al k-lea element (inordine).
void tree_kelem(Node, const int,
                char * const, int);


#endif /* ARBIN_H */
