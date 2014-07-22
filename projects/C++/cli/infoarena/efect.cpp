#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;


const int MINE = -0x7fFFffFF, N = 1 << 16; // ('1'+'0'*16)(b2)
int efect[N], root[16], nr, bar, src;
bitset<16> bit, pic;


void init()
{
    /** Setez costurile implicite. */
    for (int i = 0; i < N; ++i) efect[i] = MINE;
    for (int i = 1, j = 0; j < nr; i <<= 1, ++j) efect[i] = root[j];
}


void set_efect(int len, int pos)
{
    /** Impartim configuratia in 2 complementare. */
    if (len) {
        for (; pos < bar; ++pos) {
            if (!bit.test(pos)) continue;
            pic.set(pos);
            set_efect(len - 1, pos + 1);
            pic.reset(pos);
        }
    } else {
        int first = pic.to_ulong(), second = src ^ first;
        int sum = (efect[first] - 2) * (efect[second] - 2) - 10;
        if (sum > efect[src]) efect[src] = sum;
    }
}


void config(int len, int pos)
{
    /** Generez toate configuratiile apoi le calculez efectul maxim. */
    if (len) {
        for (; pos <= nr - len; ++pos) {
            bit.set(pos);
            config(len - 1, pos + 1);
            bit.reset(pos);
        }
    } else {
        src = bit.to_ulong();
        bar = pos; // granita
        pos = bit.count();
        //cout << bar << " " << pos << endl;
        for (len = 1; len <= pos / 2; ++len) set_efect(len, 0);
    }
}


int main()
{
    /** E(m) = (E(m1)-2)*(E(m2)-2)-10 */
    ifstream fin("efect.in");
    ofstream fout("efect.out");
    fin >> nr;
    for (int i = 0; i < nr; ++i) fin >> root[i];
    init();
    //cout << efect[1] << " " << efect[2] << endl;
    for (int len = 2; len <= nr; ++len) config(len, 0);
    fout << efect[(1 << nr) - 1];
    fin.close();
    fout.close();
    return 0;
}
