#include <fstream>

using namespace std;

int main()
{
    const unsigned long mod = 1999999973;
    unsigned long long a, b, p = 1;
    ifstream fin("lgput.in");
    ofstream fout("lgput.out");
    fin >> a >> b;
    while (b > 0) {
        if (b % 2 == 1) {
            p = p * a % mod;
        }
        a = a * a % mod;
        b /= 2;
    }
    fout << p;
    fin.close();
    fout.close();
    return 0;
}
