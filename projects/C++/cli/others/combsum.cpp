/*
 * Se pastreaza in vector doar elementele mai mici sau egale cu suma maxima.
 * Apoi acestea sunt sortate pentru a optimiza generarea solutiilor.
 * Si in final avem o complexitate mult mai buna decat 2^N.
 */


#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int nr, sum, tmp;
vector<int> vec, sol;


void parse()
{
    cin >> nr >> sum;
    vec.resize(nr);
    for (int i = 0; i < nr; ++i) {
        cin >> vec[i];
        if (vec[i] > sum) {
            --i;
            --nr;
        }
    }
    vec.resize(nr);
    sort(vec.begin(), vec.end());
}


inline void show()
{
    for (int i = 0; i < sol.size(); ++i) cout << sol[i] << " ";
    cout << endl;
}


void solve(int tot, int pos)
{
    for (++pos; pos < nr; ++pos) {
        if (tot + vec[pos] <= sum) {
            sol.push_back(vec[pos]);
            show();
            solve(tot + vec[pos], pos);
            sol.pop_back();
        } else break;
    }
}


int main()
{
    //freopen("combsum.in", "rt", stdin);
    parse();
    for (int i = 0; i < nr; ++i) {
        sol.push_back(vec[i]);
        solve(vec[i], i);
        sol.pop_back();
    }
    return 0;
}
