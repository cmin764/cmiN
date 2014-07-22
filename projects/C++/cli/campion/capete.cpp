#include <fstream>
using namespace std;

int main()
{
    unsigned int n, k, i;
    ifstream fin("capete.in");
    fin >> n;
    fin.close();
    k = 0;
    for (i = 1; i <= n; i++)
    {
        k += 6;
        k -= 1;   
    }
    ofstream fout("capete.out");
    fout << k;
    fout.close();
    return 0;
}
