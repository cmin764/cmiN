#include <iostream>

#include "shape.hpp"
#include "patrat.hpp"


using namespace std;


const string Patrat::identifier = "patrat";

Patrat::Patrat(const Punct & p1, const Punct & p2): \
    Dreptunghi(p1, p2) {}

Patrat::~Patrat() {}

string Patrat::get_id() const
{
    return Patrat::identifier;
}

bool Patrat::operator==(const Shape & _shape) const
{
    if (get_id().compare(_shape.get_id()))
        return false;
    const Patrat & shape = static_cast<const Patrat &>(_shape);
    if (p1 != shape.get_p1() || p2 != shape.get_p2())
        return false;
    return true;
}

Shape * Patrat::create()
{
    return new Patrat();
}


ostream & operator<<(ostream & out, const Patrat & patrat)
{
    out << "Patrat avand coltul din stanga sus in punctul de coordonate " << \
           patrat.p1.getX() << ' ' << patrat.p1.getY() << " si coltul din dreapta jos in " << \
           patrat.p2.getX() << ' ' << patrat.p2.getY() << endl;
    return out;
}
