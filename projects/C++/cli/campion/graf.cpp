#include <cstdio>
#include <cstdlib>

const int nMax = 7501, mMax = 14000, inf = 0x3fFF;
FILE* fin, * fout;
int nodes, edges, length[nMax], start, end, cmax = -1, count = -1, usedNode[nMax];
bool vizNode[nMax];
int* list[nMax];

void read()
{
    int i, x, y;
    fin = fopen("graf.in", "rt");
    fout = fopen("graf.out", "wt");
    fscanf(fin, "%d %d %d %d", &nodes, &edges, &start, &end);
    for (i = 1; i <= nodes; i++) {
        list[i] = (int*) malloc(sizeof(int));
        list[i][0] = 0;
    }
    for (i = 0; i < edges; i++) {
        fscanf(fin, "%d %d", &x, &y);
        list[x][0]++;
        list[y][0]++;
        list[x] = (int*) realloc(list[x], (list[x][0] + 1) * sizeof(int));
        list[y] = (int*) realloc(list[y], (list[y][0] + 1) * sizeof(int));
        list[x][list[x][0]] = y;
        list[y][list[y][0]] = x;
    }
}

void bfs()
{
    int queue[nMax], lo, hi, node;
    lo = hi = 0;
    queue[0] = start;
    vizNode[start] = 1;
    while (lo <= hi && !vizNode[end]) {
        node = queue[lo++];
        for (int i = 1; i <= list[node][0] && !vizNode[end]; i++) {
            if (!vizNode[list[node][i]]) {
                vizNode[list[node][i]] = 1;
                length[list[node][i]] = length[node] + 1;
                queue[++hi] = list[node][i];
            }
        }
    }
}

void search_back(int node)
{
    int ways = 0;
    for (int i = 1; i <= list[node][0]; i++) {
        if (length[list[node][i]] == length[node] - 1) {
            ways++;
            usedNode[list[node][i]]++;
            search_back(list[node][i]);
        }
    }
    if (ways == 0) {
        ways = 1;
    }
    usedNode[node] = usedNode[node] * ways;
    if (usedNode[node] > cmax) {
        cmax = usedNode[node];
        count = 1;
    } else if (usedNode[node] == cmax) {
        count++;
    }
}

void solve()
{
    for (int i = 1; i <= nodes; i++) {
        length[i] = inf;
    }
    length[start] = 0;
    bfs();
    search_back(end);
    usedNode[end] = cmax;
    count++;
}

void write()
{
    fprintf(fout, "%d\n", count);
    for (int i = 1; i <= nodes; i++) {
        if (usedNode[i] == cmax) {
            fprintf(fout, "%d ", i);
        }
    }
    fclose(fin);
    fclose(fout);
}

int main()
{
    read();
    solve();
    write();
    return 0;
}
