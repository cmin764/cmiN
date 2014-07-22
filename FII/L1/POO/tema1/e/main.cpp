#include <iostream>

#include "multime.hpp"


using namespace std;


int main()
{
    int _vec[] = {1, 3, 9};
    Multime::cont_type vec(_vec, _vec + 3);

    Multime mul1(vec);
    cout << (mul1 += 2) << endl;    // keep sorted
    cout << (mul1 += 1) << endl;    // no duplicates
    cout << mul1;

    Multime mul2(mul1);
    cout << mul2;
    cout << (mul2 -= 0) << endl;
    cout << (mul2 -= 1) << endl;
    cout << (mul1 -= 1) << endl;

    cout << (mul1 == mul2) << endl;

    return 0;
}
