#include <fstream>
using namespace std;

unsigned long int factorial(unsigned long int x)
{
    if (x > 1)
    {
        return (x * factorial(x - 1));
    }
    else
    {
        return 1;
    }
}

int main()
{
    unsigned long int n, k, result;
    ifstream fin("kbiti.in");
    fin >> n >> k;
    fin.close();
    n = (n / 2) - k;
    result = factorial(n + k) / (factorial(n) * factorial(k));
    ofstream fout("kbiti.out");
    fout << result;
    fout.close();
    return 0;
}
