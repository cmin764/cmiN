// bac 061
#include <iostream>
using namespace std;

int m[16][16];

int main()
{
    int n, i, j;
    cout << "Numar linii si coloane: ";
    cin >> n;
    for (i = 1; i <= n; i++) {
        m[n][i] = i;
    }
    for (i = n - 1; i > 0; i--) {
        for (j = 1; j <= n; j++) {
            if (!(j > i)) {
                m[i][j] = m[i + 1][j] + m[i + 1][j - 1] + m[i + 1][j + 1];
            }
        }
    }
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            cout << m[i][j] << " ";
        }
        cout << "\n";
    }
    system("pause >nul");
    return 0;
}
