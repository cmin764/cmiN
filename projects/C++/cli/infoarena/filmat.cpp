#include <stdio.h>

const unsigned int nmax = 1000;
unsigned int N, steps = 0;
bool mat[nmax][nmax], tmp[nmax][nmax];

void read()
{
    unsigned int i, j;
    freopen("filmat.in", "rt", stdin);
    scanf("%d", &N);
    for (i = 1; i <= N; i++) {
        for (j = 1; j <= N; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
    fclose(stdin);
}

void write()
{
    freopen("fimat.out", "wt", stdout);
    printf("%d", steps);
    fclose(stdout);
}

void update(bool mat[][nmax], bool tmp[][nmax])
{
    unsigned int i, j;
    for (i = 0; i <= N; i++) {
        for (j = 0; j <= N; j++) {
            mat[i][j] = tmp[i][j];
        }
    }
}

void process()
{
    update(tmp, mat);
    unsigned int i, j, k, vecini;
    bool status = true;
    int dlin[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dcol[] = {0, 1, 1, 1, 0, -1, -1, -1};
    while (status) {
        status = false;
        for (i = 1; i <= N; i++) {
            for (j = 1; j <= N; j++) {
                if (!mat[i][j]) {
                    vecini = 0;
                    for (k = 0; k < 8; k++) {
                        if (mat[i + dlin[k]][j + dcol[k]]) {
                            vecini++;
                            if (vecini >= 3) {
                                status = true;
                                tmp[i][j] = 1;
                                break;
                            }
                        }
                    }
                }
            }
        }
        if (status) {
            update(mat, tmp);
            steps++;
        }
    }
}

int main()
{
    read();
    process();
    write();
    return 0;
}
