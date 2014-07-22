#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
using namespace std;


struct Per {

    string name;
    int hs, height;

    Per()
    {
        hs = 0;
        height = 1;
    }
} per;


struct Comp {

    bool operator()(const Per& first, const Per& second) const
    {
        return first.hs < second.hs;
    }
} comp;


typedef set<int> si_t;
vector<Per> pers;
int nr;


int main()
{
    //freopen("C.in", "rt", stdin);
    cin >> nr;
    pers.reserve(nr);
    for (int i = 0; i < nr; ++i) {
        cin >> per.name >> per.hs;
        pers.push_back(per);
    }
    sort(pers.begin(), pers.end(), comp);
    si_t pos;
    for (int i = 0, rem; i < nr; ++i) {
        if (pers[i].hs > i) {
            cout << -1;
            return 0;
        } else if ((rem = pers[i].hs - pos.size()) > 0) {
            for (int j = i - 1; rem; --j) {
                pair<si_t::iterator, bool> ret = pos.insert(j);
                if (ret.second) --rem;
            }
            for (si_t::iterator it = pos.begin(); it != pos.end(); ++it) ++pers[*it].height;
        }
    }
    for (int i = 0; i < nr; ++i) {
        cout << pers[i].name << " " << pers[i].height << endl;
    }
    return 0;
}
