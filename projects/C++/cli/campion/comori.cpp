#include <fstream>
using namespace std;

int main()
{
    unsigned int N, d, p;
    long x = 0, y = 0;
    ifstream fin("comori.in");
    fin >> N;
    while (N > 0)
    {
        fin >> d >> p;
        switch (d)
        {
            case 1:
                y += p;
                break;
            case 2:
                x += p;
                y += p;
                break;
            case 3:
                x += p;
                break;
            case 4:
                x += p;
                y -= p;
                break;
            case 5:
                y -= p;
                break;
            case 6:
                x -= p;
                y -= p;
                break;
            case 7:
                x -= p;
                break;
            case 8:
                x -= p;
                y += p;
                break;
        }
        N--;
    }
    fin.close();
    ofstream fout("comori.out");
    fout << x << " " << y;
    fout.close();
    return 0;
}
