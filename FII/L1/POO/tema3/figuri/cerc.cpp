#include <iostream>
#include <string>

#include "punct.hpp"
#include "cerc.hpp"


using namespace std;


const string Cerc::identifier = "cerc";

Cerc::Cerc(const Punct & pnt, const int radius): pnt(pnt), radius(radius) {}

Cerc::~Cerc() {}

void Cerc::output(ostream & out) const
{
    out << pnt.getX() << ' ' << pnt.getY() << endl;
    out << radius << endl;
}

void Cerc::readFrom(istream & in)
{
    int x, y, r;
    in >> x >> y >> r;
    pnt.setX(x);
    pnt.setY(y);
    radius = r;
}

void Cerc::moveBy(int a, int b)
{
    pnt.setX(pnt.getX() + a);
    pnt.setY(pnt.getY() + b);
}


ostream &operator<<(ostream & out, const Cerc & cerc)
{
    out << "Cercul de raza " << cerc.radius << " avand centrul in " << \
           "punctul de coordonate " << cerc.pnt.getX() << ' ' << cerc.pnt.getY() << endl;
    return out;
}
