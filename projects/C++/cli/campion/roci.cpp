#include <fstream>
using namespace std;

int main()
{
    unsigned long n, i, minp = 100001, op = 0;
    bool flag1 = true, flag2 = true;
    ifstream fin("roci.in");
    fin >> n;
    unsigned int v[n], minv;
    for (i = 0; i < n; i++)
    {
        fin >> v[i];
    }
    fin.close();
    while(flag1)
    {
        flag1 = false;
        minv = 10001;
        for (i = 0; i < n; i++)
        {
            if (v[i] != 0)
            {
                flag1 = true;
                flag2 = true;
                if (v[i] < minv)
                {
                    minv = v[i];
                    minp = i;
                }
            }
        }
        while (flag2)
        {
            flag2 = false;
            for (i = 0; i < n; i++)
            {
                if (v[i] == v[minp] + 1)
                {
                    v[minp] = 0;
                    minp = i;
                    flag2 = true;
                }
            }
        }
        v[minp] = 0;
        op++;
    }
    ofstream fout("roci.out");
    fout << op - 1;
    fout.close();
    return 0;
}
