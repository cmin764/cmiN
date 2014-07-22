#include <stdio.h>

long func(long a, long b)
{
    if (b) {
        return func(b, a % b);
    } else {
        return a;
    }
}

int main()
{
    long a, b, t;
    freopen("euclid2.in", "rt", stdin);
    freopen("euclid2.out", "wt", stdout);
    scanf("%ld", &t);
    for(; t > 0; --t) {
        scanf("%ld %ld", &a, &b);
        printf("%ld\n", func(a, b));
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
