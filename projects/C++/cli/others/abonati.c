#include <stdio.h>
#include <string.h>
#include <ctype.h> // pentru a verifica tipul caracterului


#define DBG 0 // pentru debug
#define DIMT 16 // dimensiune maxima telefon
#define DIMN 32 // dimensiune maxima nume + prenume
// e recomandat sa folosesti mereu puteri ale lui 2


void parse(const char* buffer, int* numar, int* numLen, char* nume)
{
    const char* p = buffer; // cu p ne deplasam in sir
    // cat timp citim cifre stocam in numar
    while (isdigit(*p)) // cat timp avem cifre (de aia am inlcus ctype.h)
        numar[(*numLen)++] = *p++ - '0';
    // daca s-a ajuns aici e clar ca avem spatiu
    strcpy(nume, p + 1); // copiem ce este dupa spatiu in nume
    // verificam daca exista new line
    int len = -1;
    while (nume[++len]); // incrementam len pana ajungem la NULL
    if (nume[len - 1] == '\n') // avem new line, deci il scoatem
        nume[--len] = 0; // punand NULLul un pas in spate
}


int premiat(int* numar, int numLen)
{
    // verificam daca prima si ultima sunt proportionale
    if (numar[0] % numar[numLen - 1] &&
        numar[numLen - 1] % numar[0])
        return 0; // daca ambele au restul diferit de 0
    // acum verificam daca e vreo cifra impara
    for (int i = 0; i < numLen; ++i)
        if (numar[i] % 2)
            return 0;
    return 1;
}


int main()
{
    /* citim de la tastatura numele/locatia fisierului
       si o/il deschidem  */
    char fname[16];
    printf("Nume lista: ");
    scanf("%s%*c", fname); // citim un sir ignorand ultimul caracter
    #if DBG                // astfel eliminand NL din buffer
    fprintf(stderr, "fname: %s\n", fname);
    fprintf(stderr,"getchar(): %d\n", (int)getchar());
    #endif
    FILE* fin = fopen(fname, "r");
    if (!fin) {
        fprintf(stderr, "Eroare: fisierul nu a putut fi deschis\n");
        return 1;
    }
    /* acum citim fiecare linie intr-un buffer
       pana dam de EOF si separam telefonul de nume*/
    char buffer[DIMT + DIMN];
    do {
        char* ret = fgets(buffer, DIMT + DIMN, fin);
        if (!ret)  // daca am ajuns la capatul fisierului
            break; // SI daca nu am apucat sa citim vreo linie
                   // atunci iesim din bucla
        int numar[DIMT], numLen = 0;
        char nume[DIMN];
        // completam variabilele cu date din buffer
        parse(buffer, numar, &numLen, nume);
        if (premiat(numar, numLen))
            printf("%s\n", nume);
    } while (!feof(fin)); // cat timp nu am ajuns la capatul fisierului
    fclose(fin);
    return 0;
}
