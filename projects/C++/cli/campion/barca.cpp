#include <fstream>
using namespace std;

int main()
{
    unsigned int n, i = 1, mal = 1;
    char ion = 'I', geo = 'G';
    ifstream fin("barca.in");
    fin >> n;
    fin.close();
    ofstream fout("barca.out");
    fout << n * 4 << "\n";
    while (i <= n)
    {
        if (mal == 1)
        {
            fout << ion << geo << "\n";
            mal = 2;
        }
        else if (mal == 2)
        {
            fout << ion << "\n";
            mal = 0;
        }
        else
        {
            fout << i << "\n";
            i++;
            fout << geo << "\n";
            mal = 1;
        }
    }
    fout.close();
    return 0;
}
