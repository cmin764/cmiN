#include <cstdio>

struct word_s {
    char word[10002];
    int len;
} cuv, dict;
int m, k, sol[2][10002];
const int inf = 0x7Fff;

int norm(int x)
{
    if (x == 0) {
        return inf;
    } else {
        return x;
    }
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

inline int levenstein()
{
    int i, j, start, end, res;
    sol[0][0] = 1; // 0 = inf
    for (j = 1; j <= k + 1; j++) {
        sol[0][j] = j + 1;
    }
    for (i = 1; i <= cuv.len; i++) {
        sol[1][0] = i + 1;
        start = max(1, i - k);
        end = min(i + k, dict.len);
        for (j = start; j <= end; j++) {
            if (cuv.word[i] == dict.word[j]) {
                sol[1][j] = sol[0][j - 1];
            } else {
                res = min(min(norm(sol[1][j - 1]), norm(sol[0][j - 1])), norm(sol[0][j]));
                if (res != inf) {
                    res++;
                }
                sol[1][j] = res;
            }
        }
        for (j = start; j <= end; j++) {
            sol[0][j] = sol[1][j];
        }
    }
    return (norm(sol[1][dict.len]) - 1) <= k;
}

int main()
{
    freopen("cuvinte1.in", "rt", stdin);
    freopen("cuvinte1.out", "wt", stdout);
    scanf("%d %d", &m, &k);
    scanf("%d %s", &cuv.len, 1 + cuv.word);
    while (m-- > 0) {
        scanf("%d %s", &dict.len, 1 + dict.word);
        printf("%d\n", levenstein());
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
