#include <fstream>
#define nin "matrice3.in"
#define nout "matrice3.out"
using namespace std;

int main()
{
    fstream fin, fout;
    fin.open(nin, ios::in);
    fout.open(nout, ios::out);
    unsigned int n, m, i, j, max, side, maxside;
    unsigned long q;
    bool pflag, cflag;
    struct
    {
        unsigned int l;
        unsigned int c;
    } pos1, pos2, cpos;
    fin >> n >> m >> q;
    char matrix[n + 1][m + 1], c;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
        {
            do
            {
                c = fin.get();
            }
            while (isspace(c));
            matrix[i][j] = c;
        }
    }
    while (q-- > 0)
    {
        fin >> pos1.l >> pos1.c >> pos2.l >> pos2.c;
        max = (((pos2.l - pos1.l) < (pos2.c - pos1.c)) ? (pos2.l - pos1.l) : (pos2.c - pos1.c)) + 1;
        maxside = 0;
        for (side = 1; side <= max; side++)
        {
            pflag = false;
            for (cpos.l = pos1.l; cpos.l <= pos2.l - side + 1; cpos.l++)
            {
                for (cpos.c = pos1.c; cpos.c <= pos2.c - side + 1; cpos.c++)
                {
                    cflag = true;
                    for (i = cpos.l; i < cpos.l + side; i++)
                    {
                        for (j = cpos.c; j < cpos.c + side; j++)
                        {
                            if (matrix[i][j] != '0')
                            {
                                cflag = false;
                            }
                        }
                    }
                    if (cflag)
                    {
                        pflag = true;
                        maxside = side;
                        break;
                    }
                }
                if (pflag)
                {
                    break;
                }
            }
            if (!pflag)
            {
                break;
            }
        }
        fout << maxside << "\n";
    }
    fin.close();
    fout.close();
    return 0;
}
