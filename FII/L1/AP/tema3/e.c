// e: stiva si coada


#include <stdio.h>
#include <stdlib.h>


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


void stack()
{
    Node node;
    if (node_create(&node)) {
        puts("Memorie insuficienta\n");
        return;
    }
    int ask;
    do {
        puts("[1] Afisare");
        puts("[2] Adaugare");
        puts("[3] Scoatere");
        puts("[0] Iesire");
        fputs(">>> ", stdout);
        scanf("%d", &ask);
        if (!ask)
            // eliberam toata memoria
            node_free(node);
        else if (ask < 1 || ask > 3)
            puts("Optiune invalida");
        else if (ask == 1) {
            int* cnt = node_print(node, 1);
            if (*cnt) // daca am avut de afisat ceva
                putchar('\n');
            // acum `cnt` trebuie reinitializat
            *cnt = 0;
        } else if (ask == 2) {
            fputs("Valoare: ", stdout);
            int value;
            scanf("%d", &value);
            if (node_add(&node, value, 1))
                puts("Memorie insuficienta");
            else
                puts("Nodul a fost adaugat cu succes");
        } else if (ask == 3) {
            int value;
            if (node_remove(&node, &value))
                puts("Stiva vida");
            else
                printf("Nodul %d a fost scos cu succes\n",
                       value);
        }
        putchar('\n');
    } while (ask);
}


void queue()
{
    // similara cu `stack`, numai ca avem capete nu varf
    Node lo, hi;
    if (node_create(&hi)) {
        puts("Memorie insuficienta\n");
        return;
    }
    lo = hi;
    int ask;
    do {
        puts("[1] Afisare");
        puts("[2] Adaugare");
        puts("[3] Scoatere");
        puts("[0] Iesire");
        fputs(">>> ", stdout);
        scanf("%d", &ask);
        if (!ask)
            // eliberam toata memoria
            node_free(lo);
        else if (ask < 1 || ask > 3)
            puts("Optiune invalida");
        else if (ask == 1) {
            int* cnt = node_print(lo, 1);
            if (*cnt) // daca am avut de afisat ceva
                putchar('\n');
            // acum `cnt` trebuie reinitializat
            *cnt = 0;
        } else if (ask == 2) {
            fputs("Valoare: ", stdout);
            int value;
            scanf("%d", &value);
            if (node_add(&hi, value, 2))
                puts("Memorie insuficienta");
            else
                puts("Nodul a fost adaugat cu succes");
        } else if (ask == 3) {
            int value;
            if (node_remove(&lo, &value))
                puts("Coada vida");
            else
                printf("Nodul %d a fost scos cu succes\n",
                       value);
        }
        putchar('\n');
    } while (ask);
}


int main()
{
    int ask;
    do {
        puts("[1] Stiva");
        puts("[2] Coada");
        puts("[0] Iesire");
        fputs(">>> ", stdout);
        scanf("%d", &ask);
        if (!ask)
            break;
        else if (ask < 1 || ask > 2)
            puts("Optiune invalida");
        putchar('\n');
        if (ask == 1)
            stack();
        else if (ask == 2)
            queue();
        putchar('\n');
    } while (ask);
    return 0;
}
