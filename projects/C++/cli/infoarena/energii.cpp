#include <fstream>
#define inf 0x6FffFFff
#define gmax 1024
#define emax 5120

using namespace std;
struct generator {
    int e, c;
} gen[gmax];
long sol[gmax][emax];

void preprocess(int g, int w)
{
    int i;
    for (i = 0; i <= w; i++) {
        sol[0][i] = inf;
    }
    for (i = 0; i <= g; i++) {
        sol[g][0] = inf;
    }
}

void solve(int g, int w)
{
    int i, j;
    for (i = 1; i <= g; i++) {
        for (j = 1; j <= w; j++) {
            sol[i][j] = sol[i - 1][j];
            if (gen[i].e >= j && gen[i].c < sol[i][j]) {
                sol[i][j] = gen[i].c;
            } else if (gen[i].e < j && gen[i].c + sol[i - 1][j - gen[i].e] < sol[i][j]) {
                sol[i][j] = gen[i].c + sol[i - 1][j - gen[i].e];
            }
        }
    }
}

int main()
{
    ifstream fin("energii.in");
    ofstream fout("energii.out");
    int g, w;
    fin >> g >> w;
    for (int i = 1; i <= g; i++) {
        fin >> gen[i].e >> gen[i].c;
    }
    preprocess(g, w);
    solve(g, w);
    if (sol[g][w] == inf) {
        fout << -1;
    } else {
        fout << sol[g][w];
    }
    fin.close();
    fout.close();
    return 0;
}
