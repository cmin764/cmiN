#include <iostream>
#include <cstdio>
#include <string>
using namespace std;


const string vow = "aeiou";
string line, suf[4], last;
int n, k;
bool ok;


inline int get_suf()
{
    int i, j;
    for (i = line.size() - 1, j = 0; i >= 0 && j < k; --i) {
        if (vow.find(line[i]) != string::npos) ++j;
    }
    if (j != k) ok = false;
    return i + 1;
}


inline string get_rhyme()
{
    string rhyme = "abcd";
    if (!ok) return rhyme;
    else if (suf[0] == suf[1] && suf[1] == suf[2] && suf[2] == suf[3]) rhyme = "aaaa";
    else if (suf[0] == suf[1] && suf[2] == suf[3]) rhyme = "aabb";
    else if (suf[0] == suf[2] && suf[1] == suf[3]) rhyme = "abab";
    else if (suf[0] == suf[3] && suf[1] == suf[2]) rhyme = "abba";
    return rhyme;
}


int main()
{
    //freopen("c.in", "rt", stdin);
    //freopen("c.out", "wt", stdout);
    cin >> n >> k;
    ok = true;
    for (int i = 0; i < 4; ++i) {
        cin >> line;
        suf[i] = line.substr(get_suf());
    }
    last = get_rhyme();
    //cerr << last;
    if (last == "abcd") {
        cout << "NO";
        return 0;
    }
    while (--n > 0) {
        ok = true;
        for (int i = 0; i < 4; ++i) {
            cin >> line;
            suf[i] = line.substr(get_suf());
        }
        string tmp = get_rhyme();
        if (last != tmp) {
            if (tmp == "aaaa");
            else if (last == "aaaa" && tmp != "abcd") last = tmp;
            else {
                cout << "NO";
                return 0;
            }
        }
    }
    cout << last;
    return 0;
}
