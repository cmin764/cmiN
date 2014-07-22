#include <cstdio>
#include <cstdlib>
#define ifname "dfs.in"
#define ofname "dfs.out"

typedef unsigned long ul_t;
const ul_t nMax = 100001;
ul_t nodes, edges, ** adl, nr;
bool viz[nMax];

void init()
{
    ul_t i, x, y;
    FILE* fin = fopen(ifname, "rt");
    fscanf(fin, "%lu %lu", &nodes, &edges);
    adl = (ul_t**) malloc((nodes + 1) * sizeof(ul_t*));
    for (i = 1; i <= nodes; i++) {
        adl[i] = (ul_t*) malloc(sizeof(ul_t));
        adl[i][0] = 0;
    }
    for (i = 0; i < edges; i++) {
        fscanf(fin, "%lu %lu", &x, &y);
        adl[x] = (ul_t*) realloc(adl[x], (++adl[x][0] + 1) * sizeof(ul_t));
        adl[y] = (ul_t*) realloc(adl[y], (++adl[y][0] + 1) * sizeof(ul_t));
        adl[x][adl[x][0]] = y;
        adl[y][adl[y][0]] = x;
    }
    fclose(fin);
}

void dfs(ul_t node)
{
    viz[node] = 1;
    for (ul_t i = 1; i <= adl[node][0]; i++) {
        if (!viz[adl[node][i]]) {
            dfs(adl[node][i]);
        }
    }
}

void write()
{
    FILE* fout = fopen(ofname, "wt");
    fprintf(fout, "%lu", nr);
    fclose(fout);
    free(adl);
}

int main()
{
    init();
    for (ul_t i = 1; i <= nodes; i++) {
        if (!viz[i]) {
            dfs(i);
            nr++;
        }
    }
    write();
    return 0;
}
