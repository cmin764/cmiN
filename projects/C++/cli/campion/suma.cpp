#include <fstream>
using namespace std;

int main()
{
    unsigned int n, m, i;
    ifstream fin("suma.in");
    fin >> n;
    fin.close();
    unsigned int v[n];
    for (i = 0; i < n; i++)
    {
        v[i] = 0;
    }
    ofstream fout("suma.out");
    m = n;
    v[0] = 1;
    m--;
    for (i = n - 1; i > 0; i--)
    {
        if (m < 10)
        {
            v[i] = m;
            break;
        }
        else
        {
            v[i] = 9;
            m -= 9;
        }
    }
    for (i = 0; i < n; i++)
    {
        fout << v[i];
    }
    fout << "\n";
    for (i = 0; i < n; i++)
    {
        v[i] = 0;
    }
    m = n;
    for (i = 0; i < n; i++)
    {
        if (m < 10)
        {
            v[i] = m;
            break;
        }
        else
        {
            v[i] = 9;
            m -= 9;
        }
    }
    for (i = 0; i < n; i++)
    {
        fout << v[i];
    }
    fout.close();
    return 0;
}
