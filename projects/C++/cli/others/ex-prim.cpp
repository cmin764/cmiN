#include <iostream> // <iostream.h>
using namespace std; // N/A

int main() // void
{
    int n,x,i;
    cout << "Introdu un numar: "; cin >> n;
    x=0;
    for(i=2; i<n/2; i++)
    {
        if(n%i==0)
        {
            x=1;
        }              
    }
    if(x==0)
    {
        cout << "Numarul " << n << " este prim.\n"; // "\n" - pt. o noua linie sau << endl
    }
    else
    {
        cout << "Numarul " << n << " NU este prim.\n";
    }
    system("PAUSE"); // <-- ... comenzi date din consola sistemului ...
}                    // sa ai timp sa vezi rezultatul afisat
