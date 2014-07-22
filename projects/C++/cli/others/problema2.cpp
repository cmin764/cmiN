//  Se da un numar cu maxim 9 cifre, sa se afiseze numarul cel mai mare
// creat numai din cifrele acestuia.

#include <iostream>
using namespace std;

int putere(int b, int e)
{
    long int r;
    r=1;
    if(e==0)
    {
        return r;
    }
    for(int ii=1; ii<=e; ii++)
    {
        r=r*b;
    }
    return r;
}

int main()
{
    unsigned long int n,m,x;
    int c,i,ii;
    cout << "Introdu un numar: "; cin >> n;
    m=n;
    c=0;
    x=0;
    while(m>0)
    {
        c=c+1;
        m=m/10;
    }
    for(i=9; i>=0; i--)
    {
        m=n;
        while(m>0)
        {
             if(i==m%10)
             {
                 x=x+i*putere(10, c-1);
                 c=c-1;
             }
             m=m/10;
        }
    }
    cout << x << "\n";
    system("PAUSE");
}
