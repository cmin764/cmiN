// stergere linie/coloana matrice
#include <iostream>
using namespace std;

int main()
{
    int l, c, i, j, m[100][100], ans, ld = 0, cd = 0;
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
    cout << "Doriti a elimina vreo linie (1/0)? ";
    cin >> ans;
    if (ans) {
        do {
            cout << "Linia (0-" << l - 1 << "): ";
            cin >> i;
        } while (i < 0 || i >= l);
        for (; i < l - 1; i++) {
            for (j = 0; j < c; j++) {
                m[i][j] = m[i + 1][j];
            }
        }
        ld = 1;
    }
    cout << "Doriti a elimina vreo coloana (1/0)? ";
    cin >> ans;
    if (ans) {
        do {
            cout << "Coloana (0-" << c - 1 << "): ";
            cin >> j;
        } while (j < 0 || j >= c);
        for (; j < c - 1; j++) {
            for (i = 0; i < l; i++) {
                m[i][j] = m[i][j + 1];
            }
        }
        cd = 1;
    }
    for (i = 0; i < l - ld; i++) {
        for (j = 0; j < c - cd; j++) {
            cout << m[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
