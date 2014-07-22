#include <iostream>
using namespace std;

char vnr[10];

void cifmin(long nr1, long & nr2)
{
    int i;
    while (nr1 > 0) {
        vnr[nr1 % 10]++;
        nr1 /= 10;
    }
    for (i = 1; i < 10; i++) {
        while (vnr[i]-- > 0) {
            nr2 = nr2 * 10 + i;
            while (vnr[0]-- > 0) {
                nr2 *= 10;
            }
        }
    }
}

int main()
{
    long nr1, nr2 = 0;
    cout << "Numar de maxim 8 cifre: ";
    cin >> nr1;
    cifmin(nr1, nr2);
    cout << nr2;
    system("pause >nul");
    return 0;
}
