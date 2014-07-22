#include <iostream>
using namespace std;

int main()
{
    int a[100], b[100], c[101], t, m, n, i, j, max;
    cout << "Cate cifre are a ?: "; cin >> m;
    cout << "Dar b ?: "; cin >> n;
    for (i = 0; i < n - m; i++)
    {
        a[i] = 0;
    }
    for (j = 0; j < m - n; j++)
    {
        b[j] = 0;
    }
    max = m > n ? m:n;
    cout << "Introdu cifrele lui a...\n";
    for (; i < max; i++)
    {
        cin >> a[i];
    }
    cout << "Introdu cifrele lui b...\n";
    for(; j < max; j++)
    {
        cin >> b[j];
    }
    j = t = 0;
    i--;
    while (i >= 0)
    {
        c[j] = (a[i] + b[i] + t) % 10;
        t = (a[i] + b[i] + t) / 10;
        i--;
        j++;
    }
    if (t)
    {
        c[j] = t;
        j++;
    }
    cout << "Suma: ";
    for (i = j - 1; i >= 0; i--)
    {
        cout << c[i];
    }
    cout << "\n";
    return 0;
}
