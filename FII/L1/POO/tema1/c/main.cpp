#include <iostream>

#include "triunghi.hpp"


using namespace std;


int main()
{
    Punct a(0, 0), b(4, 0), c(4, 6);
    Triunghi trg1(&a, &b, &c), trg2;
    cin >> trg2;
    cout << trg1.perim() << endl;
    cout << trg1.area() << endl;
    cout << trg1.is_straight() << endl;
    cout << also(trg1, trg2);
    return 0;
}
