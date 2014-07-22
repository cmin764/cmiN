// bac 010
#include <iostream>
using namespace std;

int main()
{
    unsigned long m[20][20];
    int l, c, i, j, p = 0;
    cout << "Numarul de lnii: ";
    cin >> l;
    cout << "Numarul de coloane: ";
    cin >> c;
    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            m[i][j] = p * p;
            p += 2;
            cout << m[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
