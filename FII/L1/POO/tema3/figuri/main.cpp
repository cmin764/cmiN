#include <iostream>

#include "punct.hpp"
#include "shape.hpp"
#include "triunghi.hpp"


using namespace std;


int main()
{
    Punct p1(1, 2), p2, p3(3, 4);
    Shape * pTr = new Triunghi(p1, p2, p3);
    pTr->output(cout);
    delete pTr;
    return 0;
}
