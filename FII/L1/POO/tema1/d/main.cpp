#include <iostream>

#include "poligon.hpp"


using namespace std;


int main()
{
    Poligon plg;
    cin >> plg;
    cout << plg.get_area() << endl;
    cout << plg.is_convex() << endl;
    return 0;
}
