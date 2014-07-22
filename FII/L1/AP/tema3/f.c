// f: stive ordonate crescator


#include <stdio.h>
#include <stdlib.h>


#define DBG 0 // debug


typedef struct Node {
    /// Structura unui nod din lista.
    struct Node* next;
    int value;
}* Node;


void node_init(Node node)
{
    node->next = NULL;
    node->value = 0;
}


int node_create(Node* node)
{
    // pointer la pointer ^
    *node = (Node)malloc(sizeof(struct Node));
    if (!(*node))
        return 1;
    node_init(*node);
    return 0; // a fost creat cu succes
}


int node_empty(Node node)
{
    if (node->next)
        // daca exista un urmator nod
        return 0; // atunci nu e goala
    return 1;
}


int node_add(Node* node, int value, int mode)
{
    /**
     * Adauga nod in functie de tipul adaugarii,
     * pentru stiva, respectiv coada.
     */
    Node other;
    if (node_create(&other))
        return 1;
    // acum daca avem stiva
    if (mode == 1) {
        // legam `other` de varf si actualizam varful
        other->value = value;
        other->next = *node;
    } else {
        /* legam capatul din dreapta de `other`
           si il actualizam la noul capat */
        (*node)->value = value;
        (*node)->next = other;
    }
    *node = other; // avansare sau devansare
    return 0; // totul ok
}


int node_remove(Node* node, int* value)
{
    /**
     * Sterge varful/capatul daca nu este vida,
     * si stocheaza in `*value` valoarea scoasa.
     */
    if (node_empty(*node))
        return 1; // nu avem ce sa stergem
    /* atat pentru stiva cat si coada este suficient
       sa legam `node` de nodul urmator, apoi
       sa eliberam memoria controlata de `node` */
    Node _node = *node;
    *value = _node->value;
    *node = _node->next;
    free(_node);
    return 0;
}


void node_free(Node node)
{
    /**
     * Elibereaza memoria fiecarui nod,
     * inclusiv a santinelei (aia din Matrix :D).
     */
    if (!node)
        return;
    // avem pointer diferit de NULL
    node_free(node->next);
    free(node);
}


int* node_print(Node node, int mode)
{
    static int cnt = 0; // nu se va reinitializa cu 0
    if (!node->next)    // la urmatorul apel
        return &cnt;
    // avem nod de afisat
    ++cnt;
    if (mode == 1) {
        node_print(node->next, mode);
        printf("%d ", node->value);
    } else {
        printf("%d ", node->value);
        node_print(node->next, mode);
    }
    return &cnt;
}


Node node_fill(int which)
{
    Node node;
    if (node_create(&node))
        return NULL;
    printf("Stiva %d: ", which);
    do {
        int value;
        scanf("%d", &value);
        if (!value)
            break;
        // avem numar pozitiv
        if (node_add(&node, value, 1))
            return NULL;
    } while (1);
    return node;
}


int node_move(Node* from, Node* to)
{
    do {
        int value;
        if (node_remove(from, &value))
            break;
        // nod scos cu succes ^
        if (node_add(to, value, 1))
            return 1; // memorie insuficienta
    } while (1);
    return 0;
}


Node process(Node* node1, Node* node2)
{
    /**
     * Avand valorile in ordine crescatoare si prima
     * valoare din `node2` fiind mai mare decat ultima
     * din `node1`, este suficient sa descarcam a doua
     * stiva in ultima, apoi prima stiva in ultima stiva
     * si pentru a o avea in ordine crescatoare sa descarcam
     * elementele din ultima stiva in prima, din prima
     * in a doua si apoi la loc in ultima.
     */
    Node node3;
    if (node_create(&node3))
        return NULL;
    // mutam toate elementele dintr-o stiva intr-alta
    if (node_move(node2, &node3))
        return NULL;
    if (node_move(node1, &node3))
        return NULL;
    if (node_move(&node3, node1))
        return NULL;
    if (node_move(node1, node2))
        return NULL;
    if (node_move(node2, &node3))
        return NULL;
    return node3;
}


int main()
{
    puts("Introdu un numar arbitrar de elemente,");
    puts("oprirea facandu-se la introducerea lui 0");
    Node node1, node2;
    node1 = node_fill(1);
    node2 = node_fill(2);
    if (!(node1 && node2))
        return 1;
    Node node3 = process(&node1, &node2);
    if (!node3)
        return 1;
    int* cnt = node_print(node3, 1);
    if (*cnt) {
        *cnt = 0;
        putchar('\n');
    }
    #if DBG
    node_print(node1, 1);
    fprintf(stderr, "n1: %p, n1n: %p\n", node1, node1->next);
    fprintf(stderr, "n2: %p, n2n: %p\n", node2, node2->next);
    #endif
    #if 1
    node_free(node1);
    node_free(node2);
    node_free(node3);
    #endif
    return 0;
}
