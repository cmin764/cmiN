#include <iostream>
#include <fstream>
#define fin "nr.txt"
#define fout "ordonate.txt"

using namespace std;

int main()
{
    fstream myfile;
    unsigned int n, i, j;
    double v[100], tmp;
    bool flag;
    myfile.open(fin, ios::in);
    myfile >> n;
    for (i = 0; i < n; i++)
    {
        myfile >> v[i];
    }
    myfile.close();
    flag = true;
    j = 0;
    while (flag)
    {
        flag = false;
        j++;
        for (i = 0; i < n - j; i++)
        {
            if (v[i] < v[i + 1])
            {
                tmp = v[i];
                v[i] = v[i + 1];
                v[i + 1] = tmp;
                flag = true;
            }
        }
    }
    myfile.open(fout, ios::out);
    for (i = 0; i < n; i++)
    {
        cout << v[i] << " ";
        myfile << v[i] << " ";
    }
    myfile.close();
    return 0;
}
