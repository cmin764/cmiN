#include <fstream>

using namespace std;

int main()
{
    const long mod = 666013;
    unsigned long long nr, rez, x;
    ifstream fin("reducere.in");
    ofstream fout("reducere.out");
    fin >> nr >> rez;
    rez %= mod;
    while (nr-- > 1) {
        fin >> x;
        x %= mod;
        rez = (((rez * x) % mod) + rez + x) % mod;
    }
    fout << rez;
    fin.close();
    fout.close();
    return 0;
}
