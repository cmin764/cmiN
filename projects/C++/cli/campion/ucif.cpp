#include <fstream>
using namespace std;

int main()
{
    unsigned int n, s, i, j, x;
    ifstream fin("ucif.in");
    fin >> n;
    fin.close();
    s = 0;
    for (i = 1; i <= n; i++)
    {
        x = i % 10;
        for (j = 2; j <= i; j++)
        {
            x *= i % 10;
            x %= 10;
        }
        s += x;
    }
    ofstream fout("ucif.out");
    fout << s % 10;
    fout.close();
    return 0;
}
