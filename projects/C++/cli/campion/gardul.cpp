#include <fstream>
using namespace std;

int main()
{
    unsigned long n, p, q, i, rc = 0, ac = 0, vc = 0;
    ifstream fin("gardul.in");
    fin >> n >> p >> q;
    fin.close();
    char v[n + 1];
    for (i = p; i <= n; i += p)
    {
        v[i] = 'R';
        rc++;
    }
    for (i = q; i <= n; i += q)
    {
        if (v[i] == 'R')
        {
            rc--;
            vc++;
        }
        else
        {
            ac++;
        }
    }
    ofstream fout("gardul.out");
    fout << n - (rc + ac + vc) << "\n";
    fout << rc << "\n";
    fout << ac << "\n";
    fout << vc << "\n";
    fout.close();
    return 0;
}
