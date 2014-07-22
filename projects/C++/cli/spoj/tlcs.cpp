#include <cstdio>
#include <ctime>

const int N = 1024;
const long MAX = 500000;
const double LIM = 4.95;
int lenx, leny, mat[N][N], sum, start, lenf, lenl;
char vecx[N], vecy[N];
clock_t tstart = clock();

struct Wstr {
    int x, y;
    char c;
} word[N], first[N], last[N];

inline bool verify()
{
    if ((((double) (clock() - tstart)) / CLOCKS_PER_SEC) > LIM) {
        return 0;
    }
    if (lenx * leny > MAX) {
        return 0;
    }
    return 1;
}

inline void init()
{
    sum = lenf = lenl = 0;
    start = 1;
    scanf("%d %s", &lenx, vecx + 1);
    scanf("%d %s", &leny, vecy + 1);
}

inline void write(int cnt)
{
    int i, total;
    if (total = sum + lenf + lenl) {
        printf("case %d Y\n", cnt);
        printf("%d\n", total);
        for (i = 1; i <= lenf; ++i) {
            printf("%c %d %d\n", first[i].c, first[i].x, first[i].y);
        }
        for (i = 1; i <= sum; ++i) {
            printf("%c %d %d\n", word[i].c, word[i].x, word[i].y);
        }
        for (i = lenl; i >= 1; --i) {
            printf("%c %d %d\n", last[i].c, last[i].x, last[i].y);
        }
    } else {
        printf("case %d N\n", cnt);
    }
}

inline int maxim(int a, int b)
{
    return a > b ? a : b;
}

inline void trim()
{
    int i;
    while (vecx[start] == vecy[start]) {
        first[++lenf].c = vecx[start];
        first[lenf].x = first[lenf].y = start;
        ++start;
    }
    while (vecx[lenx] == vecy[leny]) {
        last[++lenl].c = vecx[lenx];
        last[lenl].x = lenx;
        last[lenl].y = leny;
        --lenx;
        --leny;
    }
    for (i = start - 1; i <= lenx && i <= leny; ++i) {
        mat[i][start - 1] = mat[start - 1][i] = 0;
    }
    while (i <= lenx) {
        mat[i][start - 1] = 0;
        ++i;
    }
    while (i <= leny) {
        mat[start - 1][i] = 0;
        ++i;
    }
}

inline void optimized()
{
    int i, j;
    for (i = start; i <= lenx && i <= leny; ++i) {
        if (vecx[i] == vecy[i]) {
            mat[i][i] = mat[i - 1][i - 1] + 1;
        } else {
            mat[i][i] = maxim(mat[i][i - 1], mat[i - 1][i]);
        }
        for (j = i + 1; j <= lenx && j <= leny; ++j) {
            if (vecx[i] == vecy[j]) {
                mat[i][j] = mat[i - 1][j - 1] + 1;
            } else {
                mat[i][j] = maxim(mat[i][j - 1], mat[i - 1][j]);
            }
            if (vecx[j] == vecy[i]) {
                mat[j][i] = mat[j - 1][i - 1] + 1;
            } else {
                mat[j][i] = maxim(mat[j][i - 1], mat[j - 1][i]);
            }
        }
        while (j <= lenx) {
            if (vecx[j] == vecy[i]) {
                mat[j][i] = mat[j - 1][i - 1] + 1;
            } else {
                mat[j][i] = maxim(mat[j][i - 1], mat[j - 1][i]);
            }
            ++j;
        }
        while (j <= leny) {
            if (vecx[i] == vecy[j]) {
                mat[i][j] = mat[i - 1][j - 1] + 1;
            } else {
                mat[i][j] = maxim(mat[i][j - 1], mat[i - 1][j]);
            }
            ++j;
        }
    }
}

inline void clasical()
{
    for (int i = start; i <= lenx; ++i) {
        for (int j = start; j <= leny; ++j) {
            if (vecx[i] == vecy[j]) {
                mat[i][j] = mat[i - 1][j - 1] + 1;
            } else {
                mat[i][j] = maxim(mat[i][j - 1], mat[i - 1][j]);
            }
        }
    }
}

inline void process()
{
    // trim(); // WrongAnswer
    // optimized(); // Slow - 200 pts
    clasical();
    sum = mat[lenx][leny];
    while (int poz = mat[lenx][leny]) {
        if (vecx[lenx] == vecy[leny]) {
            word[poz].c = vecx[lenx];
            word[poz].x = lenx;
            word[poz].y = leny;
            lenx--;
            leny--;
        } else if (poz == mat[lenx][leny - 1]) {
            leny--;
        } else {
            lenx--;
        }
    }
}

int main()
{
    //freopen("tlcs.in", "rt", stdin);
    int nr;
    scanf("%d", &nr);
    for (int i = 1; i <= nr; ++i) {
        init();
        if (verify()) {
            process();
        }
        write(i);
    }
    return 0;
}
