#include <iostream>
#include <fstream>
#include <vector>
#include <cfloat>
#include <queue>
#include <stack>
using namespace std;


struct Elem {

    int node;
    float dist;

    Elem(int node=-1, float dist=-1)
    {
        this->node = node;
        this->dist = dist;
    }
};


struct Comp {

    bool operator()(const Elem & first,
                    const Elem & second) const
    {
        return first.dist > second.dist;
    }
};


typedef vector<int> vi_t;
typedef vector<float> vf_t;
typedef vector<vi_t> vvi_t;
typedef vector<vf_t> vvf_t;


int src, dest, nodes, edges;

vf_t timeList; // timpul in oras
vvf_t timeMat; // timpul intre orase
vvi_t adjList; // lista de adiacenta

vf_t dist; // timpul de ajungere
float totalTime; // timpul intregului traseu


void preprocess()
{
    ifstream fin("vacanta.in");
    fin >> src >> dest >> nodes >> edges;
    int size = nodes + 1;
    timeList.resize(size);
    timeMat.resize(size);
    adjList.resize(size);
    for (int i = 1; i <= nodes; ++i)
        timeMat[i].resize(size);
    for (int i = 0; i < nodes; ++i) {
        int n;
        float d, v;
        fin >> n >> d >> v;
        timeList[n] = d / v;
    }
    for (int i = 0; i < edges; ++i) {
        int x, y;
        float d, v;
        fin >> x >> y;
        fin >> d >> v;
        timeMat[x][y] = timeMat[y][x] = d / v;
        adjList[x].push_back(y);
        adjList[y].push_back(x);
    }
    fin.close();
}


void process()
{
    /// Dijkstra folosind coada cu prioritati.
    dist.assign(nodes + 1, FLT_MAX);
    dist[src] = 0;
    priority_queue<Elem, vector<Elem>, Comp> pq;
    pq.push(Elem(src, dist[src]));
    while (!pq.empty()) {
        Elem elem = pq.top();
        pq.pop();
        if (elem.node == dest) {
            totalTime = elem.dist;
            return;
        }
        for (vi_t::iterator it = adjList[elem.node].begin();
             it != adjList[elem.node].end(); ++it) {
            float tmp;
            if ((tmp = dist[elem.node] + timeMat[elem.node][*it] +
                timeList[*it]) < dist[*it]) {
                dist[*it] = tmp;
                pq.push(Elem(*it, tmp));
            }
        }
    }
}


void write_route()
{
    ofstream fout("vacanta.out");
    fout << totalTime << endl;
    // acum refacem traseul
    stack<int> road;
    int node = dest;
    while (node != src) {
        road.push(node);
        for (vi_t::iterator it = adjList[node].begin();
             it != adjList[node].end(); ++it) {
            if (dist[node] - timeList[node] -
                timeMat[node][*it] == dist[*it]) {
                node = *it;
                break;
            }
        }
    }
    road.push(src);
    while (!road.empty()) {
        fout << road.top() << ' ';
        road.pop();
    }
    fout << endl;
    fout.close();
}


int main()
{
    preprocess();
    process();
    write_route();
    return 0;
}
