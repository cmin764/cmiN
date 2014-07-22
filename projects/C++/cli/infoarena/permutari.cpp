#include <fstream>
#define nmax 16

using namespace std;
int n, result[nmax], uvec[nmax];
ofstream fout("permutari.out");

void perm(int len)
{
    if (len - 1 == n) {
        for (int i = 1; i <= n; i++) {
            fout << result[i] << " ";
        }
        fout << "\n";
    } else {
        for (int i = 1; i <= n; i++) {
            if (!uvec[i]) {
                result[len] = i;
                uvec[i] = 1;
                perm(len + 1);
                uvec[i] = 0;
            }
        }
    }
}

int main()
{
    ifstream fin("permutari.in");
    fin >> n;
    fin.close();
    perm(1);
    fout.close();
    return 0;
}
