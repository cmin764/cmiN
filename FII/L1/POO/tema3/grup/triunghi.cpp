#include <iostream>
#include <string>

#include "punct.hpp"
#include "triunghi.hpp"


using namespace std;


const string Triunghi::identifier = "triunghi";

Triunghi::Triunghi(const Punct & p1, const Punct & p2,
                   const Punct & p3): p1(p1), p2(p2), p3(p3) {}

Triunghi::~Triunghi() {}

void Triunghi::output(ostream & out) const
{
    out << p1.getX() << ' ' << p1.getY() << endl;
    out << p2.getX() << ' ' << p2.getY() << endl;
    out << p3.getX() << ' ' << p3.getY() << endl;
}

void Triunghi::readFrom(istream & in)
{
    int x, y;
    in >> x >> y;
    p1.setX(x); p1.setY(y);
    in >> x >> y;
    p2.setX(x); p2.setY(y);
    in >> x >> y;
    p3.setX(x); p3.setY(y);
}

void Triunghi::moveBy(int a, int b)
{
    p1.setX(p1.getX() + a); p1.setY(p1.getY() + b);
    p2.setX(p1.getX() + a); p2.setY(p1.getY() + b);
    p3.setX(p1.getX() + a); p3.setY(p1.getY() + b);
}

string Triunghi::get_id() const
{
    return Triunghi::identifier;
}

Punct Triunghi::get_p1() const
{
    return p1;
}

Punct Triunghi::get_p2() const
{
    return p2;
}

Punct Triunghi::get_p3() const
{
    return p3;
}

bool Triunghi::operator==(const Shape & _shape) const
{
    if (Triunghi::identifier.compare(_shape.get_id()))
        return false;
    const Triunghi & shape = static_cast<const Triunghi &>(_shape);
    if (p1 != shape.get_p1() || p2 != shape.get_p2() || p3 != shape.get_p3())
        return false;
    return true;
}


ostream & operator<<(ostream & out, const Triunghi & trg)
{
    out << "Triunghi format din punctele: " << trg.p1.getX() << ' ' << trg.p1.getY() \
        << " | " << trg.p2.getX() << ' ' << trg.p2.getY() << " | " << trg.p3.getX() \
        << ' ' << trg.p3.getY() << endl;
    return out;
}
