#include <iostream>
#include <bitset>
#include <string>
using namespace std;


class TheLockDivTwo {

    static const int N = 10;
    bitset<1 << N> used;

    inline bool check(int from, int to)
    {
        // used[x] it's taking care of (from == to) case
        bool dif = false, bit;
        bitset<N> bitFrom(from), bitTo(to);
        for (int i = 0; i < N; ++i) {
            if (bitFrom[i] == bitTo[i]) continue;
            if (dif) {
                if (bitFrom[i] != bit) return false;
            } else {
                bit = bitFrom[i];
                dif = true;
            }
        }
        return true; // everything is fine
    }

    public:
    string password(int n, int k)
    {
        static const int nr = 1 << n;
        used.reset();
        string res(n, '0');
        int last = 0;
        while (--k > 0) {
            for (int i = 1; i < nr; ++i) {
                if (used[i] || !check(last, i)) continue;
                used[i] = 1;
                last = i;
                break;
            }
        }
        for (int j = 0; j < n; ++j) {
            res[n - j - 1] = 1 << j & last ? '1' : '0';
        }
        return res;
    }
};


int main()
{
    TheLockDivTwo problem;
    cout << problem.password(3, 1000);
    return 0;
}
