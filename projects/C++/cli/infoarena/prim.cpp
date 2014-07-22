#include <fstream>
#include <cmath>

using namespace std;
unsigned long long numbers[100001];

void generate(unsigned long n)
{
    unsigned long long i, last, old, sqoi;
    unsigned long j, len = 0;
    bool flag;
    numbers[len++] = 2;
    while (true) {
        i = numbers[len - 1];
        last = (unsigned long long) pow((long double) i, 2);
        old = len;
        for (i++; i < last; i++) {
            if (len == n) {
                return;
            }
            sqoi = sqrt(i);
            for (j = 0, flag = true; flag && j < old && numbers[j] <= sqoi; j++) {
                if (!(i % numbers[j])) {
                    flag = false;
                }
            }
            if (flag) {
                numbers[len++] = i;
            }
        }
    }
}

int main()
{
    unsigned long n;
    unsigned long long res;
    ifstream fin("prim.in");
    ofstream fout("prim.out");
    fin >> n;
    generate(n + 1);
    res = (unsigned long long) pow((long double) numbers[n], 2);
    fout << res;
    fin.close();
    fout.close();
    return 0;
}
