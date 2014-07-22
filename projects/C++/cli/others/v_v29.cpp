#include <iostream>
#include <fstream>
using namespace std;

int n, m, v1[100], v2[100];

bool proc()
{
    int i, j, s;
    if (n < m) {
        return false;
    }
    i = j = s = 0;
    for (i = 0; i < n && j < m; i++) {
        s += v1[i];
        if (s >= v2[j]) {
            if (s == v2[j]) {
                s = 0;
                j++;
            } else {
                return false;
            }
        }
    }
    if (i == n && j == m) {
        return true;
    }
    return false;
}

int main()
{
    int i;
    ifstream fin("numere.in");
    fin >> n >> m;
    for (i = 0; i < n; i++) {
        fin >> v1[i];
    }
    for (i = 0; i < m; i++) {
        fin >> v2[i];
    }
    fin.close();
    if (proc()) {
        cout << "DA";
    } else {
        cout << "NU";
    }
    cin.get();
    return 0;
}
