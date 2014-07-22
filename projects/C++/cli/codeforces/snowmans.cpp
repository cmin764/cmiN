#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;


class Snow {
    /**
     * A simple class representing a snowman.
     * It has three distinct balls.
     */

    int chunk[3]; // balls
    int cur; // current index

    public:
    Snow()
    {
        chunk[0] = -1;
        chunk[1] = -1;
        chunk[2] = -1;
        cur = 0;
    }

    bool full()
    {
        if (cur == 3) return true;
        return false;
    }

    bool set(int radi)
    {
        /** Add a ball only if it differs from the others. */
        if (radi == chunk[0] || radi == chunk[1] || radi == chunk[2]) return false;
        else if (full()) return false;
        chunk[cur++] = radi;
        return true;
    }

    int get()
    {
        int value = max(chunk[0], max(chunk[1], chunk[2]));
        if (value == chunk[0]) chunk[0] = -1;
        else if (value == chunk[1]) chunk[1] = -1;
        else if (value == chunk[2]) chunk[2] = -1;
        return value;
    }
};


class Comp {

    public:
    typedef pair<int, int> pii_t; // range, count

    bool operator()(pii_t first, pii_t second) const
    {
        return first.second > second.second; // reverse
    }
};


typedef multiset<Comp::pii_t, Comp> sp_t;
int nr;
sp_t balls;
vector<Snow> snows;


void update(sp_t::iterator& it, int value)
{
    Comp::pii_t tmp(it->first, it->second + value);
    balls.erase(it++);
    if (tmp.second) balls.insert(it, tmp); // optimized insertion
}


void solve()
{
    /** Aprox. O(N^2). */
    /* select balls from top radiuses */
    while (balls.size() >= 3) {
        Snow man; // temporar
        while (!man.full()) { // fill it with balls
            sp_t::iterator it = balls.begin();
            bool status = false; // query one value
            while (!status) { // first 3 types
                status = man.set(it->first);
                if (status) update(it, -1);
                else ++it;
            }
        }
        snows.push_back(man);
    }
}


int main()
{
    //freopen("test.in", "rt", stdin);
    cin >> nr;
    for (int i = 0, radi; i < nr; ++i) {
        cin >> radi;
        sp_t::iterator it;
        for (it = balls.begin(); it != balls.end(); ++it) {
            if (it->first == radi) break;
        }
        if (it != balls.end()) update(it, 1);
        else balls.insert(make_pair(radi, 1));
    }
    solve();
    cout << snows.size() << endl;
    for (vector<Snow>::iterator it = snows.begin(); it != snows.end(); ++it) {
        cout << it->get() << " ";
        cout << it->get() << " ";
        cout << it->get() << " ";
        cout << endl;
    }
    return 0;
}
