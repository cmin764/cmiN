// Prime
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    int n, i, x, j;
    ofstream fout("prime.txt");
    cout << "n="; cin >> n;
    for(i = 0; i < n; i++)
    {
        x = 1;
        for(j = 2; j < i / 2; j++)
        {
            if(i % j == 0)
            {
                x = 0;
            }
        }
        if(x)
        {
            cout << i << endl;
            fout << i << endl;
        }
    }
    fout.close();
    system("PAUSE >NUL");
}
