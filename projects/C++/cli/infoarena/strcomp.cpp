#include <cstdio>
#include <cstdlib>

const int n = 256;
int * lines;
const char voc[] = "aAeEiIoOuU";
char** mat;

bool str_find(const char* source, const char c)
{
    for (const char* pch = source; *pch; pch++) {
        if (*pch == c) {
            return 1;
        }
    }
    return 0;
}

int str_comp(char* str1, char* str2, int len1, int len2)
{
    int x = len1, y = len2;
    if (*str1 && *str2) {
        if (str_find(voc, *str1)) {
            x++;
        }
        if (str_find(voc, *str2)) {
            y++;
        }
        return str_comp(str1 + 1, str2 + 1, x, y);
    } else if (*str1) {
        if (str_find(voc, *str1)) {
            x++;
        }
        return str_comp(str1 + 1, str2, x, y);
    } else if (*str2) {
        if (str_find(voc, *str2)) {
            y++;
        }
        return str_comp(str1, str2 + 1, x, y);
    } else {
        if (x == y) {
            return 0;
        } else if (x > y) {
            return 1;
        } else {
            return 2;
        }
    }
}

int compare(const void* first, const void* second)
{
    const int* a, * b;
    a = (const int*) first;
    b = (const int*) second;
    int res = str_comp(mat[*a - 1], mat[*b - 1], 0, 0);
    if (res == 2) {
        return -1;
    } else {
        return res;
    }
}

int main()
{
    FILE* fin, * fout;
    lines = (int*) malloc(sizeof(int));
    lines[0] = 0;
    fin = fopen("poveste.in", "rt");
    fout = fopen("poveste.out", "wt");
    while (!feof(fin)) {
        mat = (char**) realloc(mat, ++lines[0] * sizeof(char*));
        mat[lines[0] - 1] = (char*) malloc(n * sizeof(char));
        fscanf(fin, "%s \n", mat[lines[0] - 1]);
        lines = (int*) realloc(lines, (lines[0] + 1) * sizeof(int));
        lines[lines[0]] = lines[0];
    }
    qsort(lines + 1, lines[0], sizeof(int), compare);
    for (int i = 1; i <= lines[0]; i++) {
        fprintf(fout, "%s\n", mat[lines[i] - 1]);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}
