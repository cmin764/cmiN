#include <iostream>
using namespace std;

int main()
{
    double v[100], x;
    int i, n, m;
    cout << "Numarul de elemente al vectorului: "; cin >> n;
    cout << "Introduceti elementele...\n";
    i = 0;
    cout << i << ": "; cin >> v[i];
    i++;
    while (i < n)
    {
        cout << i << ": "; cin >> v[i];
        if (v[i] >= v[i - 1])
        {
            cout << "Numarul NU este mai mic decat precedentul.\n";
        }
        else
        {
            i++;
        }
    }
    cout << "Numar cautat: "; cin >> x;
    i = 0;
    while (i < n)
    {
        m = (i + n) / 2;
        if (x == v[m])
        {
            break;
        }
        if (x < v[m])
        {
            i = m + 1;
        }
        else
        {
            n = m;
        }
    }
    if (i < n)
    {
        cout << "Numarul " << x << " a fost gasit pe pozitia " << m << ".\n";
    }
    else
    {
        cout << "Numarul " << x << " NU a fost gasit.\n";
    }
    return 0;
}
