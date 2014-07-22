#include <iostream>

#include "shape.hpp"


#define DBG 1


using namespace std;


Shape::~Shape()
{
    #if DBG
    cerr << "Shape destroyed" << endl;
    #endif
}
