#include <cstdio>
#include <cmath>
#include <iostream>
#include <set>
using namespace std;


typedef set<int> si_t;


int solve(int lo, int hi)
{
    // take every single number from lo to hi
    int total = 0;
    for (int nr = lo; nr < hi; ++nr) {
        // make a storage for rotated numbers
        // do not take care of leading zeros, it will result a lesser number
        si_t pack;
        int len = 0, clone = nr;
        while (clone > 0) {
            ++len;
            clone /= 10;
        }
        --len;
        clone = nr;
        int pos = pow(10, len);
        // rotate len times
        //cerr << nr << " ";
        for (int i = 0; i < len; ++i) {
            int last = clone % 10;
            clone = clone / 10 + pos * last;
            //cerr << clone << " ";
            if (clone > nr && clone <= hi) pack.insert(clone);
        }
        //cerr << endl;
        total += pack.size();
    }
    return total;
}


int main()
{
    freopen("C-large.in", "r", stdin);
    freopen("C-large.out", "w", stdout);
    int tests;
    cin >> tests;
    for (int i = 1; i <= tests; ++i) {
        int lo, hi;
        cin >> lo >> hi;
        printf("Case #%d: %d\n", i, solve(lo, hi));
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
