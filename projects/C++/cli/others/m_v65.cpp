// bac 065
#include <iostream>
using namespace std;

int main()
{
    int l, c, i, j, m[64][64];
    cout << "Numar linii: ";
    cin >> l;
    cout << "Numar coloane: ";
    cin >> c;
    for (i = 0; i < l; i++) {
        if (i % 2 == 0) {
            for (j = 0; j < c; j++) {
                m[i][j] = i * c + j + 1;
            }
        } else {
            for (j = 0; j < c; j++) {
                m[i][j] = (i + 1) * c - j;
            }
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
