#include <cstdio>
#include <cstdlib>

const unsigned long nMax = 100001, inf = 0xffFFffFE;
unsigned long nodes, *** adList, globLen, count, total, parent[nMax];
bool viz[nMax];

struct Q {
    unsigned long node, dist;
    Q()
    {
        node = 0;
        dist = inf;
    }
} queue[nMax];

void read()
{
    unsigned long i, x, y, d, c;
    FILE* fin = fopen("arb2.in", "rt");
    fscanf(fin, "%lu", &nodes);
    adList = (unsigned long***) malloc((nodes + 1) * sizeof(unsigned long**));
    for (i = 1; i <= nodes; i++) {
        adList[i] = (unsigned long**) malloc(sizeof(unsigned long*));
        adList[i][0] = (unsigned long*) malloc(sizeof(unsigned long));
        adList[i][0][0] = 0;
    }
    for (i = 1; i < nodes; i++) {
        fscanf(fin, "%lu %lu %lu %lu", &x, &y, &d, &c);
        adList[x][0][0]++;
        adList[x] = (unsigned long**) realloc(adList[x], (adList[x][0][0] + 1) * sizeof(unsigned long*));
        adList[x][adList[x][0][0]] = (unsigned long*) malloc(3 * sizeof(unsigned long));
        adList[x][adList[x][0][0]][0] = y;
        adList[x][adList[x][0][0]][1] = d;
        adList[x][adList[x][0][0]][2] = c;
    }
    fclose(fin);
}

void dfs(unsigned long node, unsigned long length)
{
    if (!adList[node][0][0]) {
        queue[count].node = node;
        queue[count].dist = length;
        count++;
        if (length > globLen) {
            globLen = length;
        }
    }
    for (unsigned long i = 1; i <= adList[node][0][0]; i++) {
        parent[adList[node][i][0]] = node;
        dfs(adList[node][i][0], length + adList[node][i][1]);
    }
}

void bfs()
{
    unsigned long lo = 0, i, node, minDist, curPar;
    for (i = 0; i < count; i++) {
        queue[i].dist = globLen - queue[i].dist;
    }
    while (lo < count) {
        node = queue[lo].node;
        if (!viz[node]) {
            minDist = inf;
            curPar = parent[node];
            for (i = 0; i < count; i++) {
                if (parent[queue[i].node] == curPar) {
                    if (minDist > queue[i].dist) {
                        minDist = queue[i].dist;
                    }
                }
            }
            for (i = 0; i < count; i++) {
                if (parent[queue[i].node] == curPar) {
                    total += queue[i].dist - minDist;
                    viz[queue[i].node] = 1;
                }
            }
            if (curPar) {
                queue[count].node = curPar;
                queue[count].dist = minDist;
                count++;
            }
        }
        lo++;
    }
}

void process()
{
    parent[1] = 0;
    dfs(1, 0);
    bfs();
}

void write()
{
    FILE* fout = fopen("arb2.out", "wt");
    fprintf(fout, "%lu", total);
    fclose(fout);
}

int main()
{
    read();
    process();
    write();
    return 0;
}
