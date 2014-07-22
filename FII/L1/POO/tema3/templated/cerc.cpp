#include <iostream>
#include <string>

#include "punct.hpp"
#include "cerc.hpp"


using namespace std;


template <typename T, typename R>
const string Cerc<T, R>::identifier = "cerc";

template <typename T, typename R>
Cerc<T, R>::Cerc(const Punct<T> & pnt, const R radius): pnt(pnt), radius(radius) {}

template <typename T, typename R>
Cerc<T, R>::~Cerc() {}

template <typename T, typename R>
void Cerc<T, R>::output(ostream & out) const
{
    out << get_id() << endl;
    out << pnt.getX() << ' ' << pnt.getY() << endl;
    out << radius << endl;
}

template <typename T, typename R>
void Cerc<T, R>::readFrom(istream & in)
{
    T x, y;
    R r;
    in >> x >> y >> r;
    pnt.setX(x);
    pnt.setY(y);
    radius = r;
}

template <typename T, typename R>
void Cerc<T, R>::moveBy(T a, T b)
{
    pnt.setX(pnt.getX() + a);
    pnt.setY(pnt.getY() + b);
}

template <typename T, typename R>
string Cerc<T, R>::get_id() const
{
    return Cerc<T, R>::identifier;
}

template <typename T, typename R>
Punct<T> Cerc<T, R>::get_pnt() const
{
    return pnt;
}

template <typename T, typename R>
R Cerc<T, R>::get_radius() const
{
    return radius;
}

template <typename T, typename R>
bool Cerc<T, R>::operator==(const Shape<T, R> & _shape) const
{
    if (get_id().compare(_shape.get_id()))
        return false;
    const Cerc<T, R> & shape = static_cast<const Cerc<T, R> &>(_shape);
    if (pnt != shape.get_pnt() || radius != shape.get_radius())
        return false;
    return true;
}

template <typename T, typename R>
Shape<T, R> * Cerc<T, R>::create()
{
    return new Cerc<T, R>();
}

template <typename T, typename R>
void Cerc<T, R>::cli(ostream & out) const
{
    out << "Cercul de raza " << radius << " avand centrul in " << \
           "punctul de coordonate " << pnt.getX() << ' ' << pnt.getY() << endl;
}


template <typename T, typename R>
ostream &operator<<(ostream & out, const Cerc<T, R> & cerc)
{
    cerc.cli(out);
    return out;
}
