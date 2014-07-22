/* Sa se gaseasca intr-un vector dat cu cel mult 100 elemente 
cea mai lunga secventa de elemente consecutive ca pozitie cu valori crescatoare. */
#include <iostream>
using namespace std;

int main()
{
    unsigned int n, i, j, min = 0, max = 0;
    cout << "Numarul de elemente al vectorului: ";
    cin >> n;
    long v[n];
    for (i = 0; i < n; i++)
    {
        cout << "Dati o valoare pentru elementul de pe pozitia " << i << ": ";
        cin >> v[i];
    }
    i = 0;
    while (i < n - 1)
    {
        for (j = i; j < n - 1; j++)
        {
            if (v[j + 1] <= v[j])
            {
                break;
            }
        }
        if ((max - min) < (j - i))
        {
            max = j;
            min = i;
        }
        i = j + 1;
    }
    cout << "Cea mai lunga secventa: \n";
    for (i = min; i <= max; i++)
    {
        cout << v[i] << " ";
    }
    system("pause >NUL");
    return 0;
}
