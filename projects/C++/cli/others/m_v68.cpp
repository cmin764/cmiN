// bac 068
#include <iostream>
using namespace std;

int main()
{
    int l, c, i, j;
    unsigned long p = 1;
    long m[64][64];
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
    for (i = 2; i <= l; i += 2) {
        for (j = 1; j <= c; j += 2) {
            if (m[i][j] >= 0) {
                p *= m[i][j];
            }
        }
    }
    cout << p << "\n";
    return 0;
}
