#include <stdio.h>
#include <ctype.h>
#define base 1000000000
#define len 9
#define N 1113

unsigned long first[N], second[N], last[2 * N];
unsigned short todel;

inline void init()
{
    char chr;
    unsigned short cnt;
    unsigned long total;
    todel = first[0] = second[0] = 0;
    cnt = 0;
    total = getchar() - '0';
    while (!isspace(chr = getchar())) {
        if (++cnt != len) {
            total = total * 10 + chr - '0';
        } else {
            first[++first[0]] = total;
            total = chr - '0';
            cnt = 0;
        }
    }
    todel += len - ++cnt;
    if (total) {
        while (cnt < len) {
            total *= 10;
            ++cnt;
        }
    }
    first[++first[0]] = total;
    cnt = 0;
    total = getchar() - '0';
    while (!(isspace(chr = getchar()) || chr == EOF)) {
        if (++cnt != len) {
            total = total * 10 + chr - '0';
        } else {
            second[++second[0]] = total;
            total = chr - '0';
            cnt = 0;
        }
    }
    todel += len - ++cnt;
    if (total) {
        while (cnt < len) {
            total *= 10;
            ++cnt;
        }
    }
    second[++second[0]] = total;
    //printf("%hu\n", todel);
}

inline void zfill(unsigned long nr)
{
    short i;
    if (nr) {
        while (nr < base / 10) {
            putchar('0');
            nr *= 10;
        }
    } else {
        for (i = 1; i < len; ++i) {
            putchar('0');
        }
    }
}

inline void process()
{
    unsigned long long temp;
    unsigned short i, j;
    last[0] = first[0] + second[0];
    if (!first[1] || !second[1]) {
        putchar('0');
    } else {
        //printf("%lu\n", last[0]);
        for (i = first[0]; i > 0; --i) {
            temp = 0;
            for (j = second[0]; j > 0; --j) {
                temp = (unsigned long long) first[i] * second[j] + temp + last[i + j];
                last[i + j] = temp % base;
                temp /= base;
                //printf("%lu %lu\n", (unsigned long) temp, last[i + j]);
            }
            last[i + j] = temp;
        }
        if (last[0] > 2) {
            printf("%lu", last[1]);
            last[1] = 0;
            for (i = 2; i < last[0] - 1; ++i) {
                zfill(last[i]);
                printf("%lu", last[i]);
                last[i] = 0;
            }
        }
        if (todel < 9) {
            if (last[0] > 2) {
                zfill(last[last[0] - 1]);
            }
            printf("%lu", last[last[0] - 1]);
            temp = last[last[0]];
            if (temp) {
                zfill(temp);
            }
        } else {
            todel -= 9;
            temp = last[last[0] - 1];
            if (temp && last[0] > 2) {
                zfill(temp);
            }
        }
        if (temp) {
            while (todel) {
                temp /= 10;
                --todel;
            }
            printf("%lu", (unsigned long) temp);
        } else {
            i = len - todel;
            while (i) {
                putchar('0');
                --i;
            }
        }
    }
    putchar('\n');
    last[last[0]] = last[last[0] - 1] = 0;
}

int main()
{
    short nr;
    freopen("mul.in", "rt", stdin);
    freopen("cmul.out", "wt", stdout);
    scanf("%hd\n", &nr);
    while (nr-- > 0) {
        init();
        process();
    }
    return 0;
}
