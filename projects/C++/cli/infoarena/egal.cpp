#include <fstream>
using namespace std;

int main()
{
    unsigned long n, i, j, min = 1000000000, max = 0;
    fstream myfile;
    myfile.open("egal.in", ios::in);
    myfile >> n;
    unsigned long v[n], start = 0, len = 0, nr = 0;
    for (i = 0; i < n; i++)
    {
        myfile >> v[i];
        if (v[i] > max)
        {
            max = v[i];
        }
        if (v[i] < min)
        {
            min = v[i];
        }
    }
    myfile.close();
    while (v[n - 1] < max)
    {
        for (i = 0; i < n; i++)
        {
            if (v[i] == min)
            {
                len = 1;
                for (j = i + 1; j < n; j++)
                {
                    if (v[j] == min)
                    {
                        len++;
                    }
                    else
                    {
                        break;
                    }
                }
                for (j = i; j < i + len; j++)
                {
                    v[j]++;
                }
                nr++;
                i += len;
            }
        }
        min++;
    }
    myfile.open("egal.out", ios::out);
    myfile << nr;
    myfile.close();
    return 0;
}
