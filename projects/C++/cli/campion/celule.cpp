#include <fstream>
using namespace std;

int main()
{
    unsigned int o = 0, k1 = 0, k2 = 0, j;
    unsigned long n, m, i, fpv1[32], fpv2[32];
    //fpv1 = new(nothrow) unsigned long;
    //fpv2 = new(nothrow) unsigned long;
    ifstream fin("celule.in");
    fin >> n >> m;
    fin.close();
    while (n != 1)
    {
        for (i = 2; i <= n; i++)
        {
            if (n % i == 0)
            {
                fpv1[k1++] = i;
                n /= i;
                break;
            }
        }
    }
    while (m != 1)
    {
        for (i = 2; i <= m; i++)
        {
            if (m % i == 0)
            {
                fpv2[k2++] = i;
                m /= i;
                break;
            }
        }
    }
    for (i = 0; i < k1; i++)
    {
        for (j = 0; j < k2; j++)
        {
            if (fpv1[i] == fpv2[j])
            {
                fpv1[i] = 0;
                fpv2[j] = 0;
                break;
            }
        }
    }
    for (i = 0; i < k1; i++)
    {
        if (fpv1[i] != 0)
        {
            o++;
        }
    }
    for (i = 0; i < k2; i++)
    {
        if (fpv2[i] != 0)
        {
            o++;
        }
    }
    ofstream fout("celule.out");
    fout << o;
    fout.close();
    return 0;
}
