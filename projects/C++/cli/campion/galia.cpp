#include <cstdio>
#include <cstdlib>

const int nMax = 101, mMax = 1000, cinf = 0x3fFF;
int nodes, edges, selected, mat[nMax][nMax];
struct edge {
    int x, y, c;
} edgeVec[mMax], edgeSel[mMax];
bool viz[nMax], vizEdge[mMax], flag, vizNode[nMax];
FILE* fin, * fout;

void read()
{
    fin = fopen("galia.in", "rt");
    fout = fopen("galia.out", "wt");
    fscanf(fin, "%d %d", &nodes, &edges);
    for (int i = 0; i < edges; i++) {
        fscanf(fin, "%d %d %d", &edgeVec[i].x, &edgeVec[i].y, &edgeVec[i].c);
    }
}

int compare(const void* first, const void* second)
{
    return ((edge*)first)->c - ((edge*)second)->c;
}

void prim()
{
    edgeSel[selected++] = edgeVec[0];
    vizEdge[0] = 1;
    viz[edgeVec[0].x] = viz[edgeVec[0].y] = 1;
    while (selected < nodes - 1) {
        for (int i = 1; i < edges; i++) {
            if (viz[edgeVec[i].x] && !viz[edgeVec[i].y]) {
                edgeSel[selected++] = edgeVec[i];
                viz[edgeVec[i].y] = 1;
                vizEdge[i] = 1;
                break;
            } else if (!viz[edgeVec[i].x] && viz[edgeVec[i].y]) {
                edgeSel[selected++] = edgeVec[i];
                viz[edgeVec[i].x] = 1;
                vizEdge[i] = 1;
                break;
            }
        }
    }
}

void init_viz()
{
    for (int k = 1; k <= nodes; k++) {
        vizNode[k] = 0;
    }
}

void DFS(int startNode, int endNode, int parent[])
{
    if (startNode == endNode) {
        flag = 1;
    }
    vizNode[startNode] = 1;
    for (int k = 1; !flag && k <= nodes; k++) {
        if (mat[startNode][k] && !vizNode[k]) {
            parent[k] = startNode;
            DFS(k, endNode, parent);
        }
    }
}

int test_edge(int i, int& j)
{
    int startNode = edgeVec[i].x, endNode = edgeVec[i].y, parent[nMax], temp, cmax = 0;
    init_viz();
    parent[startNode] = 0;
    DFS(startNode, endNode, parent);
    temp = parent[endNode];
    while (temp != 0) {
        if (cmax < mat[endNode][temp]) {
            cmax = mat[endNode][temp];
        }
        endNode = temp;
        temp = parent[endNode];
    }
    for (int e = 0; e < selected; e++) {
        if (edgeSel[e].c == cmax) {
            j = e;
            break;
        }
    }
    return edgeVec[i].c - cmax;
}

void write()
{
    fprintf(fout, "%d\n", selected);
    for (int i = 0; i < selected; i++) {
        fprintf(fout, "%d %d\n", edgeSel[i].x, edgeSel[i].y);
        mat[edgeSel[i].x][edgeSel[i].y] = mat[edgeSel[i].y][edgeSel[i].x] = edgeSel[i].c;
    }
}

void solve()
{
    int minValue = cinf, val, toAdd = -1, toDel = -1;
    qsort(edgeVec, edges, sizeof(edge), compare);
    prim();
    write();
    fflush(fout);
    for (int i = 0, j; i < edges; i++) {
        if (!vizEdge[i]) {
            val = test_edge(i, j);
            if (val < minValue) {
                minValue = val;
                toAdd = i;
                toDel = j;
            }
        }
    }
    edgeSel[toDel] = edgeVec[toAdd];
    write();
    fclose(fin);
    fclose(fout);
}

int main()
{
    read();
    solve();
    return 0;
}
