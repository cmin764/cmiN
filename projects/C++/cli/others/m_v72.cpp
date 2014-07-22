// bac 072
#include <iostream>
using namespace std;

int main()
{
    int n, i, j, m[128][128], s = 1;
    cout << "Numar linii si coloane: ";
    cin >> n;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i; j++) {
            m[i][j] = s++;
        }
    }
    for (j = 0; j < n; j++) {
        s = m[n - 1 - j][j];
        for (i = n - j; i < n; i++) {
            m[i][j] = --s;
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            cout << m[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
