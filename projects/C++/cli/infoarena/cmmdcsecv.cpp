#include <stdio.h>

const unsigned int nmax = 1000;
unsigned int vec[nmax], N, secvmax = 0;

void read()
{
    unsigned int i;
    freopen("cmmdcsecv.in", "rt", stdin);
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &vec[i]);
    }
    fclose(stdin);
}

void write()
{
    freopen("cmmdcsecv.out", "wt", stdout);
    printf("%d", secvmax);
    fclose(stdout);
}

inline unsigned int compute(unsigned int i, unsigned int len)
{
    unsigned int a, b, r;
    len--;
    b = vec[i + len];
    while (len-- > 0) {
        a = vec[i + len];
        r = a % b;
        while (r) {
            a = b;
            b = r;
            r = a % b;
        }
    }
    return b;
}

void process()
{
    unsigned int i, len = N;
    while (len > 0 && !secvmax) {
        for (i = 0; i + len <= N; i++) {
            if (compute(i, len) > 1) {
                secvmax = len;
                break;
            }
        }
        len--;
    }
}

int main()
{
    read();
    process();
    write();
    return 0;
}
