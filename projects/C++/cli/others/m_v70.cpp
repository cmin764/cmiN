// bac 070
#include <iostream>
using namespace std;

int main()
{
    int l, c, i, j, x;
    long m[128][128];
    cout << "Numar linii: ";
    cin >> l;
    cout << "Numar coloane: ";
    cin >> c;
    cout << "Completati matricea...\n";
    for (i = 1; i <= l; i++) {
        for (j = 1; j <= c; j++) {
            cin >> m[i][j];
        }
        cout << "\n";
    }
    cout << "Linia de sters: ";
    cin >> x;
    for (i = x; i < l; i++) {
        for (j = 1; j <= c; j++) {
            m[i][j] = m[i + 1][j];
        }
    }
    for (i = 1; i < l; i++) {
        for (j = 1; j <= c; j++) {
            cout << m[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
