#include <fstream>
#define nin "inv.in"
#define nout "inv.out"
using namespace std;

int main()
{
    fstream myfile;
    myfile.open(nin, ios::in);
    long n, i, j, sum = 0;
    myfile >> n;
    long s[n];
    for (i = 0; i < n; i++)
    {
        myfile >> s[i];
    }
    myfile.close();
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (s[i] > s[j])
            {
                sum++;
            }
        }
    }
    myfile.open(nout, ios::out);
    myfile << sum % 9917;
    myfile.close();
    return 0;
}
