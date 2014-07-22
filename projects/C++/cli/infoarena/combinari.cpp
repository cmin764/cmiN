#include <fstream>
#define nmax 32

using namespace std;
int n, k, result[nmax], uvec[nmax];
ofstream fout("combinari.out");

void comb(int len)
{
    if (len - 1 == k) {
        for (int i = 1; i <= k; i++) {
            fout << result[i] << " ";
        }
        fout << "\n";
    } else {
        for (int i = 1; i <= n; i++) {
            if (!uvec[i] && result[len - 1] < i) {
                result[len] = i;
                uvec[i] = 1;
                comb(len + 1);
                uvec[i] = 0;
            }
        }
    }
}

int main()
{
    ifstream fin("combinari.in");
    fin >> n >> k;
    fin.close();
    comb(1);
    fout.close();
    return 0;
}