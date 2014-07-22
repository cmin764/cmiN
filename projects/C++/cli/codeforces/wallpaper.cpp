#include <iostream>
#include <cstdio>
#include <vector>
#define N 500
#define MAX 0x7fFFffFF
using namespace std;


struct Chb {

    int len, wid, hei;
} tmpChb;


struct Wall {

    int len, wid, pri;
} tmpWall;


vector<Chb> chbVec;
vector<Wall> wallVec;
unsigned long long total;


inline int get_min(int len, int hei)
{
    int minCost = MAX;
    for (int i = 0; i < wallVec.size(); ++i) {
        int gain = (wallVec[i].len / hei) * wallVec[i].wid;
        if (!gain) continue;
        int rolls = len / gain;
        if (len % gain) ++rolls;
        int cost = rolls * wallVec[i].pri;
        if (cost < minCost) minCost = cost;
    }
    return minCost;
}


int main()
{
    int chbNr, wallNr;
    //freopen("b.in", "rt", stdin);
    cin >> chbNr;
    chbVec.reserve(chbNr);
    while (chbNr-- > 0) {
        cin >> tmpChb.len >> tmpChb.wid >> tmpChb.hei;
        chbVec.push_back(tmpChb);
    }
    cin >> wallNr;
    wallVec.reserve(wallNr);
    while (wallNr-- > 0) {
        cin >> tmpWall.len >> tmpWall.wid >> tmpWall.pri;
        wallVec.push_back(tmpWall);
    }
    for (int i = 0; i < chbVec.size(); ++i) {
        total += (unsigned long long)get_min(2 * (chbVec[i].len + chbVec[i].wid), chbVec[i].hei);
    }
    cout << total;
    return 0;
}
