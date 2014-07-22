#include <cstdio>

const char* iname = "dijkstra.in", * oname = "dijkstra.out";
const long inf = 0x3fFFffFF, cmax = 250000;
const unsigned int nmax = 50001;
struct curve {
    unsigned int x, y;
    int cost;
} curves[cmax];
unsigned int nodes;
long curve_nr, dist[nmax];

void read()
{
    freopen(iname, "rt", stdin);
    freopen(oname, "wt", stdout);
    scanf("%u %ld", &nodes, &curve_nr);
    for (unsigned int i = 2; i <= nodes; i++) {
        dist[i] = inf;
    }
    for (long i = 0; i < curve_nr; i++) {
        scanf("%u %u %d", &curves[i].x, &curves[i].y, &curves[i].cost);
        if (curves[i].x == 1) {
            dist[curves[i].y] = curves[i].cost;
        }
    }
}

void dijkstra()
{
    bool flag = true;
    while (flag) {
        flag = false;
        for (long i = 0; i < curve_nr; i++) {
            if (dist[curves[i].y] > dist[curves[i].x] + curves[i].cost) {
                dist[curves[i].y] = dist[curves[i].x] + curves[i].cost;
                flag = true;
            }
        }
    }
}

void write()
{
    for (int i = 2; i <= nodes; i++) {
        if (dist[i] == inf) {
            printf("%ld ", 0);
        } else {
            printf("%ld ", dist[i]);
        }
    }
    fclose(stdin);
    fclose(stdout);
}

int main()
{
    read();
    dijkstra();
    write();
    return 0;
}
