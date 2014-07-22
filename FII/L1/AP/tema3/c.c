/*
 * c: manipularea memoriei prin liste
 *
 * Dupa cum spune si enuntul, nu este obligatoriu
 * sa memoram tot tabloul pentru a sti cum este
 * memoria ocupata si pentru a aplica eficient
 * acele functii. Ajunge sa pastram ordonata lista
 * in functie de offset/adresa si vom proceda astfel:
 *     1. La ALOCARE luam doua cate doua noduri din lista
 *        si vedem daca exista "spatiu" suficient
 *        intre ele si daca exista introducem un nou
 *        nod intre cele doua cu un continut corespunzator
 *     2. La ELIBERARE vedem care sunt nodurile afectate de
 *        zona eliberata si stergem pe cele afectate pe tot
 *        intervalul iar capetele (daca sunt) afectate partial
 *        vor fi modificate, in final legand capatul stang de
 *        cel drept.
 *     3. La DEFRAGMENTARE pentru fiecare element K (incepand cu
 *        al doilea) ii actualizam adresa ca fiind adresa
 *        elementului K-1 plus lungimea intervalului si astfel
 *        toata memoria ocupata va fi continua si in "stanga".
 */


#include <stdio.h>
#include <stdlib.h>


#define MERR "Memorie insuficienta"
#define DBUG 0


typedef struct Node {
    /// Structura unui nod.
    struct Node* next; // legatura
    int offset; // adresa
    int length; // lungimea alocata
}* Node;


/* BEG functii specifice */
Node node_create(Node next, int offset, int length)
{
    /// Aloca si initializeaza un nod.
    Node node = (Node)malloc(sizeof(struct Node));
    if (node) {
        node->next = next;
        node->offset = offset;
        node->length = length;
    } else {
        fprintf(stderr, "%s\n", MERR);
        exit(EXIT_FAILURE);
    }
    return node; // NULL daca nu s-a putut aloca
}


void node_free(Node from, Node to)
{
    /**
     * Elibereaza memoria ocupata de fiecare nod
     * pornind de la `from` inclusiv pana la `to`.
     * Ultimul nod (`to`) nu este eliberat.
     *
     * Nodul `to` poate fi si NULL, asta inseamna
     * ca stergerea va fi completa, inclusiv
     * nodul santinela.
     */
    if (from == to)
        return; // s-a ajuns la capat
    node_free(from->next, to);
    free(from);
}


int* node_print(Node node)
{
    static int cnt = 0;
    if (!node->next)
        return &cnt;
    ++cnt;
    printf("(%d, %d) ", node->offset, node->length);
    node_print(node->next);
    return &cnt;
}
/* END functii specifice */


int nalloc(Node* node, int length, int size)
{
    /**
     * Aloca `length` memorie si intoarce adresa
     * de inceput. Daca nu s-a putut aloca memorie
     * intoarce -1.
     */
    // putin cod redundant
    if ((*node)->offset == -1) {
        /* daca suntem in nodul santinela
           inseamna ca lista este vida */
        if (length > size)
            return -1;
        // cream noul nod
        Node other = node_create(*node, 0, length);
        // totul ok
        *node = other;
        return 0;
    }
    // de fapt, mai mult cod redundant
    Node first, second;
    first = *node;
    second = first->next;
    // verificam daca exista spatiu inaintea capului
    if (length <= first->offset) {
        // alocam inainte si actualizam noul cap
        Node other = node_create(first, 0, length);
        *node = other;
        return 0;
    }
    /* daca am ajuns aici inseamna ca trebuie sa gasim
       o gaura printre zonele ocupate sau de la ultima
       zona pana la finalul campului */
    for (; second->offset != -1; first = second,
                                 second = first->next) {
        int newOffset;
        if (length > second->offset -
            (newOffset = first->offset + first->length)) {
            continue; // nu ne ajunge spatiul
        }
        // ne ajunge spatiul :]
        Node other = node_create(second, newOffset, length);
        first->next = other;
        return newOffset;
    }
    // poate mai e o sansa sa gasim dupa ultimul nod
    int newOffset;
    if (length <= size -
        (newOffset = first->offset + first->length)) {
        // Neo, nu uita ca acum `second` e santinela
        Node other = node_create(second, newOffset, length);
        first->next = other;
        return newOffset;
    }
    // daca s-a ajuns aici inseamna ca nu exista vreo zona buna
    return -1;
}


void link(Node* node, int offset, int length,
          Node _lo, Node lo, Node _hi, Node hi)
{
    /// Face curatenie si leaga rupturile.
    /* `lo` si/sau `_hi` trebuiesc modificate/sterse
       tot ce e intre `lo` si `_hi` trebuie sters */
    #if DBUG
    // macar sa stiu daca am gandit bine
    printf("_lo(%p): (%d, %d)\n", _lo, _lo->offset, _lo->length);
    printf("lo(%p): (%d, %d)\n", lo, lo->offset, lo->length);
    printf("_hi(%p): (%d, %d)\n", _hi, _hi->offset, _hi->length);
    printf("hi(%p): (%d, %d)\n", hi, hi->offset, hi->length);
    #endif
    int offLen = offset + length;
    if (lo == _hi) {
        /* caz mai special, baliza poate fi chiar si
           in interiorul sau spre stanga zonei */
        // daca baliza e in interiorul zonei
        if (offset > lo->offset &&
            offLen < lo->offset + lo->length) {
            /* trebuie sa spargem zona in cele doua zone
               care nu se intersecteaza cu baliza */
            Node second = node_create(hi, offLen,
                                      lo->offset + lo->length - offLen);
            Node first = node_create(second, lo->offset, offset - lo->offset);
            /* acum trebuie sa legam predecesorul lui `lo` de `first`
               dar daca `lo` era primul nod, nu avem predecesor */
            if (lo == *node)
                // nu are predecesor
                *node = first; // actualizam capul
            else
                _lo->next = first;
            // orice ar fi, stergem `lo`
            free(lo);
        // daca zona e in interiorul balizei
        } else if (offset <= lo->offset &&
                   offLen >= lo->offset + lo->length) {
            // trebuie sa eliminam cu totul nodul
            if (lo == *node)
                *node = hi;
            else
                _lo->next = hi;
            free(lo);
        // acum poate fi spre stanga sau in dreapta
        } else if (offset <= lo->offset) {
            // stanga
            lo->length = lo->offset + lo->length - offLen;
            lo->offset = offLen;
        } else if (offLen >= lo->offset + lo->length)
            // dreapta, offsetul ramane acelasi
            lo->length = offset - lo->offset;
        else {
            fputs("Eroare la incadrarea balizei\n", stderr);
            exit(EXIT_FAILURE);
        }
    } else {
        // avem noduri diferite, in sfarsit
        int loDel = 0, hiDel = 0; // stergem sau nu
        // pentru `lo`
        if (offset <= lo->offset)
            loDel = 1; // eliminat
        else
            lo->length = offset - lo->offset;
        // pentru `_hi`
        if (offLen >= _hi->offset + _hi->length)
            hiDel = 1; // you are terminated
        else {
            // si offsetul
            _hi->length = _hi->offset + _hi->length - offLen;
            _hi->offset = offLen;
        }
        // si acum legam rupturile
        Node to;
        if (hiDel)
            to = hi;
        else
            to = _hi;
        Node from;
        if (loDel) {
            from = lo;
            if (lo == *node)
                *node = to;
            else
                _lo->next = to;
        } else {
            from = lo->next;
            lo->next = to;
        }
        // stergerea in sine
        node_free(from, to);
    }
    // amin xD
}


void nfree(Node* node, int offset, int length)
{
    /**
     * Gasim nodurile afectate de eliberarea zonelor
     * de memorie si in functie de gradul de afectare
     * le eliminam complet sau le modificam
     * (maxim doua modificari).
     */
    int offLen = offset + length;
    if ((*node)->offset == -1)
        return; // nu avem noduri
    Node _lo, lo, _hi, hi;
    _lo = _hi = lo = hi = *node;
    /* acum actualizam `lo` si `hi` de asa natura
       sa incadram intre ele nodurile afectate */
    int loSet = 0, hiSet = 0;
    while (!(loSet && hiSet)) {
        // cat timp nu avem setate cele doua capete
        /* verificam daca nu cumva am trecut de baliza
           fara sa avem intersectie */
        if (!loSet)
            // daca nu avem setat `lo` verificam daca
            if (offLen <= lo->offset)
                return; // nu avem ce elibera
            else if (lo->offset + lo->length <= offset) {
                // nu intersecteaza baliza
                _lo = lo; // deci
                lo = lo->next; // avansam
                _hi = hi;
                hi = hi->next;
            } else
                loSet = 1; // avem intersectie
        else
            // setam primul `hi` neafectat
            if (hi->offset == -1 ||
                offLen <= hi->offset)
                hiSet = 1;
            else {
                _hi = hi;
                hi = hi->next;
            }
    }
    // restul modificarilor
    link(node, offset, length, _lo, lo, _hi, hi);
}


void ndefrag(Node node)
{
    /// Muta tot cat mai in stanga.
    if (node->offset == -1)
        return; // nu sunt noduri
    if (node->offset > 0)
        node->offset = 0;
    Node last = node;
    node = node->next;
    while (node->offset != -1) {
        int newOffset = last->offset + last->length;
        node->offset = newOffset;
        last = node;
        node = node->next;
    }
}


int main()
{
    Node node = node_create(NULL, -1, 0);
    int size;
    fputs("Dimensiune: ", stdout);
    scanf("%d", &size);
    do {
        puts("[1] Afiseaza");
        puts("[2] Aloca");
        puts("[3] Elibereaza");
        puts("[4] Defragmenteaza");
        puts("[0] Iesi");
        fputs(">>> ", stdout);
        int ask;
        scanf("%d", &ask);
        if (!ask) {
            node_free(node, NULL);
            break;
        } else if (ask < 1 || ask > 4)
            puts("Optiune invalida");
        else if (ask == 1) {
            int* cnt = node_print(node);
            if (*cnt) {
                *cnt = 0;
                putchar('\n');
            }
        } else if (ask == 2) {
            int length;
            fputs("Lungime: ", stdout);
            scanf("%d", &length);
            int offset = nalloc(&node, length, size);
            if (offset == -1)
                puts("Nu se poate aloca");
            else
                printf("S-a alocat la adresa %d\n", offset);
        } else if (ask == 3) {
            int offset, length;
            fputs("Adresa: ", stdout);
            scanf("%d", &offset);
            fputs("Lungime: ", stdout);
            scanf("%d", &length);
            nfree(&node, offset, length);
        } else if (ask == 4)
            ndefrag(node);
        putchar('\n');
    } while (1);
    return 0;
}
