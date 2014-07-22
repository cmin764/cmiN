#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;


typedef unsigned int ui_t;


int len;
ui_t* vec;


int last_zeros(int pos, int cnt)
{
    while (!(pos & 1 << cnt)) ++cnt;
    return cnt;
}


void update(int pos, ui_t value)
{
    int cnt = 0;
    while (pos <= len) {
        vec[pos] += value;
        cnt = last_zeros(pos, cnt);
        pos += 1 << cnt;
        ++cnt;
    }
}


ui_t query(int from, int to)
{
    if (from > 1) return query(1, to) - query(1, from - 1);
    ui_t sum = 0;
    int cnt = 0;
    while (to > 0) {
        sum += vec[to];
        cnt = last_zeros(to, cnt);
        to -= 1 << cnt;
        ++cnt;
    }
    return sum;
}


int main()
{
    freopen("aib.in", "r", stdin);
    freopen("aib.out", "w", stdout);
    int quests;
    cin >> len >> quests;
    vec = new ui_t[len + 1];
    memset(vec, 0, sizeof(ui_t) * (len + 1));
    for (int i = 1; i <= len; ++i) {
        ui_t value;
        cin >> value;
        update(i, value);
    }
    while (quests--) {
        int op;
        cin >> op;
        if (op == 0) {
            int pos;
            ui_t value;
            cin >> pos >> value;
            update(pos, value);
        } else if (op == 1) {
            int from, to;
            cin >> from >> to;
            cout << query(from, to) << '\n';
        } else {
            bool found = false;
            ui_t sum, rec = -1;
            cin >> sum;
            int from = 1, to = len, mid;
            while (from <= to) {
                mid = (from + to) / 2;
                rec = query(1, mid);
                if (sum > rec) from = mid + 1;
                else if (sum < rec) to = mid - 1;
                else {
                    found = true;
                    break;
                }
            }
            if (found) cout << mid;
            else cout << -1;
            cout << '\n';
        }
    }
    delete[] vec;
    fclose(stdin);
    fclose(stdout);
    return 0;
}
