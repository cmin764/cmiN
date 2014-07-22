//  Sa se afiseze toate numerle prime formate din cifre impare 
// din intervalul [a,b]

#include <iostream>
using namespace std;

int main()
{
    int a,b,i,ii,x,y,z,m;
    cout << "[a,b] introdu a si b: \n";
    cout << "a=";
    cin >> a;
    cout << "b=";
    cin >> b;
    for(i=a; i<=b; i=i+1)
    {
        x=0;
        for(ii=2; ii<=(i/2); ii=ii+1)
        {
            if(i%ii==0)
            {
                x=1;
            }                     
        }
        if(x==0)
        {
            y=0;
            m=i;
            while(m>0)
            {
                z=m%10;
                m=m/10;
                if(z%2==0)
                {
                    y=1;
                }
            }
            if(y==0)
            {
                cout << i << "\n";
            }         
        }
    }
    system("PAUSE");               
}
