// bac 005
#include <iostream>
using namespace std;

int main()
{
    int l, c, i, j, m[11][11];
    cout << "Numarul de linii: ";
    cin >> l;
    cout << "Numarul de coloane: ";
    cin >> c;
    for (i = 1; i <= l; i++) {
        for (j = 1; j <= c; j++) {
            m[i][j] = (i > j ? i : j);
            cout << m[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
