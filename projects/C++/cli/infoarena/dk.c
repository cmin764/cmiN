#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ACU 6

inline int logpow(long long bs, int ex, const int mod)
{
    long long res = 1;
    while (ex) {
        if (ex & 1) {
            res = res * bs % mod;
            --ex;
        }
        bs = bs * bs % mod;
        ex >>= 1;
    }
    return (int)res;
}

inline short process(int nr)
{
    short i;
    int base;
    --nr;
    for (i = 0; i < ACU; ++i) {
        base = rand() % nr + 1;
        if (logpow(base, nr, nr + 1) != 1) {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int total = 0, nr, n;
    freopen("dk.in", "rt", stdin);
    freopen("dk.out", "wt", stdout);
    srand(time(0));
    for (scanf("%d", &n); n; --n) {
        scanf("%d", &nr);
        if (nr == 1) {
            continue;
        } else if (nr == 2 || process(nr)) {
            ++total;
        }
    }
    printf("%d", total);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
