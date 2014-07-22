#include <fstream>
#include <math.h>

using namespace std;

unsigned long lgpowmod(unsigned long a, unsigned long b, unsigned int c)
{
    if (b == 0) {
        return 1;
    } else {
        if (b % 2 == 0) {
            return (unsigned long) pow(lgpowmod(a, b / 2, c), 2) % c;
        } else {
            return ((a % c) * ((unsigned long) pow(lgpowmod(a, (b - 1) / 2, c), 2) % c)) % c;
        }
    }
}

int main()
{
    unsigned long a, b;
    unsigned int c;
    ifstream fin("modulo.in");
    ofstream fout("modulo.out");
    fin >> a >> b >> c;
    fout << lgpowmod(a, b, c);
    fin.close();
    fout.close();
    return 0;
}
