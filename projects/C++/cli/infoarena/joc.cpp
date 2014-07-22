#include <fstream>
#include <set>
using namespace std;

struct Path {
    static const short nr = 4;
    static const short dl[];
    static const short dc[];
};

const short Path::dl[] = {-1, 1, 0, 0};
const short Path::dc[] = {0, 0, -1, 1};
char** tabla;
short n, m;
set<char> road;
set<char>::size_type maxTurns;

void init()
{
    short i;
    ifstream fin("joc7.in");
    fin >> n >> m;
    tabla = new char*[n + 2];
    for (i = 1; i <= n; ++i) {
        tabla[i] = new char[m + 2];
        fin >> tabla[i] + 1;
        tabla[i][0] = 0;
    }
    tabla[0] = new char[m + 2];
    tabla[n + 1] = new char[m + 2];
    for (i = 0; i <= m + 1; ++i) {
        tabla[0][i] = tabla[n + 1][i] = 0;
    }
    fin.close();

}

void process(short lin, short col)
{
    if (!tabla[lin][col] || road.count(tabla[lin][col])) {
        if (road.size() > maxTurns) {
            maxTurns = road.size();
        }
    } else {
        pair<set<char>::iterator, bool> ret = road.insert(tabla[lin][col]);
        for (short i = 0; i < Path::nr; ++i) {
            process(lin + Path::dl[i], col + Path::dc[i]);
        }
        road.erase(ret.first);
    }
}

void show()
{
    ofstream fout("joc7.out");
    fout << maxTurns;
    fout.close();
}

int main()
{
    init();
    process(1, 1);
    show();
    return 0;
}
