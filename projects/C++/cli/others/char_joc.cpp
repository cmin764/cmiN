#include <iostream>
using namespace std;

int main()
{
    int t, y, z, status;
    char x;
    cout << "Introdu un caracter: "; cin >> x;
    y = x;
    status = 1;
    t = 0;
    cout << " Introdu un numar [0-255] pentru a ghici valoarea numerica a lui " << x << endl;
    cout << "sau introdu -1 pentru terminarea jocului." << endl;
    while(status)
    {
        t += 1;
        cin >> z;
        if(z == y)
        {
            cout << "Felicitari! Ai gasit codul ASCII al lui " << x << " din " << t << " incercari." << endl;
            status = 0;
        } 
        else if(z == -1)
        {
            cout << "Codul ASCII pentru " << x << " este " << y << "." << endl;
            status = 0;
        } 
        else 
        {
            if(z > y)
            {
                cout << "Gresit! Valoarea e mai mare." << endl;
            }
            else
            {
                cout << "Gresit! Valoarea e mai mica." << endl;
            }
        }
    }
    system("pause >NUL");
}
