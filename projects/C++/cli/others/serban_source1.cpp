#include <iostream>
using namespace std;

int main()
{
    int n, s, u;
    cin >> n;
    u = n % 10;
    s = n / 100;
    if (s==u)
    {
        cout << "Numarul este parindrom.";   
    }
    else
    {
        cout << "Numarul nu este parindrom.";
    }
    system("pause >NUL");
}
