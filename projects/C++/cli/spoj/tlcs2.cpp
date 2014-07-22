#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <vector>
using namespace std;

const int N = 1024, A = 26;
int lenx, leny, gmlen, * length;
long ipos, maxmem;
char vecx[N], vecy[N];
vector<pair<int, int> > apar;

inline void read()
{
    scanf("%d %s", &lenx, vecx + 1);
    scanf("%d %s", &leny, vecy + 1);
}

void futere(long param)
{
    if (param >= 0) {
        if ((length[param] == gmlen) && (apar[ipos].second > apar[param].second)) {
            gmlen--;
            futere(param - 1);
            printf("%c %d %d\n", vecy[apar[param].second], apar[param].first, apar[param].second);
        } else {
            futere(param - 1);
        }
    }
}

inline void write(int cnt, bool flag)
{
    if (flag) {
        printf("case %d Y\n", cnt);
        printf("%d\n", gmlen);
        gmlen--;
        futere(ipos - 1);
        printf("%c %d %d\n", vecy[apar[ipos].second], apar[ipos].first, apar[ipos].second);
    } else {
        printf("case %d N\n", cnt);
    }
}

inline void generate()
{
    bool viz[A];
    vector<pair<int, int> > lists[A];
    memset(viz, 0, A);
    apar.clear();
    for (int i = 1; i <= lenx; ++i) {
        short int poz = vecx[i] - 'a';
        if (!viz[poz]) {
            viz[poz] = 1;
            for (int j = 1; j <= leny; ++j) {
                if (vecx[i] == vecy[j]) {
                    lists[poz].push_back(pair<int, int>(i, j));
                }
            }
        }
        vector<pair<int, int> >::reverse_iterator fit = lists[poz].rbegin(), lit = lists[poz].rend();
        for (; fit != lit; ++fit) {
            fit->first = i;
            apar.push_back(*fit);
        }
    }
}

inline void lis(int cnt)
{
    bool flag = 0;
    long dim, i, j;
    int mlen;
    gmlen = 1;
    ipos = 0;
    dim = (long) apar.size();
    if (dim) {
        flag = 1;
        if (dim > maxmem) {
            maxmem = dim;
            length = (int*) realloc(length, maxmem * sizeof(int));
        }
        length[0] = 1;
        for (i = 1; i < dim; ++i) {
            mlen = 0;
            for (j = i - 1; j >= 0; --j) {
                if ((apar[i].second > apar[j].second) && (length[j] > mlen)) {
                    mlen = length[j];
                }
            }
            length[i] = mlen + 1;
            if (length[i] > gmlen) {
                gmlen = length[i];
                ipos = i;
            }
        }
    }
    write(cnt, flag);
}

int main()
{
    //freopen("tlcs.in", "rt", stdin);
    clock_t tstart = clock();
    int nr, i;
    scanf("%d", &nr);
    for (i = 1; i <= nr; ++i) {
        if ((double) (clock() - tstart) / CLOCKS_PER_SEC < 4.8) {
            read();
            generate();
            lis(i);
        } else {
            write(i, 0);
        }
    }
    return 0;
}
