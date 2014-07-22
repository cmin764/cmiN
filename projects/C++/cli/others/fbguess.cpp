#include <cstdio>
#include <iostream>
#include <set>
#include <map>
#include <vector>
using namespace std;


class Comp {

    public:
    typedef vector<int> vi_t;
    typedef pair<int, vi_t> piv_t;

    bool operator()(const piv_t& a, const piv_t& b) const
    {
        return a.first < b.first;
    }
};


const int DIM = 11;
typedef vector<Comp::vi_t> vv_t;
typedef multiset<Comp::piv_t, Comp> sp_t;
bool status;
int nr, len, lines; // n, k, q
int sol[DIM][DIM + 1];
sp_t guesses;
sp_t::iterator bidIt;


template<class T>
inline int count_differences(const T& first, const T& second)
{
    int diff = 0;
    typename T::const_iterator firstIt, secondIt;
    firstIt = first.begin();
    secondIt = second.begin();
    while (firstIt != first.end() && secondIt != second.end()) {
        if (*firstIt != *secondIt) ++diff;
        ++firstIt;
        ++secondIt;
    }
    while (firstIt != first.end()) {
        ++diff;
        ++firstIt;
    }
    while (secondIt != second.end()) {
        ++diff;
        ++secondIt;
    }
    return diff;
}


void init_sol()
{
    for (int i = 0; i < len; ++i) {
        sol[i][0] = 0;
        for (int j = 1; j <= nr; ++j) {
            sol[i][j] = 1;
        }
    }
}


void back(int pos, int use)
{
    if (bidIt == guesses.end()) {
        status = true;
    } else {
        if (use == bidIt->first) {
            bool ok = true;
            int active = 0;
            map<int, pair<int, int> > toZero;
            for (int i = 0; i < len && ok; ++i) {
                if (bidIt->second[i] == sol[i][0]) {
                    ++active;
                    continue;
                }
                if (!sol[i][0]) {
                    bool leastOne = false;
                    for (int j = 1; j <= nr; ++j) {
                        if (sol[i][j] && j != bidIt->second[i]) {
                            leastOne = true;
                            break;
                        }
                    }
                    if (leastOne) {
                        toZero[i] = make_pair(bidIt->second[i], sol[i][bidIt->second[i]]);
                    } else {
                        ok = false;
                    }
                }
            }
            if (ok && use == active) {
                map<int, pair<int, int> >::iterator it;
                for (it = toZero.begin(); it != toZero.end(); ++it) {
                    sol[it->first][it->second.first] = 0;
                }
                ++bidIt;
                back(0, 0);
                --bidIt;
                for (it = toZero.begin(); it != toZero.end(); ++it) {
                    sol[it->first][it->second.first] = it->second.second;
                }
            }
        } else { // count and mark the good ones
            for (int i = pos; i <= len - bidIt->first + use && !status; ++i) {
                if (!sol[i][0] && sol[i][bidIt->second[i]]) {
                    sol[i][0] = bidIt->second[i];
                    back(i + 1, use + 1);
                    sol[i][0] = 0;
                } else if (sol[i][0] == bidIt->second[i]) {
                    back(i + 1, use + 1);
                } else {
                    continue;
                }
            }
        }
    }
}


void process()
{
    bool fullGuess = false;
    Comp::vi_t guess;
    vector<sp_t::iterator> iters;
    /* get rid of full guesses */
    for (sp_t::reverse_iterator it = guesses.rbegin(); it != guesses.rend() && it->first == len && status; it++) {
        if (fullGuess) {
            if (count_differences<Comp::vi_t>(guess, it->second)) status = false;
        } else {
            //cerr << "activated";
            fullGuess = true;
            guess = it->second;
        } // actually --.base with casting it's a weird solution
        iters.push_back((sp_t::iterator)(--(it.base()))); // iterator integrity safe
    }
    for (vector<sp_t::iterator>::iterator it = iters.begin(); it != iters.end(); ++it) {
        guesses.erase(*it);
    }
    if (!status) return;
    if (fullGuess) {
        /* check the rest for exceptions */
        sp_t::iterator it = guesses.begin();
        while (it != guesses.end() && status) {
            if (count_differences<Comp::vi_t>(guess, it->second) != len - it->first) status = false;
            it++;
        }
    } else {
        /* or reduce possibilities */
        init_sol();
        for (sp_t::iterator it = guesses.begin(); it != guesses.end() && !it->first;) {
            for (int i = 0; i < len; ++i) {
                sol[i][it->second[i]] = 0;
            }
            guesses.erase(it++);
        }
        status = false;
        bidIt = guesses.begin();
        back(0, 0);
    }
}


int main()
{
    //freopen("fbguess.in", "rt", stdin);
    int tests;
    cin >> tests;
    while (tests--) {
        status = true;
        guesses.clear();
        cin >> nr >> len >> lines;
        for (int i = 0, good; i < lines; ++i) {
            vector<int> tmpVec;
            for (int j = 0, tmpInt; j < len; ++j) {
                cin >> tmpInt;
                tmpVec.push_back(tmpInt);
            }
            cin >> good;
            guesses.insert(make_pair(good, tmpVec));
        }
        process();
        if (status) cout << "YES";
        else cout << "NO";
        cout << endl;
    }
    return 0;
}
