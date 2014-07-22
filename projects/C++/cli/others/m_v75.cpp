// bac 075
#include <iostream>
using namespace std;

int main()
{
    int l, c, i, j, m[64][64], e;
    cout << "Numar linii: ";
    cin >> l;
    cout << "Numar coloane: ";
    cin >> c;
    for (i = 0; i < l; i++) {
        if (i % 4 == 0 || i % 4 == 1) {
            e = 0;
        } else {
            e = 1;
        }
        for (j = 0; j < c; j++) {
            m[i][j] = e;
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
