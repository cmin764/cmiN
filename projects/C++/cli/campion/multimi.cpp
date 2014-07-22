#include <fstream>
using namespace std;

int main()
{
    int n, a, b, x = 0, y = 30000;
    ifstream fin("multimi.in");
    fin >> n;
    while (n > 0)
    {
        fin >> a >> b;
        if (a > x)
        {
            x = a;
        }
        if (b < y)
        {
            y = b;
        }
        n--;
    }
    fin.close();
    ofstream fout("multimi.out");
    if (x > y)
    {
        fout << "multimea vida";
    }
    else
    {
        while (x <= y)
        {
            fout << x << " ";
            x++;
        }
    }
    fout.close();
    return 0;
}
