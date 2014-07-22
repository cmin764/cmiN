#include <fstream>
using namespace std;

void vsort(unsigned int v2[][2], unsigned int l)
{
    unsigned int i, temp[2];
    bool flag = true;
    while (flag)
    {
        flag = false;
        for (i = 0; i < l - 1; i++)
        {
            if (v2[i][0] * v2[i + 1][1] < v2[i][1] * v2[i + 1][0])
            {
                flag = true;
                temp[0] = v2[i][0];
                temp[1] = v2[i][1];
                v2[i][0] = v2[i + 1][0];
                v2[i][1] = v2[i + 1][1];
                v2[i + 1][0] = temp[0];
                v2[i + 1][1] = temp[1];
            }
        }
    }
}

int main()
{
    unsigned int n, m;
    ifstream fin("fractii.in");
    fin >> n;
    fin.close();
    unsigned int v[n], i, j, k = 1, l = 0, fp1[11], fp2[11], x, y, p, v2[n][2];
    for (i = 0; i < n - 1; i += 2)
    {
        v[i] = n - k;
        v[i + 1] = n + k;
        k++;
    }
    if (i == n - 1)
    {
        v[i] = n;
    }
    for (i = 0; i < n; i++)
    {
        x = 0;
        y = 0;
        while (v[i] != 1)
        {
            for (j = 2; j <= v[i]; j++)
            {
                if (v[i] % j == 0)
                {
                    v[i] /= j;
                    fp1[x++] = j;
                    break;
                }
            }
        }
        m = n;
        while (m != 1)
        {
            for (j = 2; j <= m; j++)
            {
                if (m % j == 0)
                {
                    m /= j;
                    fp2[y++] = j;
                    break;
                }
            }
        }
        for (j = 0; j < x; j++)
        {
            for (k = 0; k < y; k++)
            {
                if (fp1[j] == fp2[k])
                {
                    fp1[j] = 1;
                    fp2[k] = 1;
                    break;
                }
            }
        }
        p = 1;
        for (j = 0; j < x; j++)
        {
            p *= fp1[j];
        }
        v2[l][0] = p;
        p = 1;
        for (j = 0; j < y; j++)
        {
            p *= fp2[j];
        }
        v2[l][1] = p;
        l++;
    }
    vsort(v2, l);
    ofstream fout("fractii.out");
    for (i = 0; i < l; i++)
    {
        fout << v2[i][0] << " " << v2[i][1] << "\n";
    }
    fout.close();
    return 0;
}
