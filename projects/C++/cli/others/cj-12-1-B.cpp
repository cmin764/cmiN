#include <cstdio>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;


typedef pair<int, int> pii_t;


pii_t process(int sum)
{
    if (sum < 3) {
        switch (sum) {
            case 0: return make_pair(0, 0);
            case 1: return make_pair(1, 1);
            case 2: return make_pair(1, 2);
        }
    }
    int start = sum / 3;
    switch (sum % 3) {
        case 0: return make_pair(start, min(start + 1, 10));
        case 1: return make_pair(min(start + 1, 10), min(start + 1, 10));
        case 2: return make_pair(min(start + 1, 10), min(start + 2, 10));
    }
}


int solve()
{
    int nr, sp, lim, total = 0;
    scanf("%d %d %d", &nr, &sp, &lim);
    for (int i = 0; i < nr; ++i) {
        int sum;
        scanf("%d", &sum);
        pii_t tmp = process(sum);
        if (tmp.first >= lim) ++total;
        else if (tmp.second >= lim && sp) {
            ++total;
            --sp;
        }
    }
    return total;
}


int main()
{
    freopen("B-large.in", "r", stdin);
    freopen("B-large.out", "w", stdout);
    int tests;
    scanf("%d", &tests);
    for (int i = 1; i <= tests; ++i) {
        printf("Case #%d: %d\n", i, solve());
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
