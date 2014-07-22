// bac 063
#include <iostream>
using namespace std;

int main()
{
    int l, c, i, j, m[64][64];
    cout << "Numar linii: ";
    cin >> l;
    cout << "Numar coloane: ";
    cin >> c;
    for (j = 0; j < c; j++) {
        for (i = 0; i < l; i++) {
            m[i][j] = j * l + i + 1;
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
