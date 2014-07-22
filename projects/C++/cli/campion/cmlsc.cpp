#include <fstream>
#define len 1024
using namespace std;

int v1[len], v2[len], vc[len], lcs[len + 1][len + 1], m, n;

void solvestr()
{
    int i, j;
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            if (v1[i] == v2[j]) {
                lcs[i][j] = 1 + lcs[i - 1][j - 1];
            } else {
                lcs[i][j] = (lcs[i - 1][j] > lcs[i][j - 1] ? lcs[i - 1][j] : lcs[i][j - 1]);
            }
        }
    }
}

void writestr(int i, int j)
{
    if (lcs[i][j]) {
        if (v1[i] == v2[j]) {
            vc[lcs[i][j]] = v1[i];
            writestr(i - 1, j - 1);
        } else {
            if (lcs[i][j] == lcs[i - 1][j]) {
                writestr(i - 1, j);
            } else {
                writestr(i, j - 1);
            }
        }
    }
}

int main()
{
    int i;
    ifstream fin("cmlsc.in");
    ofstream fout("cmlsc.out");
    fin >> m >> n;
    for (i = 1; i <= m; i++) {
        fin >> v1[i];
    }
    for (i = 1; i <= n; i++) {
        fin >> v2[i];
    }
    fin.close();
    solvestr();
    writestr(m, n);
    fout << lcs[m][n] << "\n";
    for (i = 1; i <= lcs[m][n]; i++) {
        fout << vc[i] << " ";
    }
    fout.close();
    return 0;
}
