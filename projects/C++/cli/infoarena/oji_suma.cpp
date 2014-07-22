#include <cstdio>
#include <cstdlib>

const unsigned int nMax = 0xffFF;
const unsigned long inf = 0x7fFFffFF;
FILE* fin, * fout;
unsigned int*** cost, niv = 1, road[nMax], dl[] = {0, 0, 1, 1}, dc[] = {0, 1, 0, 1};
unsigned long*** total, min = inf;

void init()
{
    unsigned int nr, sum = 0, i, j, c;
    fin = fopen("suma.in", "rt");
    fout = fopen("suma.out", "wt");
    fscanf(fin, "%u", &nr);
    while (sum < nr) {
        cost = (unsigned int***) realloc(cost, niv * sizeof(unsigned int**));
        total = (unsigned long***) realloc(total, niv * sizeof(unsigned long**));
        cost[niv - 1] = (unsigned int**) malloc(niv * sizeof(unsigned int*));
        total[niv - 1] = (unsigned long**) malloc(niv * sizeof(unsigned long*));
        for (i = 0; i < niv; i++) {
            cost[niv - 1][i] = (unsigned int*) malloc(niv * sizeof(unsigned int));
            total[niv - 1][i] = (unsigned long*) malloc(niv * sizeof(unsigned long));
            for (j = 0; j < niv; j++) {
                fscanf(fin, "%u", &c);
                cost[niv - 1][i][j] = c;
                total[niv - 1][i][j] = inf;
            }
        }
        sum += niv * niv;
        niv++;
    }
    niv--;
}

void process()
{
    unsigned int i, j, k, d, sum = 1;
    total[0][0][0] = cost[0][0][0];
    road[0] = 1;
    for (i = 1; i < niv; i++) {
        min = inf;
        for (j = 0; j < i; j++) {
            for (k = 0; k < i; k++) {
                for (d = 0; d < 4; d++) {
                    if (total[i - 1][j][k] + cost[i][j + dl[d]][k + dc[d]] < total[i][j + dl[d]][k + dc[d]]) {
                        total[i][j + dl[d]][k + dc[d]] = total[i - 1][j][k] + cost[i][j + dl[d]][k + dc[d]];
                        if (min > total[i][j + dl[d]][k + dc[d]]) {
                            min = total[i][j + dl[d]][k + dc[d]];
                            road[i] = sum + 1 + (j + dl[d]) * (i + 1) + (k + dc[d]);
                        }
                    }
                }
            }
        }
        sum = sum + (i + 1) * (i + 1);
    }
}

void write()
{
    fprintf(fout, "%u %lu\n", niv, min);
    for (unsigned int i = 0; i < niv; i++) {
        fprintf(fout, "%u ", road[i]);
    }
    fclose(fin);
    fclose(fout);
}

int main()
{
    init();
    process();
    write();
    return 0;
}
