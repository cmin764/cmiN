#include <fstream>
using namespace std;

int main()
{
    unsigned int n, p, k, i;
    ifstream fin("pinochio.in");
    fin >> n >> p >> k;
    fin.close();
    n += (k / 7) * (5 * p - 2);
    for (i = 1; i <= k % 7; i++)
    {
        if (i == 6)
        {
            n -= 1;
        }
        else
        {
            n += p;
        }
    }
    ofstream fout("pinochio.out");
    fout << n;
    fout.close();
    return 0;
}
