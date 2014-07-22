#include <fstream>
#include <vector>
#define iname "pachete.in"
#define oname "pachete.out"
using namespace std;

int nr, minWait;
vector<pair<short, short> > pack;

void init()
{
    short x, y;
    ifstream fin(iname);
    fin >> nr;
    for (int i = 0; i < nr; ++i) {
        fin >> x >> y;
        pack.push_back(make_pair(x, y));
    }
    fin.close();
}

void process()
{
    int tmp = 0;
    minWait = pack[0].second;
    for (int i = 0; i < pack.size() - 1; ++i) {
        tmp += pack[i + 1].second - pack[i].first;
        if (tmp > 0) {
            minWait += tmp;
            tmp = 0;
        }
    }
}

void show()
{
    ofstream fout(oname);
    fout << minWait;
    fout.close();
}

int main()
{
    init();
    process();
    show();
    return 0;
}
