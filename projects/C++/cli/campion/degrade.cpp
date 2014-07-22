#include <fstream>
using namespace std;

int main()
{
    char p[10], v[100001];
    unsigned long i, j, k = 0, len = 0, pos = 0, maxlen = 0, nr = 0;
    ifstream fin("degrade.in");
    for (i = 0; i < 10; i++)
    {
        fin >> p[i];
    }
    while (fin >> v[k])
    {
        k++;
    }
    fin.close();
    for (i = 0; i < k; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (v[i] == p[j])
            {
                if (j >= pos)
                {
                    pos = j;
                    len++;
                }
                else
                {
                    if (len > maxlen)
                    {
                        maxlen = len;
                    }
                    len = 0;
                    pos = 0;
                    i--;
                }
                break;
            }
        }
    }
    len = 0;
    pos = 0;
    for (i = 0; i < k; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (v[i] == p[j])
            {
                if (j >= pos)
                {
                    pos = j;
                    len++;
                }
                else
                {
                    if (len == maxlen)
                    {
                        nr++;
                    }
                    len = 0;
                    pos = 0;
                    i--;
                }
                break;
            }
        }
    }
    ofstream fout("degrade.out");
    fout << maxlen << " " << nr;
    fout.close();
    return 0;
}
