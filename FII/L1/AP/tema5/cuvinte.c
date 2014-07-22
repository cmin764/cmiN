#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int from;
    int to;
} er_t;


static inline int compare(const void * _first,
                          const void * _second)
{
    /// Functia de comparare a doua siruri.
    char * first = *(char **)_first;
    char * second = *(char **)_second;
    return strcmp(first, second);
}


void fill(char *** words, char *** specs,
          int * wordLen, int specLen,
          int wordsNr, int specsNr)
{
    *words = (char **)malloc(sizeof(char *) * wordsNr);
    (*words)[0] = NULL;    // pentru realloc
    *specs = (char **)malloc(sizeof(char *) * specsNr);

    // determina lungimea cuvintelor
    *wordLen = 0;
    char chr;
    while ((chr = getchar()) != '\n') {
        ++(*wordLen);
        // actualizam dimensiunea pentru primul cuvant
        (*words)[0] = (char *)realloc((*words)[0], sizeof(char) *\
                                           *wordLen);
        (*words)[0][*wordLen - 1] = chr;
    }
    (*words)[0] = (char *)realloc((*words)[0], sizeof(char) *\
                                       (*wordLen + 1));
    (*words)[0][*wordLen] = '\0';
    // completam urmatoarele cuvinte
    for (int i = 1; i < wordsNr; ++i) {
        (*words)[i] = (char *)malloc(sizeof(char) * (*wordLen + 1));
        scanf("%s", (*words)[i]);
    }

    // si acum cuvintele de ales
    for (int i = 0; i < specsNr; ++i) {
        (*specs)[i] = (char *)malloc(sizeof(char) * (specLen + 1));
        scanf("%s", (*specs)[i]);
    }
}


void release(char ** mat, int len)
{
    for (int i = 0; i < len; ++i)
        free(mat[i]);
    free(mat);
}


void test(char ** words, char ** specs,
          int wordsNr, int specsNr)
{
    fputs("Words...\n", stderr);
    for (int i = 0; i < wordsNr; ++i)
        fprintf(stderr, "%s\n", words[i]);
    fputs("Specs...\n", stderr);
    for (int i = 0; i < specsNr; ++i)
        fprintf(stderr, "%s\n", specs[i]);
}


er_t equal_range(char key, char ** col, er_t colRange, int pos)
{
    /**
     * Cauta binar intervalul in care se gasesc
     * candidatii corespunzatori cheii cautate.
     */
    int left = colRange.from;
    int right = colRange.to;
    er_t ret;
    ret.from = ret.to = -1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (key == col[mid][pos]) {
            ret.from = ret.to = mid;
            break;
        }
        if (key < col[mid][pos])
            right = mid;
        else
            left = mid + 1;
    }
    if (ret.from != -1) {
        while (ret.from && col[ret.from][pos] == key)
            --ret.from;
        if (col[ret.from][pos] != key)
            ++ret.from;
        while (ret.to < colRange.to && col[ret.to][pos] == key)
            ++ret.to;
    }
    return ret;
}


void bt(int pos, int specLen, char ** sol, char ** specs, int specsNr,
        char ** words, int wordsNr, int wordLen,
        char ** col1, char ** col2, er_t col1Range, er_t col2Range)
{
    if (pos == specLen) {
        // daca am format solutia
        for (int i = 0; i < specLen; ++i)
            // afisam cuvintele
            printf("%s\n", sol[i]);
        putchar('\n');
        return;
    }

    /* la fiecare pas alegem un cuvant si in functie
       de prima si ultima litera actualizam lista de
       candidati posibili (din cuvintele speciale), 
       cautand binar litera de pe pozitia respectiva */
    for (int i = 0; i < wordsNr; ++i) {
        char * word = words[i];
        // prima si ultima litera
        char lo = word[0], hi = word[wordLen - 1];
        /* acum eliminam cuvintele "speciale" ce nu
           contin ca prima si respectiv ultima litera
           pe pozitia pos */
        er_t ret1 = equal_range(lo, col1, col1Range, pos);
        // avem sau nu candidati
        if (ret1.from == ret1.to)
            continue;    // nu avem candidati
        // la fel si pentru a doua litera
        er_t ret2 = equal_range(hi, col2, col2Range, pos);
        if (ret2.from == ret2.to)
            continue;
        /* e ok, inca mai avem posibilitatea
           de a finaliza solutia */
        sol[pos] = word;
        bt(pos + 1, specLen, sol, specs, specsNr, words, wordsNr,
           wordLen, col1, col2, ret1, ret2);
    }
}


int main()
{
    freopen("cuvinte.in", "r", stdin);
    freopen("cuvinte.out", "w", stdout);

    /* numarul de cuvinte, cuvinte speciale
       si cate trebuiesc alese */
    int wordsNr, specsNr, specLen;
    scanf("%d %d %d", &wordsNr, &specsNr,
          &specLen);
    getchar();    // scapam de EOL ramas in buffer

    // stocam cuvintele normale si de ales
    int wordLen;
    char ** words, ** specs;
    fill(&words, &specs, &wordLen, specLen,
         wordsNr, specsNr);
    qsort(specs, specsNr, sizeof(char *), compare);
    //test(words, specs, wordsNr, specsNr);

    // unde o sa retinem solutia
    char ** sol = (char **)malloc(sizeof(char *) * specLen);
    char ** col1 = (char **)malloc(sizeof(char *) * specsNr);
    char ** col2 = (char **)malloc(sizeof(char *) * specsNr);
    // umplem col1 si col2 cu toate cuvintele "speciale"
    for (int i = 0; i < specsNr; ++i)
        col1[i] = specs[i];
    for (int i = 0; i < specsNr; ++i)
        col2[i] = specs[i];
    // razele in care trebuie sa facem cautarea
    er_t col1Range, col2Range;
    col1Range.from = col2Range.from = 0;
    col1Range.to = col2Range.to = specsNr;

    bt(0, specLen, sol, specs, specsNr, words, wordsNr,
       wordLen, col1, col2, col1Range, col2Range);

    release(words, wordsNr);
    release(specs, specsNr);
    free(sol);
    free(col1);
    free(col2);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
