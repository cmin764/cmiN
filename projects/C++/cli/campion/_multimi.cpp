#include <fstream>
using namespace std;

void sorted(int v[], int k)
{
    int temp, i;
    bool flag;
    do
    {
        flag = false;
        for (i = 0; i < (k - 1); i++)
        {
            if (v[i] > v[i + 1])
            {
                temp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temp;
                flag = true;
            }
        }
    }
    while (flag);
}

int main()
{
    int n, x, y, i, j, k;
    bool flag;
    ifstream fin("multimi.in");
    fin >> n;
    fin >> x >> y;
    int v[x - y + 1];
    k = 0;
    for (i = x; i <= y; i++)
    {
        v[i - x] = i;
        k++;
    }
    n--;
    while (n > 0)
    {
        fin >> x >> y;
        for (i = 0; i < k; i++)
        {
            flag = true;
            for (j = x; j <= y; j++)
            {
                if (v[i] == j)
                {
                    flag = false;
                }
            }
            if (flag)
            {
                v[i] = v[k - 1];
                k--;
                i--;
            }
        }
        n--;
    }
    fin.close();
    sorted(v, k);
    ofstream fout("multimi.out");
    if (k == 0)
    {
        fout << "multimea vida";
    }
    else
    {
        for (i = 0; i < k; i++)
        {
            fout << v[i];
            if (i != (k - 1))
            {
                fout << " ";
            }
        }
    }
    fout.close();   
    return 0;
}
