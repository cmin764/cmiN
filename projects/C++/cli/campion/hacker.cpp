#include <cstdio>
#include <vector>
#define iname "hacker.in"
#define oname "hacker.out"
using namespace std;

typedef vector<vector<pair<int, short> > > Obj;
bool flag;
int nodes, queries;
Obj adList;

inline void process(int ant, int src, int dist)
{
    if (dist <= 0) {
        for (Obj::size_type i = 0; i < adList[src].size(); ++i) {
            if (adList[src][i].first == ant) {
                printf("%d %d %hd\n", ant, src, adList[src][i].second + dist);
                flag = false;
            }
        }
    } else {
        for (Obj::size_type i = 0; i < adList[src].size() && flag; ++i) {
            if (adList[src][i].first != ant) {
                process(src, adList[src][i].first, dist - adList[src][i].second);
            }
        }
    }
}

int main()
{
    int i, x, y;
    short d;
    freopen(iname, "rt", stdin);
    freopen(oname, "wt", stdout);
    scanf("%d %d", &nodes, &queries);
    adList.resize(nodes + 1);
    for (i = 1; i < nodes; ++i) {
        scanf("%d %d %hd", &x, &y, &d);
        adList[x].push_back(make_pair(y, d));
        adList[y].push_back(make_pair(x, d));
    }
    for (i = 0; i < queries; ++i) {
        flag = true;
        scanf("%d %d", &x, &y);
        process(x, x, y);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
