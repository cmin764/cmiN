#include <fstream>
using namespace std;
/* s0z ma bate am incercat si nu-mi vedea %l64d, iar cu 1LL ala nu m-am prins */

int main()
{
    ifstream fin("sir.in");
    ofstream fout("sir.out");
    int T;
    unsigned long long x, y, a, b, c, s, f, tmp, i, sum, mod = 101587009;
    fin >> T;
    while (T-- > 0) {
        sum = 0;
        i = 2;
        fin >> x >> y >> a >> b >> c >> s >> f;
        if (s == 0) {
            sum = (x + y) % mod;
        } else if (s == 1) {
            sum = y % mod;
        }
        while (i < s) {
            tmp = ((a * y % mod) + (b * x % mod) + c) % mod;
            x = y;
            y = tmp;
            i++;
        }
        while (i <= f) {
            tmp = ((a * y % mod) + (b * x % mod) + c) % mod;
            sum = (sum + tmp) % mod;
            x = y;
            y = tmp;
            i++;
        }
        fout << sum << endl;
    }
    fin.close();
    fout.close();
    return 0;
}
