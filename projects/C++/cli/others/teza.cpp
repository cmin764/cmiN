#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    int n, i, m;
    long int x;
    cout << "n="; cin >> n;
    for(i = 1; i <= n; i++)
    {
        cout << "x="; cin >> x;
        m = 9;
        while(x != 0)
        {
            if(x % 10 < m)
            {
                m = x % 10;
            }
            x = x / 10;
        }
        cout << "Cea mai mica cifra: " << m << endl;
    }
    system("pause >NUL");
}
