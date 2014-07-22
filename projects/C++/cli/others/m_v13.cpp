// bac 013
#include <iostream>
using namespace std;

int main()
{
    int n, i, j, m[50][50];
    cout << "Numarul de linii si coloane: ";
    cin >> n;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i + j + 1 == n) {
                m[i][j] = 0;
            } else if (i + j + 1 < n) {
                m[i][j] = 1;
            } else {
                m[i][j] = 2;
            }
            cout << m[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
