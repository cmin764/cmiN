#include <iostream>
#include <fstream>
using namespace std;

int cifrak(long n, int k)
{
    int s = 0;
    while (n > 0) {
        if (n % 10 == k) {
            s++;
        }
        n /= 10;
    }
    return s;
}

int main()
{
    ifstream fin("numere.txt");
    long n;
    while (fin >> n) {
        if (cifrak(n, 0) == 3) {
            cout << n << " ";
        }
    }
    fin.close();
    cin.get();
    return 0;
}
