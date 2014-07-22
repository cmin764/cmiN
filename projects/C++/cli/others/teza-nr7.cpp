#include <iostream>
using namespace std;

int main()
{
    int a, b, s, i, x;
    cout << "a="; cin >> a;
    cout << "b="; cin >> b;
    for(i = a; i <= b; i++)
    {
        s = 0;
        x = i;
        while(x != 0)
        {
            s = s + x % 10;
            x = x / 10;
        }
        if(s < 10)
        {
            cout << i << " ";
        }
    }
    system("pause >NUL");
}
