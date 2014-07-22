// Suma maxima in triunghi
#include <iostream>

using namespace std;
int tgl[10][10], sol[10][10];

int maxim(int a, int b)
{
    return a > b ? a : b;
}

void process(int n)
{
    int i, j;
    for (j = 0; j < n; j++) {
        sol[n - 1][j] = tgl[n - 1][j];
    }
    for (i = n - 2; i >= 0; i--) {
        for (j = 0; j <= i; j++) {
            sol[i][j] = tgl[i][j] + maxim(sol[i + 1][j], sol[i + 1][j + 1]);
        }
    }
}

int main()
{
    int n, i, j;
    cout << "Linii triunghi: ";
    cin >> n;
    cout << "Elemente...\n";
    for (i = 0; i < n; i++) {
        for (j = 0; j <= i; j++) {
            cin >> tgl[i][j];
        }
        cout << "\n";
    }
    process(n);
    cout << "Suma maxima: " << sol[0][0];
    system("pause >nul");
    return 0;
}
