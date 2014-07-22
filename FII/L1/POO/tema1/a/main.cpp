#include <iostream>

#include "complex.hpp"


using namespace std;


int main()
{
    Complex nr1(5, 3), nr2;
    cin >> nr2;
    nr1 += nr2;
    nr1 *= nr2;
    cout << nr1 * 10;
    return 0;
}
