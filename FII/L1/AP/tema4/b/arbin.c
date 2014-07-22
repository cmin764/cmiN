#include <stdlib.h>
#include <stdio.h>

#include "arbin.h"
#include "queue.h"


#define DBG 0


// variabile globale
static const char * str; // pentru a itera sirul


static int node_create(Node * node, char key)
{
    /**
     * Functie "privata" folosita pentru
     * crearea si initializarea valorilor.
     */
    // cream nodul
    *node = (Node)malloc(sizeof(struct _Node));
    #if DBG
    fprintf(stderr, "node: %p\n", *node);
    #endif
    if (!*node) // nu a putut fi alocat
        return 1;
    // initializam
    (*node)->key = key;
    (*node)->left = (*node)->right = NULL;
    return 0; // totul ok
}


int tree_create(Node * node, const char * const _str)
{
    static int inited = 0;
    if (!inited) {
        // se executa doar la primul apel
        inited = 1;
        str = _str;
    }
    /* intotdeauna `*str` trebuie sa arate
       catre valoarea unui nod (litera sau $)
       si nu catre o virgula sau paranteza,
       de asemenea trebuie sa-si pastreze pozitia */
    if (*str == '$') {
        *node = NULL;
        ++str;    // ca sa fim pe virgula sau
        return 0; // paranteza inchisa
    }
    // avem litera
    int rc = node_create(node, *str);
    if (rc) // nu a putut fi creat
        return rc;
    // acum vedem ce se afla dupa
    ++str;
    if (*str != '(')
        // nu avem fii
        return 0;
    // deci avem fii
    ++str;
    rc = tree_create(&(*node)->left, _str);
    if (rc)
        return rc;
    // acum suntem pe virgula
    ++str;
    rc = tree_create(&(*node)->right, _str);
    if (rc)
        return rc;
    // acum suntem pe paranteza inchisa
    ++str; // acum nu mai suntem :]
    return 0;
}


void tree_destroy(Node * node)
{
    if (!*node)
        return;
    tree_destroy(&(*node)->left);
    tree_destroy(&(*node)->right);
    free(*node);
    *node = NULL;
}


void tree_dfs(Node node, int mode)
{
    /**
     * Printeaza arborele in functie de mod:
     *     0 - preordine
     *     1 - inordine
     *     2 - postordine
     */
    if (!node)
        return;
    if (mode == 0)
        printf("%c ", node->key);
    tree_dfs(node->left, mode);
    if (mode == 1)
        printf("%c ", node->key);
    tree_dfs(node->right, mode);
    if (mode == 2)
        printf("%c ", node->key);
}


int tree_bfs(Node node)
{
    /**
     * Exploreaza arborele in latime,
     * adaugand fiecare nou nod ce urmeaza
     * a fi vizitat intr-o coada si la
     * fiecare vizita se extrage un nod
     * din coada.
     */
     // cream coada
     queue_t queue;
     queue_create(&queue);
     queue_push(&queue, node);
     // cat timp avem noduri in coada
     while (!queue_empty(queue)) {
        // scoatem primul nod
        queue_pop(&queue, &node);
        // ii adaugam fiii in coada
        if (node->left)
            if (queue_push(&queue, node->left))
                return 1;
        if (node->right)
            if (queue_push(&queue, node->right))
                return 1;
        // afisam nodul
        printf("%c ", node->key);
     }
     queue_destroy(&queue);
     return 0;
}


/* adaugarile problemei doi */


static inline void swap(
    Node * first,
    Node * second)
{
    Node tmp;
    tmp = *first;
    *first = *second;
    *second = tmp;
}


void tree_mirror(Node node)
{
    /**
     * Pentru a crea oglinditul este
     * suficient sa interschimbam fiecare
     * din cei doi fii pentru fiecare nod,
     * fie acestia si nuli.
     */
    if (!node) // nu avem ce procesa
        return;
    /* radacina ramane in pozitie
       doar schimbam adresele */
    swap(&node->left, &node->right);
    tree_mirror(node->left);
    tree_mirror(node->right);
}


void tree_lvl(Node node, int lvl, int crt)
{
    if (!node || crt > lvl)
        return;
    /* suntem pe nivelul corespunzator sau
       unul mai mic si avem noduri de afisat */
    if (lvl == crt)
        printf("%c ", node->key);
    tree_lvl(node->left, lvl, crt + 1);
    tree_lvl(node->right, lvl, crt + 1);
}


int tree_cnt1(Node node)
{
    if (!node)
        return 0;
    return 1 + tree_cnt1(node->left) +
               tree_cnt1(node->right);
}


int tree_cnt2(Node node)
{
    if (!node)
        return 0;
    // verificam cati descendenti are
    int cnt = 0; // initial nu-l numaram
    int des = (node->left ? 1 : 0) +
              (node->right ? 1 : 0);
    if (des == 1) // un descendent
        cnt = 1;  // deci numaram
    return cnt + tree_cnt2(node->left) +
                 tree_cnt2(node->right);
}


void tree_kelem(Node node, const int k,
                char * const chr, int firstTime)
{
    static int cnt = 0;
    if (firstTime)
        cnt = 0;
    if (!node || cnt == k)
        return;
    tree_kelem(node->left, k, chr, 0);
    ++cnt;
    if (cnt == k)
        *chr = node->key;
    tree_kelem(node->right, k, chr, 0);
}
