#include <cstdio>
#include <cmath>

const int nmax = 10;
int n, vec[nmax];
bool viz[nmax];

bool prim()
{
    long long nr = 0, rad;
    for (int i = 0; i < n; i++) {
        nr = nr * 10 + vec[i];
    }
    rad = sqrt(nr);
    for (long long i = 2; i <= rad; i++) {
        if (!(nr % i)) {
            return 0;
        }
    }
    return 1;
}

void back(int poz)
{
    if (poz == n) {
        if (prim()) {
            for (int i = 0; i < n; i++) {
                printf("%d", vec[i]);
            }
            printf("\n");
        }
    } else {
        for (int i = 0; i < 10; i++) {
            if (!viz[i]) {
                viz[i] = 1;
                vec[poz] = i;
                back(poz + 1);
                viz[i] = 0;
            }
        }
    }
}

int main()
{
    printf("n: ");
    scanf("%d", &n);
    for (int i = 1; i < 10; i++) {
        viz[i] = 1;
        vec[0] = i;
        back(1);
        viz[i] = 0;
    }
    return 0;
}
