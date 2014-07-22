// bac 020
#include <iostream>
using namespace std;

int main()
{
    unsigned int n, i, j, m[10][10];
    cout << "Numarul de linii si coloane: ";
    cin >> n;
    for (i = 1, j = 1; i <= n || j <= n; i++, j++) {
        m[i][1] = i + 1;
        m[1][j] = j + 1;
    }
    for (i = 2; i <= n; i++) {
        for (j = 2; j <= n; j++) {
            m[i][j] = m[i - 1][j] + m[i][j - 1];
        }
    }
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            cout << m[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
