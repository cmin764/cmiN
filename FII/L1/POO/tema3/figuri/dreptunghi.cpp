#include <iostream>
#include <istream>
#include <string>

#include "punct.hpp"
#include "dreptunghi.hpp"


using namespace std;


const string Dreptunghi::identifier = "dreptunghi";

Dreptunghi::Dreptunghi(const Punct & p1, const Punct & p2): p1(p1), p2(p2) {}

Dreptunghi::~Dreptunghi() {}

void Dreptunghi::output(ostream & out) const
{
    out << p1.getX() << ' ' << p1.getY() << endl;
    out << p2.getX() << ' ' << p2.getY() << endl;
}

void Dreptunghi::readFrom(istream & in)
{
    int x, y;
    in >> x >> y;
    p1.setX(x); p1.setY(y);
    in >> x >> y;
    p2.setX(x); p2.setY(y);
}

void Dreptunghi::moveBy(int a, int b)
{
    p1.setX(p1.getX() + a);
    p1.setY(p1.getY() + b);
    p2.setX(p2.getX() + a);
    p2.setY(p2.getY() + b);
}


ostream &operator<<(ostream & out, const Dreptunghi & drpt)
{
    out << "Dreptunghi avand coltul din stanga sus in punctul de coordonate " << \
           drpt.p1.getX() << ' ' << drpt.p1.getY() << " si coltul din dreapta jos in" << \
           drpt.p2.getX() << ' ' << drpt.p2.getY() << endl;
    return out;
}
