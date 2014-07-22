// Suma maxima in vector
#include <iostream>
#define nmax 1000

using namespace std;
int vec[nmax];
unsigned long sol[nmax];

unsigned long process(int & n)
{
    int sum;
    unsigned long maxsum = 0;
    for (int i = n; i > 0; i--) {
        sum = 0;
        for (int j = i + 2; j <= n; j++) {
            if (sol[j] > sum) {
                sum = sol[j];
            }
        }
        sol[i] = sum + vec[i];
        if (sol[i] > maxsum) {
            maxsum = sol[i];
        }
    }
    return maxsum;
}

int main()
{
    int n;
    cout << "Numar: ";
    cin >> n;
    cout << "Numere...\n";
    for (int i = 1; i <= n; i++) {
        cin >> vec[i];
    }
    cout << "Suma maxima: " << process(n);
    system("pause >nul");
    return 0;
}
