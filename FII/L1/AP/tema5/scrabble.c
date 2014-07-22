#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define WORD 32


static inline int compare(const void * _first,
                          const void * _second)
{
    char * first = *(char **)_first;
    char * second = *(char **)_second;

    int i;
    for (i = 0; first[i] && second[i]; ++i)
        if (first[i] != second[i])
            return first[i] - second[i];

    return first[i] - second[i];
}


void add_word(char *** dict, char * buffer,
              int * dictLen, int wordLen)
{
    *dict = (char **)realloc(*dict, sizeof(char *) *\
        ++(*dictLen));
    (*dict)[*dictLen - 1] = (char *)malloc(sizeof(char) *\
        (wordLen + 1));
    strcpy((*dict)[*dictLen - 1], buffer);
}


void fill(char *** dict, int * len)
{
    while (1) {
        char buffer[WORD];
        scanf("%s", buffer);
        if (feof(stdin))
            break;
        int length = strlen(buffer);
        add_word(dict, buffer, len, length);
    }
}


void show(char ** dict, int len)
{
    for (int i = 0; i < len; ++i)
        printf("%s\n", dict[i]);
}


void release(char ** dict, int len)
{
    for (int i = 0; i < len; ++i) {
        free(dict[i]);
    }
    free(dict);
}


int check(char * first, char * second)
{
    int fLen = strlen(first);
    int sLen = strlen(second);

    if (fLen != sLen)
        return 0;

    int * used = (int *)calloc(fLen, sizeof(int));
    for (int i = 0; i < sLen; ++i) {
        int found = 0;
        for (int j = 0; j < fLen; ++j)
            if (!used[j] && tolower(second[i]) ==\
                tolower(first[j])) {
                    found = 1;
                    used[j] = 1;
                    break;
            }
        if (!found) {
            free(used);
            return 0;
        }
    }

    free(used);
    return 1;
}


void process(char ** dict, int len)
{
    int validSize = sizeof(int) * len;
    int * valid = (int *)malloc(validSize);
    memset(valid, 0x7F, validSize);

    for (int i = 0; i < len; ++i)
        for (int j = i + 1; j < len; ++j)
            if (check(dict[i], dict[j]))
                valid[i] = valid[j] = 0;
    char ** newDict = NULL;
    int newLen = 0;
    for (int i = 0; i < len; ++i)
        if (valid[i])
            add_word(&newDict, dict[i],
                     &newLen, strlen(dict[i]));
    qsort(newDict, newLen, sizeof(char *), compare);
    free(valid);
    show(newDict, newLen);
    release(newDict, newLen);
}

int main()
{
    freopen("scrabble.in", "r", stdin);
    freopen("scrabble.out", "w", stdout);

    char ** dict = NULL;
    int len = 0;

    fill(&dict, &len);
    process(dict, len);
    release(dict, len);

    fclose(stdin);
    fclose(stdout);
    return 0;
}
