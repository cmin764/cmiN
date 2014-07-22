#include <fstream>
using namespace std;

char nr[512];
int A[512];

void impart()
{
    int i, t = 0, B = 2;
    for (i = A[0]; i > 0; i--, t %= B)
        A[i] = (t = t * 10 + A[i]) / B;
    for (; A[0] > 1 && !A[A[0]]; A[0]--);
}

int process()
{
    int i = 0, op = 0;
    while (nr[++i] != '\0');
    A[0] = i - 1;
    if (A[0] == 1) {
        A[1] = nr[1] - 48;
    }
    for (i = 1; i <= A[0] / 2; i++) {
        A[i] = nr[A[0] - i + 1] - 48;
        A[A[0] - i + 1] = nr[i] - 48;
    }
    while (A[1] > 0 || A[0] > 1) {
        if (A[1] % 2 == 0) {
            impart();
        } else {
            A[1]--;
        }
        op++;
    }
    return op;
}

int main()
{
    int n;
    ifstream fin("doi.in");
    ofstream fout("doi.out");
    fin >> n;
    while (n-- > 0) {
        fin >> nr + 1;
        fout << process() << "\n";
    }
    fin.close();
    fout.close();
    return 0;
}
