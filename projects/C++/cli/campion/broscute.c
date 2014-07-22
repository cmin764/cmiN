/**
 * Se cauta punctele de pe diagonale comune, marcand locurile,
 * apoi se face intersectia celorlalte diagonale.
 * O(KNsqrt2)
 */
#include <stdio.h>
#define N 1001
#define K 200001
#define iname "broscute.in"
#define oname "broscute.out"


int n, mat[N][N], total;
char used[K];


inline char check(int x, int y)
{
    if (x < 1 || x > n) return 0;
    if (y < 1 || y > n) return 0;
    return 1;
}


inline void mark(int x, int y, int id)
{
    /* Se numara toate intersectiile cu exceptia celor de pe diagonala comuna. */
    int i = 1, c1, c2, c3, c4, *tmp; // in functie de raza incrementam intersectiile
    char d1, d2, d3, d4; // daca exista sau nu directia respectiva
    char s1, s2, s3, s4; // daca nu am intalnit pe directie vreo sursa
    d1 = d2 = d3 = d4 = 1;
    s1 = s2 = s3 = s4 = 1;
    c1 = c2 = c3 = c4 = 0;
    mat[x][y] = id; // marcam sursa
    while (d1 || d2 || d3 || d4) {
        d1 = check(x + i, y + i);
        d2 = check(x + i, y - i);
        d3 = check(x - i, y - i);
        d4 = check(x - i, y + i);
        if (d1) {
            tmp = &mat[x + i][y + i];
            if (*tmp) {
                if (*tmp == -1) {
                    ++c1;
                } else {
                    if (!used[id]) ++total;
                    if (!used[*tmp]) ++total;
                    used[id] = 1;
                    used[*tmp] = 1;
                    s1 = 0;
                }
            } else {
                *tmp = -1;
            }
        }
        if (d2) {
            tmp = &mat[x + i][y - i];
            if (*tmp) {
                if (*tmp == -1) {
                    ++c2;
                } else {
                    if (!used[id]) ++total;
                    if (!used[*tmp]) ++total;
                    used[id] = 1;
                    used[*tmp] = 1;
                    s2 = 0;
                }
            } else {
                *tmp = -1;
            }
        }
        if (d3) {
            tmp = &mat[x - i][y - i];
            if (*tmp) {
                if (*tmp == -1) {
                    ++c3;
                } else {
                    if (!used[id]) ++total;
                    if (!used[*tmp]) ++total;
                    used[id] = 1;
                    used[*tmp] = 1;
                    s3 = 0;
                }
            } else {
                *tmp = -1;
            }
        }
        if (d4) {
            tmp = &mat[x - i][y + i];
            if (*tmp) {
                if (*tmp == -1) {
                    ++c4;
                } else {
                    if (!used[id]) ++total;
                    if (!used[*tmp]) ++total;
                    used[id] = 1;
                    used[*tmp] = 1;
                    s4 = 0;
                }
            } else {
                *tmp = -1;
            }
        }
        ++i;
    }
    if (s1 && s3) total += c1 + c3;
    if (s2 && s4) total += c2 + c4;
}


int main()
{
    int i, k, x, y;
    freopen(iname, "r", stdin);
    freopen(oname, "w", stdout);
    scanf("%d %d", &n, &k);
    for (i = 1; i <= k; ++i) {
        scanf("%d %d", &x, &y);
        mark(x, y, i);
    }
    printf("%d", total);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
