#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
using namespace std;


typedef list<int> li_t;


int nodes, edges;
queue<int> start;
vector<int> ordered;
vector<li_t> /*parent,*/ adjList;
int* parSize;


void solve()
{
    // check for those without parents
    for (int i = 1; i <= nodes; ++i) {
        //if (parent[i].empty()) start.push(i);
        if (!parSize[i]) start.push(i);
    }
    while (!start.empty()) {
        int node = start.front();
        start.pop();
        ordered.push_back(node);
        //queue<li_t::iterator> toErase;
        for (li_t::iterator it = adjList[node].begin(); it != adjList[node].end(); ++it) {
            /*toErase.push(it);
            parent[*it].erase(find(parent[*it].begin(), parent[*it].end(), node));
            if (parent[*it].empty()) start.push(*it);*/
            --parSize[*it];
            if (!parSize[*it]) start.push(*it);
        }
        /*while (!toErase.empty()) {
            adjList[node].erase(toErase.front());
            toErase.pop();
        }*/
    }
}


int main()
{
    freopen("sortaret.in", "r", stdin);
    freopen("sortaret.out", "w", stdout);
    cin >> nodes >> edges;
    parSize = new int[nodes + 1];
    memset(parSize, 0, sizeof(int) * (nodes + 1));
    //parent.resize(nodes + 1);
    adjList.resize(nodes + 1);
    for (int i = 0; i < edges; ++i) {
        int x, y;
        cin >> x >> y;
        adjList[x].push_back(y);
        ++parSize[y];
        //parent[y].push_back(x);
    }
    solve();
    for (int i = 0; i < ordered.size(); ++i) cout << ordered[i] << ' ';
    fclose(stdin);
    fclose(stdout);
    return 0;
}
