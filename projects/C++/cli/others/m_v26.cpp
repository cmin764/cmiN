// bac 026
#include <iostream>
using namespace std;

int main()
{
    int n, i, j, m[6][6], v[6], max;
    cout << "Numarul de linii si coloane: ";
    cin >> n;
    cout << "Completati matricea...\n";
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) { 
            cin >> m[i][j];
        }
        cout << "\n";
    }
    for (j = 0; j < n; j++) {
        v[j] = 1;
        max = 0;
        for (i = 0; i < n; i++) {
            v[j] *= m[i][j];
            if (m[i][j] > max) {
                max = m[i][j];
            }
        }
        if (v[j] / max == max) {
            cout << max << " ";
        }
    }
    return 0;
}
