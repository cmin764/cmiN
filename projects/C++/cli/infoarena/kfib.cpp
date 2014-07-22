#include <fstream>
#define mod 666013

using namespace std;
typedef unsigned long long ull_t;

void preprocess(ull_t mat[][2], ull_t result[][2])
{
    mat[0][0] = 0;
    mat[0][1] = 1;
    mat[1][0] = 1;
    mat[1][1] = 1;
    result[0][0] = 1;
    result[0][1] = 0;
    result[1][0] = 0;
    result[1][1] = 1;
}

void multiply(ull_t mat[][2], ull_t result[][2])
{
    ull_t tmp[2][2];
    int i, j, k;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            tmp[i][j] = 0;
            for (k = 0; k < 2; k++) {
                tmp[i][j] = (tmp[i][j] + mat[i][k] * result[k][j]) % mod;
            }
        }
    }
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            result[i][j] = tmp[i][j];
        }
    }
}

void process(ull_t mat[][2], ull_t result[][2], unsigned long & k)
{
    while (k > 0) {
        if (k % 2) {
            multiply(mat, result);
            k--;
        }
        multiply(mat, mat);
        k /= 2;
    }
}

int main()
{
    unsigned long k;
    ull_t mat[2][2], result[2][2];
    ifstream fin("kfib.in");
    ofstream fout("kfib.out");
    fin >> k;
    k++;
    preprocess(mat, result);
    process(mat, result, k);
    fout << result[0][0];
    fin.close();
    fout.close();
    return 0;
}
