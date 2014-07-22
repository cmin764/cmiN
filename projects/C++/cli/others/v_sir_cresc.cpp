// Scrieti un program care construieste si afiseaza un tablou unidimensional care memoreaza un sir crescator de n*k termeni din multimea primelor n numere naturale nenule, fiecare numar fiind in sir de k ori.
#include <iostream>
using namespace std;

int main()
{
    int n, k, i, j, v[200];
    cout << "n="; cin >> n;
    cout << "k="; cin >> k;
    j = 0;
    while (n > 0)
    {
        for (i = 0; i < k; i++)
        {
            v[i + j] = n;
        }
        j += k;
        n--;
    }
    for (i = j - 1; i >= 0; i--)
    {
        cout << v[i] << " ";
    }
    return 0;
}
