#include <iostream>
#include <fstream>
#include <math.h>
#define fname "triunghiuri.in"

using namespace std;
struct Punct {
    int x, y;
};

double dist(Punct A, Punct B)
{
    return sqrt(pow((B.x - A.x), 2) + pow((B.y - A.y), 2));
}

int main()
{
    int n, i, nr = 0;
    double val, lat[3], sp;
    Punct tgl[3];
    cout << "Valoare: ";
    cin >> val;
    ifstream fin(fname);
    fin >> n;
    while (n-- > 0) {
        for (i = 0; i < 3; i++) {
            fin >> tgl[i].x >> tgl[i].y;
        }
        lat[0] = dist(tgl[0], tgl[1]);
        lat[1] = dist(tgl[0], tgl[2]);
        lat[2] = dist(tgl[1], tgl[2]);
        // Heron
        sp = (lat[0] + lat[1] + lat[2]) / 2;
        if (sqrt(sp * (sp - lat[0]) * (sp - lat[1]) * (sp - lat[2])) > val) {
            nr++;
        }
    }
    fin.close();
    cout << nr;
    system("pause >nul");
    return 0;
}
