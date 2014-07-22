#include <iostream>
#include <string>

#include "punct.hpp"
#include "triunghi.hpp"


using namespace std;


template <typename T, typename R>
const string Triunghi<T, R>::identifier = "triunghi";

template <typename T, typename R>
Triunghi<T, R>::Triunghi(const Punct<T> & p1, const Punct<T> & p2,
                         const Punct<T> & p3): p1(p1), p2(p2), p3(p3) {}

template <typename T, typename R>
Triunghi<T, R>::~Triunghi() {}

template <typename T, typename R>
void Triunghi<T, R>::output(ostream & out) const
{
    out << get_id() << endl;
    out << p1.getX() << ' ' << p1.getY() << endl;
    out << p2.getX() << ' ' << p2.getY() << endl;
    out << p3.getX() << ' ' << p3.getY() << endl;
}

template <typename T, typename R>
void Triunghi<T, R>::readFrom(istream & in)
{
    T x, y;
    in >> x >> y;
    p1.setX(x); p1.setY(y);
    in >> x >> y;
    p2.setX(x); p2.setY(y);
    in >> x >> y;
    p3.setX(x); p3.setY(y);
}

template <typename T, typename R>
void Triunghi<T, R>::moveBy(T a, T b)
{
    p1.setX(p1.getX() + a); p1.setY(p1.getY() + b);
    p2.setX(p1.getX() + a); p2.setY(p1.getY() + b);
    p3.setX(p1.getX() + a); p3.setY(p1.getY() + b);
}

template <typename T, typename R>
string Triunghi<T, R>::get_id() const
{
    return Triunghi<T, R>::identifier;
}

template <typename T, typename R>
Punct<T> Triunghi<T, R>::get_p1() const
{
    return p1;
}

template <typename T, typename R>
Punct<T> Triunghi<T, R>::get_p2() const
{
    return p2;
}

template <typename T, typename R>
Punct<T> Triunghi<T, R>::get_p3() const
{
    return p3;
}

template <typename T, typename R>
bool Triunghi<T, R>::operator==(const Shape<T, R> & _shape) const
{
    if (get_id().compare(_shape.get_id()))
        return false;
    const Triunghi<T, R> & shape = static_cast<const Triunghi<T, R> &>(_shape);
    if (p1 != shape.get_p1() || p2 != shape.get_p2() || p3 != shape.get_p3())
        return false;
    return true;
}

template <typename T, typename R>
Shape<T, R> * Triunghi<T, R>::create()
{
    return new Triunghi<T, R>();
}

template <typename T, typename R>
void Triunghi<T, R>::cli(ostream & out) const
{
    out << "Triunghi format din punctele: " << p1.getX() << ' ' << p1.getY() \
        << " | " << p2.getX() << ' ' << p2.getY() << " | " << p3.getX() \
        << ' ' << p3.getY() << endl;
}


template <typename T, typename R>
ostream & operator<<(ostream & out, const Triunghi<T, R> & trg)
{
    trg.cli(out);
    return out;
}
