//#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    unsigned int F, B;
    unsigned int index;
    char f, b;
    f = 'f';
    b = 'b';
    ifstream fin("film.in");
    fin >> F >> B;
    fin.close();
    index = F + B;
    char sir[index];
    if (F == B)
    {
        for (unsigned int i = 0; i < F; i++)
        {
            sir[i * 2] = f;
            sir[i * 2 + 1] = b;
        }
    }
    else
    {
        unsigned int x;
        x = (F > B) ? F:B;
        if (B > F)
        {
            f = 'b';
            b = 'f';
        }
        sir[0] = f;
        sir[1] = b;
        for (unsigned int i = 2; i < index; i++)
        {
            if (sir[i - 1] == f && sir[i - 2] == f)
            {
                sir[i] = b;
            }
            else if (x - 1 > 0)
            {
                sir[i] = f;
                x--;
            }
            else
            {
                sir[i] = b;
            }
        }
    }
    ofstream fout("film.out");
    fout << sir;
    fout.close();
    //cout << sir << "\n";
    //system("PAUSE >NUL");
    return 0;
}
