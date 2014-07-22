#include <iostream>

#include "punct.hpp"


using namespace std;


int main()
{
    Punct pct1, pct2;
    cin >> pct2;
    cout << pct1 << pct2;
    cout << pct1.is_origin() << endl;
    cout << pct1.equals(pct2) << endl;
    Punct::corners_t corners = Punct::rectangle(pct1, pct2);
    cout << corners.first.GetX() << ' ' << corners.first.GetY() << endl;
    cout << corners.second.GetX() << ' ' << corners.second.GetY() << endl;
    cout << pct1.dist(pct2);
    return 0;
}
