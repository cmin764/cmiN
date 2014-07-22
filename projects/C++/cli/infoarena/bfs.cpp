#include <cstdio>
#include <cstdlib>
#include <cstring>
#define ifname "bfs.in"
#define ofname "bfs.out"

const unsigned long nMax = 100001;
unsigned long nodes, edges, ** adList, queue[nMax];
long dist[nMax];

void init(unsigned long& src)
{
    unsigned long i, x, y;
    FILE* fin = fopen(ifname, "rt");
    fscanf(fin, "%lu %lu %lu", &nodes, &edges, &src);
    adList = (unsigned long**) malloc((nodes + 1) * sizeof(unsigned long*));
    for (i = 1; i <= nodes; i++) {
        adList[i] = (unsigned long*) malloc(sizeof(unsigned long));
        adList[i][0] = 0;
    }
    for (i = 0; i < edges; i++) {
        fscanf(fin, "%lu %lu", &x, &y);
        adList[x][0]++;
        adList[x] = (unsigned long*) realloc(adList[x], (adList[x][0] + 1) * sizeof(unsigned long));
        adList[x][adList[x][0]] = y;
    }
    memset(dist, -1, nMax);
    fclose(fin);
}

void bfs(const unsigned long& src)
{
    unsigned long lo, hi, i, node;
    lo = hi = 0;
    queue[0] = src;
    dist[src] = 0;
    while (lo <= hi) {
        node = queue[lo++];
        for (i = 1; i <= adList[node][0]; i++) {
            if (dist[adList[node][i]] == -1) {
                dist[adList[node][i]] = dist[node] + 1;
                queue[++hi] = adList[node][i];
            }
        }
    }
}

void write()
{
    FILE* fout = fopen(ofname, "wt");
    for (unsigned long i = 1; i <= nodes; i++) {
        fprintf(fout, "%ld ", dist[i]);
    }
    fclose(fout);
}

int main()
{
    unsigned long src;
    init(src);
    bfs(src);
    write();
    return 0;
}
