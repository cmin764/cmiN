// d: siruri prin liste


#include <stdio.h>
#include <stdlib.h>


#define EOL '\n' // end of line


typedef struct List {
    struct List* next;
    char value;
}* List;


void list_init(List list)
{
    list->next = NULL;
    list->value = 0;
}


int list_add(List list)
{
    list->next = malloc(sizeof(struct List));
    list = list->next;
    if (!list)
        return 1;
    list_init(list);
    return 0;
}


int list_fill(List list)
{
    char value;
    do {
        value = getchar();
        if (value == EOL)
            break;
        list->value = value;
        int ret = list_add(list);
        if (ret)
            return 1;
        list = list->next;
    } while (1);
    return 0;
}


void list_print(List list)
{
    while (list->value) {
        printf("%c", list->value);
        list = list->next;
    }
    putchar('\n');
}


void list_free(List list)
{
    /// Elibereaza memoria ocupata de noduri.
    list = list->next; // cu exceptia capului
    if (list) {
        list_free(list);
        free(list);
    }
}


void errprt()
{
    const char errmsg[] = "Nu a putut fi alocata memorie";
    fprintf(stderr, "Eroare: %s\n", errmsg);
}


/* oglindit1 BEGIN */
static inline void swap_value(List from, List to)
{
    char tmp = from->value;
    from->value = to->value;
    to->value = tmp;
}


void list_swap(List list, int lo, int hi)
{
    /// Iterand prin lista face interschimbari.
    List from, to; // capetele corespunzatoare
    while (lo < hi) {
        /* se putea optimiza, dar complexitatea
           teoretica ramanea aceeasi */
        from = to = list;
        for (int i = 0; i < lo; ++i)
            from = from->next;
        for (int i = 0; i < hi; ++i)
            to = to->next;
        swap_value(from, to);
        ++lo;
        --hi;
    }
}


void oglindit1(List list)
{
    /// Construieste oglinditul peste acelasi continut.
    // mai intai determinam lungimea sirului
    int len = 0;
    List _list = list;
    while (_list->value) {
        // cat timp nu dam de NULL
        ++len;
        _list = _list->next;
    }
    // acum facem interschimbari simetrice intre caractere
    list_swap(list, 0, len - 1);
}
/* oglindit1 END */


/* oglindit2 BEGIN */
int oglindit2(List list)
{
    /* procedam similar ca-n `oglindit1` numai ca
       facem oglinditul primei jumatati si apoi
       verificam daca prima jumatate coincide cu ultima */
    // la fel, determinam lungimea
    int len = 0;
    List _list = list;
    while (_list->value) {
        ++len;
        _list = _list->next;
    }
    if (len % 2)
        return 0; // lungime impara
    list_swap(list, 0, len / 2 - 1);
    // acum verificam egalitatea jumatatilor
    _list = list;
    // avansam headul temporar catre a doua jumatate
    for (int i = 0; i < len / 2; ++i)
        _list = _list->next;
    // si acum verificam liniar
    while (_list->value) {
        if (list->value != _list->value)
            return 0;
        list = list->next;
        _list = _list->next;
    }
    return 1; // OK!!!1!11
}
/* oglindit2 END */


/* Sir1 <= Sir2 BEGIN */
int list_cmp(List list1, List list2)
{
    int v1, v2;
    while ((v1 = list1->value) && (v2 = list2->value)) {
        // cat timp nu am dat de NULL
        if (v1 != v2) // daca se abate vreun caracter
            return v1 - v2;
        list1 = list1->next;
        list2 = list2->next;
    }
    return v1 - v2;
}
/* Sir1 <= Sir2 END */


int main()
{
    List list1, list2;
    list1 = malloc(sizeof(struct List));
    list2 = malloc(sizeof(struct List));
    if (!(list1 && list2)) {
        errprt();
        return 1;
    }
    int ask;
    do {
        puts("[1] Oglindit1");
        puts("[2] Oglindit2");
        puts("[3] Sir1 <= Sir2");
        puts("[0] Iesire");
        printf(">>> ");
        scanf("%d%*c", &ask); // also ignore EOL
        if (!ask) // quit
            break;
        if (ask < 1 || ask > 3) {
            // invalid option
            puts("Optiune invalida\n");
            continue;
        }
        list_init(list1);
        fputs("Sir 1: ", stdout);
        int ret = list_fill(list1);
        if (ret) {
            errprt();
            return 1;
        }
        switch (ask) {
            case 1:
            oglindit1(list1);
            list_print(list1);
            break;
            case 2:
            ret = oglindit2(list1);
            if (ret)
                puts("Da");
            else
                puts("Nu");
            break;
            case 3:
            // avem nevoie si de al doilea sir
            list_init(list2);
            fputs("Sir 2: ", stdout);
            ret = list_fill(list2);
            if (ret) {
                errprt();
                return 1;
            }
            ret = list_cmp(list1, list2);
            if (ret <= 0)
                puts("Da");
            else
                puts("Nu");
            list_free(list2);
        }
        putchar('\n');
        list_free(list1);
    } while (1);
    return 0;
}
