#include <iostream>
using namespace std;

int main()
{
    int n, i, j, k, p;
    cout << "Numarul de linii si coloane: ";
    cin >> n;
    double v[n][n], r1[n][n], r2[n][n], s;
    cout << "Puterea: ";
    cin >> p;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            cout << "Elementul " << i << j << ": ";
            cin >> v[i][j];
            r1[i][j] = v[i][j];
        }
    }
    while (p-- > 1)
    {
        for (i = 0; i < n; i++)
        {
            for (k = 0; k < n; k++)
            {
                s = 0;
                for (j = 0; j < n; j++)
                {
                    s += r1[i][j] * v[j][k];
                }
                r2[i][k] = s;
            }
        }
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                r1[i][j] = r2[i][j];
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            cout << r1[i][j] << " ";
        }
        cout << "\n";
    }
    system("pause >nul");
    return 0;
}
