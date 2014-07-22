// b: interclaseaza doua liste ordonate, similar cu "a"


#include <stdio.h>
#include <stdlib.h>


#define NAN 0 // element de oprire/invalid
#define DBG 0 // debug


typedef struct List {
    /**
     * Structura recursiva ce defineste nodul unei liste.
     * Aceasta contine valoarea elementului corespunzator,
     * dar si o legatura catre urmatorul nod.
     * Primul si ultimul capat nu sunt legate intre ele
     * si exista legaturi intr-un singur sens, de aici si
     * numele de lista liniara simplu inalntuita.
     */
    struct List* next; // legatura catre urmatorul nod
    int value;
}* List; // definitia ca pointer la structura


void list_init(List list, int value)
{
    /// Functie de initializare pentru fiecare nou nod creat.
    list->next = NULL;
    list->value = value;
}


int list_add(List list, int value)
{
    /**
     * Functie ce adauga un nod la finalul listei `list`
     * cu valoarea `value`.
     */
    // determinam ultimul element
    while (list->next) list = list->next;
    // alocam memorie si verificam daca s-a alocat cu succes
    list->next = malloc(sizeof(struct List));
    list = list->next;
    if (!list)
        return 1;
    // totul e ok, inlistializam si scriem valoarea
    list_init(list, value);
    return 0;
}


int list_fill(List list) {
    int value;
    do {
        // cat timp nu avem `NAN`, citim numere
        scanf("%d", &value);
        if (value == NAN)
            break; // am citit `NAN`
        // il scriem in nodul curent
        list_init(list, value);
        int ret = list_add(list, NAN);
        if (ret)
            return ret;
        // aici am pierdut aproape o ora :(
        list = list->next; // sa-mi dau seama ca nu o iteram
    } while (1);
    return 0;
}



void list_print(List list)
{
    /// Itereaza si afiseaza elementele listei.
    while (list->value != NAN) {
        printf("%d ", list->value);
        list = list->next;
    }
    putchar('\n');
}


List list_merge(List list1, List list2)
{
    /**
     * Interclaseaza `list1` si `list2`
     * si returneaza noua lista.
     */
    // cream lista finala
    List list3 = malloc(sizeof(struct List));
    if (!list3)
        return NULL; // nu s-a putut aloca memorie
    List _list3 = list3; // copiem capul
    // cat timp nu se ajunge la vreun final
    int ret, v1, v2;
    while ((v1 = list1->value) != NAN && (v2 = list2->value) != NAN) {
        // comparam si adaugam elementele
        if (v1 < v2) {
            list_init(list3, v1);
            list1 = list1->next;
        }
        else {
            list_init(list3, v2);
            list2 = list2->next;
        }
        ret = list_add(list3, NAN);
        if (ret)
            return NULL;
        list3 = list3->next;
    }
    // acum concatenam restul listei 1 sau 2
    while ((v1 = list1->value) != NAN) {
        list_init(list3, v1);
        ret = list_add(list3, NAN);
        if (ret)
            return NULL;
        list1 = list1->next;
        list3 = list3->next;
    }
    while ((v2 = list2->value) != NAN) {
        list_init(list3, v2);
        ret = list_add(list3, NAN);
        if (ret)
            return NULL;
        list2 = list2->next;
        list3 = list3->next;
    }
    return _list3;
}


int main()
{
    // cream, initializam si completam listele
    const char errmsg[] = "Nu a putut fi alocata memorie";
    List list1, list2;
    list1 = malloc(sizeof(struct List));
    list2 = malloc(sizeof(struct List));
    if (!(list1 && list2)) {
        fprintf(stderr, "Eroare: %s\n", errmsg);
        return 1;
    }
    #if DBG
    fprintf(stderr, "l1: %p, l2: %p\n", list1, list2);
    #endif
    list_init(list1, NAN);
    list_init(list2, NAN);
    printf("Introdu un numar arbitrar de numere, %d pentru a opri\n",
           NAN);
    // pentru prima lista
    fputs("Lista 1: ", stdout);
    int ret = list_fill(list1);
    if (ret) {
        fprintf(stderr, "Eroare: %s\n", errmsg);
        return ret;
    }
    // pentru a doua lista
    fputs("Lista 2: ", stdout);
    ret = list_fill(list2);
    if (ret) {
        fprintf(stderr, "Eroare: %s\n", errmsg);
        return ret;
    }
    // cream o lista cu cele doua interclasate, implicit e ordonata
    List list3 = list_merge(list1, list2);
    if (!list3) {
        fprintf(stderr, "Eroare: %s\n", errmsg);
        return 1;
    }
    list_print(list3);
    /* sila sa mai eliberez memoria si in cazul in care dadea eroare
       asa ca nu o mai eliberez deloc, o face sistemul la iesire :) */
    return 0;
}
