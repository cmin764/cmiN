// bac 003
#include <iostream>
using namespace std;

int main()
{
    int n, t, i, j, m[24][24];
    cout << "Dati numarul de linii si coloane: ";
    cin >> n;
    t = n;
    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
            if (i == j) {
                m[i][j] = 0;
            } else {
                m[i][j] = t;
            }
            cout << m[i][j] << " ";
        }
        t--;
        cout << "\n";
    }
    return 0;
}
