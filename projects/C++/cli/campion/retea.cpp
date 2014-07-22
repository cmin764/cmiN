#include <cstdio>

const int n = 101, inf = 0x3fFF;
int noduri, mat[n][n], cost[n], viz[n];

void init()
{
    for (int i = 1; i <= noduri; i++) {
        cost[i] = inf;
    }
}

void process()
{
    int coada[n], le, ri, i, nod;
    cost[1] = 0;
    le = ri = 1;
    coada[le] = 1;
    viz[1] = 1;
    while (le <= ri) {
        nod = coada[le++];
        for (i = 1; i <= noduri; i++) {
            if (mat[nod][i]) {
                if (cost[nod] + 1 < cost[i]) {
                    cost[i] = cost[nod] + 1;
                }
                if (!viz[i]) {
                    viz[i] = 1;
                    coada[++ri] = i;
                }
            }
        }
    }
}

void write()
{
    for (int i = 2; i <= noduri; i++) {
        printf("%d ", cost[i]);
    }
}

int main()
{
    int muchii, x, y;
    freopen("retea.in", "rt", stdin);
    freopen("retea.out", "wt", stdout);
    scanf("%d %d", &noduri, &muchii);
    while (muchii-- > 0) {
        scanf("%d %d", &x, &y);
        mat[x][y] = mat[y][x] = 1;
    }
    init();
    process();
    write();
    fclose(stdin);
    fclose(stdout);
    return 0;
}
