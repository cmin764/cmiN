// Se da un vector cu n numere naturale, sa se ordoneze crescator cea mai lunga secventa de numere impare din vector.
#include <iostream>
using namespace std;

int main()
{
    unsigned long v[100];
    int n, i, j, k, tmp, maxlen = 0, maxpos = 0;
    bool flag;
    cout << "Cate elemente are vectorul ?: "; cin >> n;
    cout << "Acum introduceti numerele...\n";
    for (i = 0; i < n; i++)
    {
        cout << " "; cin >> v[i];
    }
    for (i = 0; i < n - 1; i++)
    {
        if (v[i] % 2 == 1)
        {
            for (j = i + 1; j < n; j++)
            {
                if (v[j] % 2 == 0)
                {
                    break;
                }
            }
            if (j - i > maxlen)
            {
                maxlen = j - i;
                maxpos = i;
            }
            i = j;
        }
    }
    if (maxlen)
    {
        j = 0;
        for (i = maxpos; i < maxpos + maxlen; i++)
        {
            v[j++] = v[i];
        }
        k = 0;
        flag = true;
        while (flag)
        {
            flag = false;
            k++;
            for (i = 0; i < j - k; i++)
            {
                if (v[i] > v[i + 1])
                {
                    tmp = v[i];
                    v[i] = v[i + 1];
                    v[i + 1] = tmp;
                    flag = true;
                }
            }
        }
        for (i = 0; i < j; i++)
        {
            cout << v[i] << " ";
        }
    }
    return 0;
}
