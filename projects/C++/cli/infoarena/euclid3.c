#include <stdio.h>

inline void func(int a, int b, int c)
{
    int x1, x2, y1, y2, tmp;
    x1 = y2 = 1;
    x2 = y1 = 0;
    while (b) {
        x1 -= (a / b) * x2;
        y1 -= (a / b) * y2;
        tmp = x1;
        x1 = x2;
        x2 = tmp;
        tmp = y1;
        y1 = y2;
        y2 = tmp;
        tmp = a;
        a = b;
        b = tmp % b;
    }
    if (c % a) {
        printf("0 0\n");
    } else {
        printf("%d %d\n", x1 * (c / a), y1 * (c / a));
    }
}

int main()
{
    int a, b, c, t;
    freopen("euclid3.in", "rt", stdin);
    freopen("euclid3.out", "wt", stdout);
    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d %d %d", &a, &b, &c);
        func(a, b, c);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
