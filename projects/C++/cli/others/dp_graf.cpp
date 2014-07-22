#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;


const int T = 5001, N = 101;
int maxMoney, startNode, nodes, edges, time, win[N], mat[T][N][N];
vector<vector<pair<int, int> > > adjacent;


void parse_input()
{
    cin >> nodes >> edges >> startNode >> time;
    for (int i = 1; i <= nodes; ++i) cin >> win[i]; // money gain for node i
    adjacent.resize(nodes + 1);
    for (int i = 0; i < edges; ++i) {
        int t, x, y;
        cin >> t >> x >> y; // t time between x and y
        adjacent[x].push_back(make_pair(y, t));
        adjacent[y].push_back(make_pair(x, t));
    }
}


void solve()
{
    /** O(TN^2) */
    maxMoney = win[startNode]; // atribuim maximului castigul de start
    mat[0][startNode][0] = maxMoney; // la momentul de timp t=0 initializam nodul de start
    mat[0][startNode][startNode] = 1; // marcam ca este vizitat in lantul curent
    for (int i = 0; i < time; ++i) { // pentru fiecare moment de timp
        for (int j = 1; j <= nodes; ++j) { // luam fiecare nod
            if (mat[i][j][0]) { // si daca s-a putut ajunge in el (avand suma strict pozitiva)
                for (int k = 0; k < adjacent[j].size(); ++k) { // luam fiecare vecin al lui
                    int tmpTime = i + adjacent[j][k].second; // aflam noul timp pentru vizita vecinului
                    int tmpMoney = mat[i][j][0]; // clonam suma de la care pornim vizita
                    if (!mat[i][j][adjacent[j][k].first]) { // daca nu a mai fost vizitat acel vecin
                        tmpMoney += win[adjacent[j][k].first]; // actualizam suma
                    } // apoi daca vizita intra in timp si obtinem o suma mai buna de bani
                    if (tmpTime <= time && tmpMoney > mat[tmpTime][adjacent[j][k].first][0]) {
                        if (tmpMoney > maxMoney) maxMoney = tmpMoney; // actualizam maximul
                        mat[tmpTime][adjacent[j][k].first][0] = tmpMoney; // evenimentul in matrice
                        for (int l = 1; l <= nodes; ++l) { // dar si lantul de noduri vizitate
                            mat[tmpTime][adjacent[j][k].first][l] = mat[i][j][l];
                            mat[tmpTime][adjacent[j][k].first][adjacent[j][k].first] = 1;
                        }
                    }
                }
            }
        }
    }
}


int main()
{
    freopen("dp_graf.in", "rt", stdin); // switch input source
    parse_input();
    solve();
    cout << maxMoney;
    return 0;
}
