// bac 074
#include <iostream>
using namespace std;

int main()
{
    int n, i, j, m[128][128], t;
    cout << "Numar linii si coloane: ";
    cin >> n;
    for (i = 1; i <= n; i++) {
        if (i % 2 == 1) {
            for (j = 1; j <= n; j++) {
                m[i][j] = j;
            }
        } else {
            t = n;
            for (j = 1; j <= n; j++) {
                m[i][j] = t--;
            }
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
