// bac 011
#include <iostream>
using namespace std;

int main()
{
    int l, c, i, j, v[10], x;
    cout << "Numarul de linii: ";
    cin >> l;
    cout << "Numarul de coloane: ";
    cin >> c;
    cout << "Dati elementele matricei...\n";
    for (i = 0; i < l; i++) {
        v[i] = 9999;
        for (j = 0; j < c; j++) {
            cin >> x;
            if (x < v[i]) {
                v[i] = x;
            }
        }
        cout << "\n";
    }
    for (i = 0; i < l; i++) {
        cout << v[i] << " ";
    }
    return 0;
}
