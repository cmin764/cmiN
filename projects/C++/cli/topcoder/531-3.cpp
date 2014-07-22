#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;


class KingdomReorganization {

    public:
    typedef vector<string> vs_t;
    typedef multimap<int, pair<int, int> > mip_t; // cost-edge
    typedef set<int> si_t;
    mip_t destroy, build, graph;
    int minCost, edges;

    int get_cost(char arg) const
    {
        int ret = arg - 'A';
        if (arg >= 'a') ret -= 'a' - 'Z' - 1; // skip 6 punctuation chars
        return ret;
    }

    void init(const vs_t& kingdom, const vs_t& build, const vs_t& destroy)
    {
        /** Filter costs from args. */
        minCost = 0;
        edges = kingdom.size();
        for (int i = 0; i < edges; ++i) {
            for (int j = i + 1; j < edges; ++j) {
                if (kingdom[i][j] == '1') this->destroy.insert(make_pair(get_cost(destroy[i][j]), make_pair(i, j)));
                else this->build.insert(make_pair(get_cost(build[i][j]), make_pair(i, j)));
            }
        }
    }

    bool add(int id, const pair<int, int>& edge)
    {
        int x = edge.first, y = edge.second;
        int xLink = 0, yLink = 0;
        for (mip_t::iterator it = graph.begin(); it != graph.end(); ++it) {
            if (x == it->second.first || x == it->second.second) xLink = it->first;
            if (y == it->second.first || y == it->second.second) yLink = it->first;
        }
        if (!(xLink || yLink)) { // lonely edge xD
            graph.insert(make_pair(id, edge));
            return true;
        } else if (xLink != yLink) { // no cycle
            si_t conflict;
            if (xLink) conflict.insert(xLink);
            if (yLink) conflict.insert(yLink);
            int to = *conflict.begin(); // destination
            graph.insert(make_pair(to, edge));
            if (conflict.size() == 2) {
                int from = *(++conflict.begin()); // what to transform in `to`
                pair<mip_t::iterator, mip_t::iterator> range = graph.equal_range(from);
                mip_t temp(range.first, range.second);
                graph.erase(range.first, range.second);
                for (mip_t::iterator it = temp.begin(); it != temp.end(); ++it) {
                    graph.insert(make_pair(to, it->second));
                }
            }
            return true;
        }
        return false;
    }

    void make()
    {
        /** Build an acyclic graph. */
        int id = 1;
        for (mip_t::reverse_iterator rit = destroy.rbegin(); rit != destroy.rend(); ++rit, ++id) {
            // keep those with higher cost
            bool res = add(id, rit->second);
            if (!res) minCost += rit->first;
        }
        for (mip_t::iterator it = build.begin(); it != build.end(); ++it, ++id) {
            // try to add those with lower cost
            bool res = add(id, it->second);
            if (res) minCost += it->first;
        }
    }

    int getCost(vs_t kingdom, vs_t build, vs_t destroy)
    {
        init(kingdom, build, destroy);
        make();
        return minCost;
    }
};


int main()
{
    const int N = 10;
    string k[N] = {"0000000000","0000000011","0001010000","0010010000","0000001000","0011000000","0000100000","0000000011","0100000101","0100000110"};
    string b[N] = {"AhPEqkSFMM","hAfKPtsDad","PfAyGQkaqN","EKyAeLpRpm","qPGeASfNwo","ktQLSAnCAK","SskpfnAdJS","FDaRNCdAZz","MaqpwAJZAn","MdNmoKSznA"};
    string d[N] = {"AgTqWWxEYH","gAXPgjzIRA","TXAleTmWvT","qPlAQkwxRO","WgeQAqgbJJ","WjTkqAiTzl","xzmwgiAuHb","EIWxbTuAwk","YRvRJzHwAn","HATOJlbknA"};
    KingdomReorganization::vs_t kingdom(k, k + N), build(b, b + N), destroy(d, d + N);
    KingdomReorganization obj;
    cout << obj.getCost(kingdom, build, destroy);
    return 0;
}
