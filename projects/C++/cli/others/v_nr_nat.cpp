#include <iostream>
#include <fstream>
using namespace std;

unsigned int v[10], x;

int main()
{
    ifstream fin("nr.txt");
    int c;
    while (fin >> x)
    {
        while (x > 0)
        {
            c = x % 10;
            x /= 10;
            v[c] = 1;
        }
    }
    fin.close();
    for (c = 0; c < 10; c++)
    {
        if (v[c])
        {
            cout << c << " ";
        }
    }
    cout << "\n";
    for (c = 9; c >= 0; c--)
    {
        if (!v[c])
        {
            cout << c << " ";
        }
    }
    cout << "\n";
    return 0;
}
