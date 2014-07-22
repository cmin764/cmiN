#include <iostream>
#include <istream>
#include <string>

#include "punct.hpp"
#include "dreptunghi.hpp"


using namespace std;


template <typename T, typename R>
const string Dreptunghi<T, R>::identifier = "dreptunghi";

template <typename T, typename R>
Dreptunghi<T, R>::Dreptunghi(const Punct<T> & p1, const Punct<T> & p2): p1(p1), p2(p2) {}

template <typename T, typename R>
Dreptunghi<T, R>::~Dreptunghi() {}

template <typename T, typename R>
void Dreptunghi<T, R>::output(ostream & out) const
{
    out << get_id() << endl;
    out << p1.getX() << ' ' << p1.getY() << endl;
    out << p2.getX() << ' ' << p2.getY() << endl;
}

template <typename T, typename R>
void Dreptunghi<T, R>::readFrom(istream & in)
{
    T x, y;
    in >> x >> y;
    p1.setX(x); p1.setY(y);
    in >> x >> y;
    p2.setX(x); p2.setY(y);
}

template <typename T, typename R>
void Dreptunghi<T, R>::moveBy(T a, T b)
{
    p1.setX(p1.getX() + a);
    p1.setY(p1.getY() + b);
    p2.setX(p2.getX() + a);
    p2.setY(p2.getY() + b);
}

template <typename T, typename R>
string Dreptunghi<T, R>::get_id() const
{
    return Dreptunghi<T, R>::identifier;
}

template <typename T, typename R>
Punct<T> Dreptunghi<T, R>::get_p1() const
{
    return p1;
}

template <typename T, typename R>
Punct<T> Dreptunghi<T, R>::get_p2() const
{
    return p2;
}

template <typename T, typename R>
bool Dreptunghi<T, R>::operator==(const Shape<T, R> & _shape) const
{
    if (get_id().compare(_shape.get_id()))
        return false;
    const Dreptunghi<T, R> & shape = static_cast<const Dreptunghi<T, R> &>(_shape);
    if (p1 != shape.get_p1() || p2 != shape.get_p2())
        return false;
    return true;
}

template <typename T, typename R>
Shape<T, R> * Dreptunghi<T, R>::create()
{
    return new Dreptunghi<T, R>();
}

template <typename T, typename R>
void Dreptunghi<T, R>::cli(ostream & out) const
{
    out << "Dreptunghi avand coltul din stanga sus in punctul de coordonate " << \
           p1.getX() << ' ' << p1.getY() << " si coltul din dreapta jos in " << \
           p2.getX() << ' ' << p2.getY() << endl;
}


template <typename T, typename R>
ostream &operator<<(ostream & out, const Dreptunghi<T, R> & drpt)
{
    drpt.cli(out);
    return out;
}
