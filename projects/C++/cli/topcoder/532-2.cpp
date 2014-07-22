#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;


class DengklekMakingChains {

    public:
	typedef vector<string> vs_t;
	pair<string, int> left, right;
	int single;

	inline int check(const string& chain)
	{
		if (chain[0] == '.' && chain[1] == '.' && chain[2] == '.') return -1; // useless
		int sum = 0;
		for (int i = 0; i < 3; ++i) {
			if (chain[i] == '.') return 0; // rusted
			else sum += chain[i] - '0';
		}
		return sum; // no rust
	}

	inline void process(const string& chain)
	{
        // single case
        if (chain[0] == '.' && chain[2] == '.') {
            single = max(single, chain[1] - '0');
            return;
        }
        // process left
        int left = 0;
        if (chain[0] != '.') {
            left += chain[0] - '0';
            if (chain[1] != '.') left += chain[1] - '0';
        }
        if (left > this->left.second) this->left = make_pair(chain, left);
        // process right
        int right = 0;
        if (chain[2] != '.') {
            right += chain[2] - '0';
            if (chain[1] != '.') right += chain[1] - '0';
        }
        if (right > this->right.second) this->right = make_pair(chain, right);
	}

	int maxBeauty(vs_t chains)
	{
	    int get;
		int sum = 0;
		single = 0;
		// select those with rust
		vs_t rust;
		for (int i = 0; i < chains.size(); ++i) {
			get = check(chains[i]);
			if (get > 0) sum += get;
			else if (get == 0) rust.push_back(chains[i]);
		}
		//cerr << sum << " " << rust.size();
		// now select those with max lef/right
		left = right = make_pair("...", 0);
		for (int i = 0; i < rust.size(); ++i) process(rust[i]);
		get = left.second + right.second;
		if (left.first == right.first && count(rust.begin(), rust.end(), left.first) == 1) {
		    // same string used twice
		    pair<string, int> leftClone = left, rightClone = right;
			rust.erase(find(rust.begin(), rust.end(), left.first)); // erase it
			//cerr << rust.size() << endl;
			left = right = make_pair("...", 0);
			for (int i = 0; i < rust.size(); ++i) process(rust[i]); // and find another solution
			get = max(leftClone.second + right.second, rightClone.second + left.second);
		}
		//cerr << left.second << " " << right.second << " " << single;
		sum += get;
		return max(single, sum);
	}
};


int main()
{
    const int N = 8;
    string vec[N] = {"16.", "9.8", ".24", "52.", "3.1", "532", "4.4", "111"};
    DengklekMakingChains::vs_t param(vec, vec + N);
    DengklekMakingChains problem;
    cout << problem.maxBeauty(param);
    return 0;
}
