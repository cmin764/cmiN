#include <fstream>
#define nd 4
#define nmax 177
using namespace std;

struct punct_t
{
    unsigned int l;
    unsigned int c;
};

int dl[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
char alee[nmax][nmax];

void lee(punct_t, unsigned int matrix[nmax][nmax]);

int main()
{
    unsigned int n, m, i, j, calee[nmax][nmax];
    punct_t p1, p2;
    fstream myfile;
    myfile.open("alee.in", ios::in);
    myfile >> n >> m;
    for (i = 0; i <= n + 1; i++)
    {
        alee[0][i] = alee[n + 1][i] = 'x';
        alee[i][0] = alee[i][n + 1] = 'x';
    }
    while (m--)
    {
        myfile >> i >> j;
        alee[i][j] = 'x';
    }
    myfile >> p1.l >> p1.c;
    myfile >> p2.l >> p2.c;
    myfile.close();
    lee(p1, calee);
    myfile.open("alee.out", ios::out);
    myfile << calee[p2.l][p2.c];
    myfile.close();
    return 0;
}

void lee(punct_t p, unsigned int matrix[nmax][nmax])
{
    unsigned int i, ic = 0, sf = 0;
    punct_t coada[nmax * nmax];
    coada[0] = p;
    matrix[p.l][p.c] = 1;
    while (ic <= sf)
    {
        p = coada[ic++];
        for (i = 0; i < nd; i++)
        {
            if ((alee[p.l + dl[i]][p.c + dc[i]] == 0) && (matrix[p.l + dl[i]][p.c + dc[i]] == 0))
            {
                matrix[p.l + dl[i]][p.c + dc[i]] = matrix[p.l][p.c] + 1;
                sf++;
                coada[sf].l = p.l + dl[i];
                coada[sf].c = p.c + dc[i];
            }
        }
    }
}
