#include <fstream>
using namespace std;

int main()
{
    unsigned int n, m, k, ab;
    ifstream fin("finala.in");
    fin >> n >> m >> k;
    fin.close();
    ab = (n + m) / k;
    if (ab * k != (n + m))
    {
        ab++;
    }
    ofstream fout("finala.out");
    if ((m / ab) < 2)
    {
        fout << 0;
    }
    else
    {
        fout << ab;
    }
    fout.close();
    return 0;
}
