#include <stdio.h>
#include <stdlib.h>

FILE * fin, * fout;
int N, M, I, mat[22][22];
struct immortal {
    int lin, col;
    bool alive;
} immortals[16];
struct battle {
    struct pozition {
        int lin, col;
    } oldpoz, newpoz;
} battles[16];
int dlin[] = {-1, 0, 1, 0};
int dcol[] = {0, 1, 0, -1};

void process()
{
    int i;
    fin = fopen("immortal.in", "rt");
    fout = fopen("immortal.out", "wt");
    fscanf(fin, "%d %d %d", &N, &M, &I);
    for (i = 1; i <= I; i++) {
        fscanf(fin, "%d %d", &immortals[i].lin, &immortals[i].col);
        immortals[i].alive = 1;
        mat[immortals[i].lin][immortals[i].col] = i;
    }
    fclose(fin);
    for (i = 0; i < M + 2; i++) {
        mat[0][i] = -1;
        mat[N + 1][i] = -1;
    }
    for (i = 0; i < N + 2; i++) {
        mat[i][0] = -1;
        mat[i][M + 1] = -1;
    }
}

void backtrack(int fight)
{
    int i, j;
    if (fight == I - 1) {
        for (i = 0; i < fight; i++) {
            fprintf(fout, "%d %d %d %d\n", battles[i].oldpoz.lin, battles[i].oldpoz.col, battles[i].newpoz.lin, battles[i].newpoz.col);
        }
        fclose(fout);
        exit(0);
    } else {
        for (i = 1; i <= I; i++) {
            if (immortals[i].alive) {
                int neighbour, destination;
                for (j = 0; j < 4; j++) {
                    neighbour = mat[immortals[i].lin + dlin[j]][immortals[i].col + dcol[j]];
                    destination = mat[immortals[i].lin + dlin[j] * 2][immortals[i].col + dcol[j] * 2];
                    if (neighbour > 0 && destination == 0) {
                        battles[fight].oldpoz.lin = immortals[i].lin;
                        battles[fight].oldpoz.col = immortals[i].col;
                        battles[fight].newpoz.lin = immortals[i].lin + dlin[j] * 2;
                        battles[fight].newpoz.col = immortals[i].col + dcol[j] * 2;
                        mat[immortals[i].lin][immortals[i].col] = 0;
                        mat[immortals[i].lin + dlin[j]][immortals[i].col + dcol[j]] = 0;
                        mat[immortals[i].lin + dlin[j] * 2][immortals[i].col + dcol[j] * 2] = i;
                        immortals[neighbour].alive = false;
                        immortals[i].lin += dlin[j] * 2;
                        immortals[i].col += dcol[j] * 2;
                        backtrack(fight + 1);
                        immortals[i].lin -= dlin[j] * 2;
                        immortals[i].col -= dcol[j] * 2;
                        immortals[neighbour].alive = true;
                        mat[immortals[i].lin + dlin[j] * 2][immortals[i].col + dcol[j] * 2] = 0;
                        mat[immortals[i].lin + dlin[j]][immortals[i].col + dcol[j]] = neighbour;
                        mat[immortals[i].lin][immortals[i].col] = i;
                    }
                }
            }
        }
    }
}

int main()
{
    process();
    backtrack(0);
    return 0;
}
