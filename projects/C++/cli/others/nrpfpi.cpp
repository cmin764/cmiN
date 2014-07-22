#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    long double x;
    long int pi;
    int i, f;
    i = 0; f = 0;
    cout << "x="; cin >> x;
    pi = floor(x);
    while(pi!=0)
    {
        i = i + 1;
        pi = pi / 10;
    }
    while((x - floor(x))!= 0)
    {
        f = f + 1;
        x = x * 10;
    }
    cout << "Partea intreaga a numarului are " << i << " cifre." << endl;
    cout << "Partea fractionara a numarului are " << f << " cifre." << endl;
    system("pause >NUL");
}
