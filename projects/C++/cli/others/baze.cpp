// Converter de numere din baze de la 2 la 10
// cmiN

#include <iostream>
using namespace std;

int putere(int b, int e)
{
    long int r;
    r = 1;
    if(e == 0)
    {
        return r;
    }
    for(int ii = 1; ii <= e; ii++)
    {
        r = r * b;
    }
    return r;
}

int main()
{
    int bi, bf, s, p, c;
    long int ni, nx, nf;
    cout << "Introdu numarul bazei in care se afla numarul (2-10): ";
    cin >> bi;
    cout << "Introdu numarul: ";
    cin >> ni;
    cout << "Introdu numarul bazei in care vrei sa fie afisat numarul (2-10): ";
    cin >> bf;
    s = 1;
    nx = 0;
    nf = 0;
    if (bi < 2 || bi > 10)
    {
        s = 0;
    }
    if (bf < 2 || bf > 10)
    {
        s = 0;
    }
    if (s == 0)
    {
        cout << "Baza trebuie sa fie un numar intre 2 si 10 inclusiv! \n";
        system("pause >NUL");
        main();
    }
    p = 0;
    while (ni != 0)
    {
        c = ni % 10;
        nx = nx + c * putere(bi, p);
        ni = ni / 10;
        p = p + 1;
    }
    p = 0;
    while (nx != 0)
    {
        c = nx % bf;
        nf = nf + c * putere(10, p);
        nx = nx / bf;
        p = p + 1;
    }
    cout << endl << nf << endl;
    system("pause >NUL");
}
