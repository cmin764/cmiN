// a: liste egale


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


int list_cmp(List list1, List list2)
{
    /**
     * Comparam element cu element pana dam
     * de `NAN` in `value` sau pana difera.
     * Intoarce 0 daca sunt egale
     *          1 daca `list1` > `list2`
     *         -1 daca `list1` < `list2`
     */
    while (list1->value == list2->value) {
        #if DBG
        fprintf(stderr, "v1: %d, v2: %d\n",
                list1->value, list2->value);
        #endif
        // cat timp elementele sunt egale
        if (list1->value == NAN || list2->value == NAN)
            break; // una din liste a ajuns la final
        list1 = list1->next;
        list2 = list2->next;
    }
    #if DBG
    fprintf(stderr, "v1: %d, v2: %d, v1-v2: %d\n",
            list1->value, list2->value,
            list1->value - list2->value);
    #endif
    return list1->value - list2->value;
}


void list_print(List list)
{
    /// Itereaza si afiseaza elementele listei.
    fprintf(stderr, "%p: ", list);
    while (list->value != NAN) {
        fprintf(stderr, "%d ", list->value);
        list = list->next;
    }
    fputc('\n', stderr);
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
    // le comparam
    #if DBG
    fprintf(stderr, "l1: %p, l2: %p\n", list1, list2);
    list_print(list1);
    list_print(list2);
    #endif
    ret = list_cmp(list1, list2);
    if (ret < 0)
        puts("Prima lista este mai MICA ca a doua");
    else if (ret > 0)
        puts("Prima lista este mai MARE ca a doua");
    else
        puts("Listele sunt egale.");
    /* sila sa mai eliberez memoria si in cazul in care dadea eroare
       asa ca nu o mai eliberez deloc, o face sistemul la iesire :) */
    return 0;
}
