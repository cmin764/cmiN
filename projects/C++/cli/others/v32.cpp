#include <iostream>
using namespace std;

int main()
{
    int a, b, c;
    cout << "a= "; cin >> a;
    cout << "b= "; cin >> b;
    if (a > b)
    {
        c = b;
        b = a;
        a = c;
    }
    while(a <= b)
    {
        cout << a << " ";
        a = a * 2;
    }
    cout << a;
    system("pause >NUL");
}
