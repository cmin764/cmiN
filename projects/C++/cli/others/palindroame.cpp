// Palindroame
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    int n, i, x, s;
    cout << "n="; cin >> n;
    ofstream fout("palindroame.txt");
    for(i = 0; i < n; i++)
    {
        x = i;
        s = 0;
        while(x > 0)
        {
            s = s * 10 + x % 10;
            x /= 10;
        }
        if(i == s)
        {
            cout << i << endl;
            fout << i << endl;
        }
    }
    fout.close();
    system("PAUSE >NUL");
}
