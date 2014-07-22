#include <cstdio>

const int LEN = 1001;
FILE* fin, * fout;
char temp[LEN], sab[LEN], str[LEN];

void safety()
{
    bool flag = 0;
    int i, k;
    for (i = 0, k = 0; temp[i]; i++) {
        if (temp[i] == '*') {
            if (!flag) {
                flag = 1;
                sab[k++] = temp[i];
            }
        } else {
            flag = 0;
            sab[k++] = temp[i];
        }
    }
    sab[k] = 0;
}

bool process(int head, int curs)
{
    if (sab[head] && str[curs]) {
        if (sab[head] == '?') {
            return process(head + 1, curs + 1);
        } else if (sab[head] == '*') {
            int i;
            for (i = 0; str[curs + i]; i++) {
                if (process(head + 1, curs + i)) {
                    return 1;
                }
            }
            if (process(head + 1, curs + i)) {
                return 1;
            }
            return 0;
        } else {
            if (sab[head] != str[curs]) {
                return 0;
            } else {
                return process(head + 1, curs + 1);
            }
        }
    } else {
        if (sab[head] || str[curs]) {
            if (sab[head] == '*' && !sab[head + 1]) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 1;
        }
    }
}

int main()
{
    int nr;
    fin = fopen("sablon.in", "rt");
    fout = fopen("sablon.out", "wt");
    fscanf(fin, "%d", &nr);
    fscanf(fin, "%s", temp);
    safety();
    for (int i = 1; i <= nr; i++) {
        fscanf(fin, "%s", str);
        if (process(0, 0)) {
            fprintf(fout, "%d\n", i);
        }
    }
    fclose(fin);
    fclose(fout);
    return 0;
}
