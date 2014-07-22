#include <fstream>
#define fin "nrdivunique.in"
#define fout "nrdivunique.out"
using namespace std;

int main()
{
    unsigned int n;
    unsigned long a, b, d, i, j;
    fstream myfile1, myfile2;
    myfile1.open(fin, ios::in);
    myfile2.open(fout, ios::out);
    myfile1 >> n;
    while (n > 0)
    {
        myfile1 >> a >> b;
        d = b - a + 1 + 1;
        for (i = 2; i < a; i++)
        {
            for (j = a; j <= b; j++)
            {
                if (j % i == 0)
                {
                    d++;
                    break;
                }
            }
        }
        myfile2 << d << "\n";
        n--;
    }
    myfile1.close();
    myfile2.close();
    return 0;
}
