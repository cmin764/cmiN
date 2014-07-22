#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;


int* vec;


void update(int node, int left, int right, int pos, int value)
{
    /// Update every affected range by going up from the changed leaf.
    if (left == right) { // elementar range
        vec[node] = value;
        return;
    }
    // else go in left or right son/range
    int mid = (left + right) / 2;
    if (pos <= mid) update(2 * node, left, mid, pos, value);
    else update(2 * node + 1, mid + 1, right, pos, value);
    // then update the affected parents
    vec[node] = max(vec[2 * node], vec[2 * node + 1]);
}


int query(int node, int left, int right, int lo, int hi)
{
    /// Get maximum in a range by splitting it when it's needed.
    if (lo <= left && right <= hi) { // our range includes computed range
        return vec[node];
    }
    // compute 1 or 2 parts of it
    int maxRet = -1;
    int mid = (left + right) / 2;
    // go left and take what you need
    if (lo <= mid) maxRet = query(2 * node, left, mid, lo, hi);
    // go right too
    if (hi > mid) maxRet = max(maxRet, query(2 * node + 1, mid + 1, right, lo, hi));
    return maxRet;
}


int main()
{
    freopen("arbint.in", "r", stdin);
    freopen("arbint.out", "w", stdout);
    // read numbers and queries
    int len, quests;
    cin >> len >> quests;
    // allocate memory
    int exp = (int)log2(2 * len - 1) + 1;
    vec = new int[1 << exp];
    memset(vec, 0, (1 << exp) * sizeof(int));
    // init values
    for (int i = 1; i <= len; ++i) {
        int value;
        cin >> value;
        update(1, 1, len, i, value);
    }
    while (quests--) {
        int op, lo, hi;
        cin >> op >> lo >> hi;
        if (op) update(1, 1, len, lo, hi);
        else cout << query(1, 1, len, lo, hi) << '\n';
    }
    delete[] vec;
    fclose(stdin);
    fclose(stdout);
    return 0;
}
