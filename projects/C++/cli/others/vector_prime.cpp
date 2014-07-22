#include <iostream>
using namespace std;

int main()
{
    unsigned int n, i, j;
    bool status;
    cout << "Cate numere doriti a introduce?: ";
    cin >> n;
    long v[n], temp, c = 0;
    for (i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    for (i = 0; i < n; i++)
    {
        status = true;
        for (j = 2; j <= v[i] / 2; j++)
        {
            if (v[i] % j == 0)
            {
                status = false;
            }
        }
        if (status)
        {
            v[i] = 0;
        }
    }
    for (i = 0; i < n; i++)
    {
        if (v[i] == 0)
        {
            c++;
            for (j = 0; j < i; j++)
            {
                if (v[j] != 0)
                {
                    temp = v[j];
                    v[j] = v[i];
                    v[i] = temp;
                }
            }
        }
    }
    cout << "Numerele care nu sunt prime: ";
    for (i = c; i < n; i++)
    {
        cout << v[i] << " ";
    }
    system("pause >NUL");
    return 0;
}
