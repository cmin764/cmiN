#include <cstdio>
#include <cctype>
#include <iostream>
#include <string>
using namespace std;


//#define ERR 1 // show debug
#define EOL '\n'


const int N = 26;


char dict[N];
bool marked[N];


inline int ord(char c)
{
    return c - 'a';
}


inline void init()
{
    string from[] = {"ejp mysljylc kd kxveddknmc re jsicpdrysi",
                     "rbcpc ypc rtcsra dkh wyfrepkym veddknkmkrkcd",
                     "de kr kd eoya kw aej tysr re ujdr lkgc jv"};
    string to[] = {"our language is impossible to understand",
                   "there are twenty six factorial possibilities",
                   "so it is okay if you want to just give up"};
    // y-a e-o q-z
    dict[ord('y')] = 'a'; marked[ord('a')] = 1;
    dict[ord('e')] = 'o'; marked[ord('o')] = 1;
    dict[ord('q')] = 'z'; marked[ord('z')] = 1;
    int total = 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < from[i].size(); ++j) {
            if (isspace(from[i][j])) continue;
            int pos = ord(from[i][j]);
            #ifdef ERR
            cerr << pos << endl;
            #endif
            if (dict[pos]) continue;
            dict[pos] = to[i][j];
            marked[ord(to[i][j])] = 1;
            ++total;
        }
    }
    if (total != N) {
        #ifdef ERR
        cerr << "Missing: " << N - total << endl;
        #endif
        // one is missing
        int pos = 0;
        while (dict[pos]) ++pos;
        int trans = 0;
        while (marked[trans]) ++trans;
        // complete
        dict[pos] = trans + 'a';
        #ifdef ERR
        for (int i = 0; i < N; ++i) cerr << char('a' + i) << ": " << dict[i] << endl;
        #endif
    }
}


void process()
{
    int tests;
    scanf("%d\n", &tests);
    for (int i = 1; i <= tests; ++i) {
        // now read until EOL
        printf("Case #%d: ", i);
        char chr;
        while ((chr = getchar()) != EOL && chr != EOF) {
            if (isspace(chr)) {
                putchar(' ');
            } else {
                putchar(dict[ord(chr)]);
            }
        }
        putchar(EOL);
    }
}


int main()
{
    freopen("A-small-attempt0.in", "r", stdin);
    freopen("A-small-attempt0.out", "w", stdout);
    init();
    process();
    fclose(stdin);
    fclose(stdout);
    return 0;
}
