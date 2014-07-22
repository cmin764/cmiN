#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;


struct CandyGame {

	static const int N = 2000000000;

	typedef long long ll_t;
	typedef vector<string> vs_t;
	typedef vector<int> vi_t;
	typedef vector<vi_t> vv_t;

	vv_t adjList; // adjacency list
	int root, size; // target, nodes
	ll_t total; // number of cookies
	int* height; // h[i] -> maximum height of node i
	ll_t* cookie; // c[i] -> how many cookies are on node i
	bool* seen; // seen[i] -> passed through i
	queue<int> nodeQue;

	~CandyGame()
	{
		delete[] height;
		delete[] cookie;
	}

	inline void add(ll_t value)
	{
		if (total == -1) return;
		total += value;
		if (total > N) total = -1;
	}

	void dfs(int from, int node)
	{
		//cout << node << endl;
		height[node] = 0;
		int nbrs = adjList[node].size();
		if (!nbrs) return; // useless
		for (int i = 0; i < nbrs; ++i) {
			int crt = adjList[node][i];
			if (crt == from) continue; // do not get back
			dfs(node, crt);
			if (height[crt] + 1 > height[node]) height[node] = height[crt] + 1;
		}
	}

	void bfs()
	{
		while (!nodeQue.empty()) {
			int from = nodeQue.front();
			nodeQue.pop();
			seen[from] = 1;
			// check for sons
			int nbrs = adjList[from].size();
			if (nbrs == 1 && seen[adjList[from][0]]) continue; // leave it be
			// or go further
			ll_t last = cookie[from]; // number of parent cookies
			// erase all cookies from parent
			cookie[from] = 0;
			add(-1 * last);
			// spread them around
			int maxNode = -1; // invalid
			int maxHeight = -1;
			for (int i = 0; i < nbrs; ++i) {
				int crt = adjList[from][i];
				if (seen[crt]) continue;
				if (height[crt] > maxHeight) {
					maxHeight = height[crt];
					maxNode = crt;
				}
			}
			// `maxNode` gets all
			cookie[maxNode] = last * 2 + 1;
			add(cookie[maxNode]);
			nodeQue.push(maxNode);
			// and 1 for the rest
			for (int i = 0; i < nbrs; ++i) {
				int crt = adjList[from][i];
				if (crt == maxNode || seen[crt]) continue;
				cookie[crt] = 1;
				add(1);
				nodeQue.push(crt); // save the neighbour
			}
		}
	}

	void test1()
	{
		for (int i = 0; i < adjList.size(); ++i) {
			for (int j = 0; j < adjList[i].size(); ++j) {
				cout << adjList[i][j] << " ";
			}
			cout << endl;
		}
	}

	void test2()
	{
		for (int i = 0; i < size; ++i) cout << height[i] << " ";
		cout << endl;
	}

	void conex(int node)
	{
		seen[node] = 1;
		for (int i = 0; i < adjList[node].size(); ++i) {
			int crt = adjList[node][i];
			if (seen[crt]) continue;
			conex(crt);
		}
	}

	void solve()
	{
		if (size == 1) {
			total = 0;
			return;
		}
		seen = new bool[size];
		memset(seen, 0, sizeof(bool) * size);
		conex(root);
		for (int i = 0; i < size; ++i) {
			if (seen[i]) continue;
			total = -1;
			return;
		}
		// compute heights
		height = new int[size];
		dfs(-1, root); // from=>to
		// put cookies :]
		cookie = new ll_t[size];
		cookie[root] = 0;
		memset(seen, 0, sizeof(bool) * size);
		nodeQue.push(root);
		bfs();
	}

	int maximumCandy(vs_t graph, int target)
	{
		/// Main function. Create adjacency list from `graph` and set `target` as root.
		total = 0;
		root = target;
		size = graph.size();
		adjList.resize(size);
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				if (graph[i][j] == 'Y') adjList[i].push_back(j);
			}
		}
		//test1();
		solve();
		return total;
	}
};


int main()
{
    CandyGame problem;
    string vec[] = {"NYNNNYN",
                    "YNYNYNN",
                    "NYNYNNN",
                    "NNYNNNN",
                    "NYNNNNN",
                    "YNNNNNY",
                    "NNNNNYN"};
    CandyGame::vs_t arg(vec, vec + 7);
    cout << problem.maximumCandy(arg, 0);
    return 0;
}
