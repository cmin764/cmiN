#include <iostream>
#include <fstream>
#define nmax 100000
using namespace std;

int main()
{
    long n, i, vec[nmax], poz, maxlen = 0, len = 1;
    ifstream fin("ssm.in");
    fin >> n;
    fin >> vec[0];
    for (i = 1; i < n; i++) {
        fin >> vec[i];
        if (vec[i] <= vec[i - 1]) {
            if (len > maxlen) {
                maxlen = len;
                poz = i;
                len = 1;
            }
        } else {
            len++;
        }
    }
    fin.close();
    ofstream fout("ssm.out");
    fout << maxlen << "\n";
    for (i = poz - maxlen; i < poz; i++) {
        fout << vec[i] << " ";
    }
    fout.close();
    return 0;
}
