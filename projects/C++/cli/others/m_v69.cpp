// bac 069
#include <iostream>
using namespace std;

int main()
{
    int l, c, i, j;
    long m[64][64];
    bool flag = true;
    cout << "Numar linii: ";
    cin >> l;
    cout << "Numar coloane: ";
    cin >> c;
    cout << "Completati matricea...\n";
    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            cin >> m[i][j];
            if (i > j) {
                if (m[i][j]) {
                    flag = false;
                }
            }
        }
        cout << "\n";
    }
    if (flag) {
        cout << "Este triunghiulară superior.\n";
    } else {
        cout << "Nu este triunghiulară superior.\n";
    }
    return 0;
}
