// interschimbari in matrice
#include <iostream>
using namespace std;

int main()
{
    int l, c, i, j, m[100][100], ans, t, f;
    do {
        cout << "Numarul de linii (1-100): ";
        cin >> l;
    } while (l < 1 || l > 100);
    do {
        cout << "Numarul de coloane (1-100): ";
        cin >> c;
    } while (c < 1 || c > 100);
    cout << "Completati matricea...\n";
    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            cin >> m[i][j];
        }
        cout << "\n";
    }
    cout << "Interschimbati doua linii (1/0)? ";
    cin >> ans;
    if (ans) {
        do {
            cout << "Linia initiala (0-" << l - 1 << "): ";
            cin >> i;
        } while (i < 0 || i >= l);
        do {
            cout << "Linia finala (0-" << l - 1 << "): ";
            cin >> f;
        } while (f < 0 || f >= l);
        for (j = 0; j < c; j++) {
            t = m[i][j];
            m[i][j] = m[f][j];
            m[f][j] = t;
        }
    }
    cout << "Interschimbati doua coloane (1/0)? ";
    cin >> ans;
    if (ans) {
        do {
            cout << "Coloana initiala (0-" << c - 1 << "): ";
            cin >> j;
        } while (j < 0 || j >= c);
        do {
            cout << "Coloana finala (0-" << c - 1 << "): ";
            cin >> f;
        } while (f < 0 || f >= c);
        for (i = 0; i < l; i++) {
            t = m[i][j];
            m[i][j] = m[i][f];
            m[i][f] = t;
        }
    }
    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            cout << m[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
