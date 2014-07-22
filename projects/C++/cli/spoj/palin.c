#include <stdio.h>
#define N 1000010

int len;
char vec[N], ciot;

inline short is_palin()
{
    short flag = 1;
    int mid = len / 2;
    for (; flag && mid < len; ++mid) {
        if (vec[mid] != vec[len - mid - 1]) {
            flag = 0;
        }
    }
    return flag;
}

inline void gen(short flag)
{
    int mid = len / 2;
    while (mid < len - 1 && vec[mid] == vec[len - mid - 1]) {
        ++mid;
    }
    if (vec[mid] < vec[len - mid - 1]) {
        while (mid < len) {
            vec[mid] = vec[len - mid - 1];
            ++mid;
        }
    } else {
        mid = len / 2;
        if (!flag) {
            --mid;
        }
        while (mid >= 0 && ++vec[mid] > '9') {
            vec[mid] = '0';
            --mid;
        }
        if (mid < 0) {
            ciot = '1';
        }
        mid = len / 2;
        while (mid < len) {
            vec[mid] = vec[len - mid - 1];
            ++mid;
        }
    }
}

int main()
{
    int test;
    char chr;
    freopen("palin.in", "rt", stdin);
    for (scanf("%d\n", &test); test; --test) {
        len = 0;
        ciot = '0';
        while ((chr = getchar()) != '\n') {
            vec[len++] = chr;
        }
        vec[len] = '\0';
        if (len == 1) {
            if (vec[0] == '9') {
                vec[0] = '1';
                vec[1] = '1';
                vec[2] = '\0';
            } else {
                ++vec[0];
            }
        } else {
            gen(len % 2);
            if (ciot != '0') {
                putchar(ciot);
                vec[len - 1] += ciot - '0';
            }
        }
        puts(vec);
    }
    return 0;
}
