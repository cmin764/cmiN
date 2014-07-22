#include <iostream>
using namespace std;

int main()
{
    int n, i, j, x, k;
    cout << "Numarul de randuri si coloane: ";
    cin >> n;
    double v[n][n];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            cout << "Elementul de pe pozitia " << i << j << ": ";
            cin >> v[i][j];
        }
    }
    x = n / 2;
    if (n % 2 == 0)
    {
        x -= 1;
    }
    for (k = 0; k <= x; k++)
    {
        for (i = k; i < n - k; i++)
        {
            cout << v[k][i] << " ";
        }
        for (i = k + 1; i < n - k; i++)
        {
            cout << v[i][n - k - 1] << " ";
        }
        for (i = n - k - 2; i >= k; i--)
        {
            cout << v[n - k - 1][i] << " ";
        }
        for (i = n - k - 2; i >= k + 1; i--)
        {
            cout << v[i][k] << " ";
        }
    }
    system("pause >NUL");
    return 0;
}
