#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define iname "table.txt"
#define N 16
#define sufix "RON"
#define sep 6

typedef struct {
    char nume[N], prenume[N]; // adaugam ce ne intereseaza sa citim de pe fiecare linie
    uint64_t cnp; // de 64b ca sa intre numerele de 13 cifre
    unsigned short salariu, spor, cur; // pe 16 biti -> 0-64000
} Linie; // si acum cu Linie facem obiecte care contin datele impachetate mai sus

unsigned short nr; // aici actualizam numarul de obiecte create
Linie* lista; // un pointer la structura de mai sus
// care va fi de fapt un vector cu memorie alocata dinamic ce contine obiecte de tip Linie
unsigned short dimCel[sep - 1] = {5, 14, 15, 11, 17}; // dimensiunea celulelor
unsigned short dimSep = sep;

static char* itoax(int val, int base){ // itoa nu e o functia standard se gaseste pe win pe unele compilatoare
	static char buf[32] = {0};
	int i = 30; // asa ca
	for(; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return &buf[i+1]; // am luat de pe net functia pentru a converti din intreg in sir
}

void init()
{
    unsigned short i, tmp;
    freopen(iname, "rt", stdin); // deschidem fisierul de la linia 2 si-l directionam catre consola
    while (!feof(stdin)) {
        lista = (Linie*) realloc(lista, ++nr * sizeof(Linie));
        i = nr - 1; // fixam indexul si citim pe pozitia i urmatoare date
        scanf("%s %s %I64u %hu %hu\n", lista[i].nume, lista[i].prenume, &lista[i].cnp, &lista[i].salariu, &lista[i].spor);
        lista[i].cur = nr;
        tmp = strlen(lista[i].nume) + strlen(lista[i].prenume) + 3;
        if (tmp > dimCel[1]) {
            dimCel[1] = tmp; // actualizam dimensiunea pentru "Nume Prenume"
        }
    }
    fclose(stdin);
    for (i = 0; i < sep - 1; ++i) {
        dimSep += dimCel[i];
    }
}

void zfills(unsigned short tipCel, const char* text)
{ // afisam atatea spatii cate trebuie sa punem in fata fiecarui continut
    unsigned short dim;
    dim = dimCel[tipCel] - strlen(text) - 1;
    while (dim) {
        putchar(' ');
        --dim;
    }
}

void zfilld(unsigned short tipCel, unsigned short value)
{ // pentru varianta ce are continut numeric ce are RON ca sufix
    unsigned short dim = 0;
    while (value) {
        ++dim;
        value /= 10;
    }
    dim = dimCel[tipCel] - dim - strlen(sufix) - 2;
    while (dim) {
        putchar(' ');
        --dim;
    }
}

void print_sep()
{
    unsigned short i;
    for (i = 0; i < dimSep; ++i) {
        putchar('-');
    }
    putchar('\n');
}

void bar()
{
    putchar('|');
}

void show()
{ // facem afisarea datelor citite, stocate si impachetate in "lista"
    unsigned short i;
    char tmp[2 * N];
    print_sep();
    bar();
    zfills(0, "Nr.");
    printf("%s ", "Nr.");
    bar();
    zfills(1, "Nume Prenume");
    printf("%s ", "Nume Prenume");
    bar();
    zfills(2, "CNP");
    printf("%s ", "CNP");
    bar();
    zfills(3, "Salariu");
    printf("%s ", "Salariu");
    bar();
    zfills(4, "Spor de vechime");
    printf("%s ", "Spor de vechime");
    bar();
    putchar('\n');
    for (i = 0; i < nr; ++i) {
        print_sep();
        bar();
        zfills(0, itoax(lista[i].cur, 10));
        printf("%hu ", lista[i].cur);
        bar();
        tmp[0] = 0;
        strcat(strcat(strcat(tmp, lista[i].nume), " "), lista[i].prenume);
        zfills(1, tmp);
        printf("%s ", tmp);
        bar(); // in caz de face faze citirea si scrierea numerelor ce sar de 4 miliarde
        printf(" %I64u ", lista[i].cnp); // modifici tipul lui cnp in char[13]
        bar(); // si-l citesti si afisezi ca pe un string
        zfilld(3, lista[i].salariu);
        printf("%hu %s ", lista[i].salariu, sufix);
        bar();
        zfilld(4, lista[i].spor);
        printf("%hu %s ", lista[i].spor, sufix);
        bar();
        putchar('\n');
    } // imagineaza-ti cat de mult aveai de scris daca adaugai fiecare linie manual
    print_sep(); // in loc s-o faci cu forul de mai sus
}

int main()
{
    init();
    show();
    return 0;
}
