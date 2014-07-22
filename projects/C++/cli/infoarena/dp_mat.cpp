// Suma maxima in matrice pornind din stanga sus
#include <iostream>

using namespace std;
unsigned int matrix[10][10], sol[10][10];

unsigned int maxim(unsigned int a, unsigned int b)
{
    return a > b ? a : b;
}

void process(int l, int c)
{
    for (int i = 1; i <= l; i++) {
        for (int j = 1; j <= c; j++) {
            sol[i][j] = maxim(sol[i - 1][j], sol[i][j - 1]) + matrix[i][j];
        }
    }
}

int main()
{
    int l, c;
    cout << "Linii: ";
    cin >> l;
    cout << "Coloane: ";
    cin >> c;
    cout << "Elemente...\n";
    for (int i = 1; i <= l; i++) {
        for (int j = 1; j <= c; j++) {
            cin >> matrix[i][j];
        }
        cout << "\n";
    }
    process(l, c);
    cout << "Suma maxima: " << sol[l][c];
    system("pause >nul");
    return 0;
}
