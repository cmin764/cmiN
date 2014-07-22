#include <iostream>
#include <fstream>

using namespace std;
int g, w, emax = 0;
struct generator {
    int e;
    int c;
    bool a;
} gen[1024];
long enr[5120];

void restore()
{
    for (int i = 1; i <= g; i++) {
        gen[i].a = 0;
    }
}

long process()
{
    int i, j, last = 0;
    long cmax = 10000000, erel = -1;
    enr[0] = 0;
    for (i = 1; i <= w; i++) {
        enr[i] = cmax;
        if (i <= emax) {
            for (j = 1; j <= g; j++) {
                if (gen[j].e >= i && gen[j].c < enr[i]) {
                    enr[i] = gen[j].c;
                    restore();
                    gen[j].a = 1;
                    erel = gen[j].e - i;
                }
            }
        } else {
            if (erel >= 0) {
                enr[i] = enr[i - 1];
                erel--;
            } else {
                for (j = 1; j <= g; j++) {
                    if (!gen[j].a && (gen[j].c + enr[i - 1]) < enr[i]) {
                        enr[i] = gen[j].c + enr[i - 1];
                        erel = gen[j].e - 1;
                        gen[last].a = 0;
                        gen[j].a = 1;
                        last = j;
                    }
                }
                last = 0;
                if (erel == -1) {
                    return -1;
                }
            }
        }
    }
    return enr[w];
}

int main()
{
    ifstream fin("energii.in");
    fin >> g >> w;
    for (int i = 1; i <= g; i++) {
        fin >> gen[i].e >> gen[i].c;
        gen[i].a = 0;
        if (gen[i].e > emax) {
            emax = gen[i].e;
        }
    }
    fin.close();
    ofstream fout("energii.out");
    fout << process();
    fout.close();
    return 0;
}
