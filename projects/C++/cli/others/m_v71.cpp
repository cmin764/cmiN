// bac 071
#include <iostream>
using namespace std;

int main()
{
    int n, i, j, m[128][128];
    cout << "Numar linii si coloane: ";
    cin >> n;
    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
            m[i][j] = j * n + i + 1;
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
