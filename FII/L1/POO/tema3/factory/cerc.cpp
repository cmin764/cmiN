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
    out << Cerc::identifier << endl;
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

string Cerc::get_id() const
{
    return Cerc::identifier;
}

Punct Cerc::get_pnt() const
{
    return pnt;
}

int Cerc::get_radius() const
{
    return radius;
}

bool Cerc::operator==(const Shape & _shape) const
{
    if (Cerc::identifier.compare(_shape.get_id()))
        return false;
    const Cerc & shape = static_cast<const Cerc &>(_shape);
    if (pnt != shape.get_pnt() || radius != shape.get_radius())
        return false;
    return true;
}

Shape * Cerc::create()
{
    return new Cerc();
}

void Cerc::free_mem()
{
    delete this;
}


ostream &operator<<(ostream & out, const Cerc & cerc)
{
    out << "Cercul de raza " << cerc.radius << " avand centrul in " << \
           "punctul de coordonate " << cerc.pnt.getX() << ' ' << cerc.pnt.getY() << endl;
    return out;
}
