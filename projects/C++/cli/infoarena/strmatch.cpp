/*
 * Fail example of Rabin-Karp for string matching.
 * It takes O(NlogN) (not linear).
 * Also on some examples it gives wrong answer.
 * Just for code fun, not efficient.
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;


class Hash {
    /**
     * Simple hashing class.
     * Works with string objects.
     * Optimized update.
     *
     * Hash(arg) -> make hash
     * get() -> get hash
     * del() -> erase first char
     * add() -> append char
     */

    private:
    typedef unsigned int hash_type;
    static const hash_type MOD1 = 63013, MOD2 = 51337;
    static const hash_type BAS1 = 101, BAS2 = 13; // base
    hash_type hash1, hash2, exp;
    queue<char> que;

    hash_type power(hash_type bas, hash_type expo, hash_type mod)
    {
        /// Logarithmic exponentiation. Here I have logN.
        hash_type res = 1;
        while (expo) {
            if (expo % 2) res = (res * bas) % mod;
            bas = (bas * bas) % mod;
            expo /= 2;
        }
        return res;
    }

    public:
    Hash(string arg="")
    {
        hash1 = hash2 = 0;
        exp = arg.size() - 1;
        for (int i = 0; i <= exp; ++i) {
            que.push(arg[i]);
            hash1 = (hash1 + arg[i] * power(BAS1, exp - i, MOD1)) % MOD1;
            hash2 = (hash2 + arg[i] * power(BAS2, exp - i, MOD2)) % MOD2;
        }
    }

    hash_type get(int which) const
    {
        if (which == 1) return hash1;
        return hash2;
    }

    void del()
    {
        if (que.empty()) return;
        hash1 -= (que.front() * power(BAS1, exp, MOD1)) % MOD1;
        hash2 -= (que.front() * power(BAS2, exp, MOD2)) % MOD2;
        que.pop();
    }

    void add(char chr)
    {
        hash1 = (hash1 * BAS1 + chr) % MOD1;
        hash2 = (hash2 * BAS2 + chr) % MOD2;
        que.push(chr);
    }

    bool operator==(const Hash& arg) const
    {
        bool test1 = get(1) == arg.get(1) ? true : false;
        bool test2 = get(2) == arg.get(2) ? true : false;
        if (test1 && test2) return true;
        return false;
    }
};


const int DIM = 1000;
string str, pat;
vector<int> matchPos;


void solve()
{
    Hash patHash(pat);
    int ind = min(pat.size(), str.size());
    Hash strHash(str.substr(0, ind));
    for (; matchPos.size() < DIM; ++ind) {
        if (patHash == strHash) matchPos.push_back(ind - pat.size());
        if (ind == str.size()) break;
        strHash.del();
        strHash.add(str[ind]);
    }
}


int main()
{
    ifstream fin("strmatch.in");
    ofstream fout("strmatch.out");
    fin >> pat >> str;
    solve();
    fout << matchPos.size() << '\n';
    for (int i = 0; i < matchPos.size(); ++i) fout << matchPos[i] << ' ';
    fin.close();
    fout.close();
    return 0;
}
