#include <iostream>

#include "shape.hpp"
#include "patrat.hpp"


using namespace std;


template <typename T, typename R>
const string Patrat<T, R>::identifier = "patrat";

template <typename T, typename R>
Patrat<T, R>::Patrat(const Punct<T> & p1, const Punct<T> & p2): \
    Dreptunghi<T, R>(p1, p2) {}

template <typename T, typename R>
Patrat<T, R>::~Patrat() {}

template <typename T, typename R>
string Patrat<T, R>::get_id() const
{
    return Patrat<T, R>::identifier;
}

template <typename T, typename R>
bool Patrat<T, R>::operator==(const Shape<T, R> & _shape) const
{
    if (get_id().compare(_shape.get_id()))
        return false;
    const Patrat<T, R> & shape = static_cast<const Patrat<T, R> &>(_shape);
    if (Dreptunghi<T, R>::p1 != shape.get_p1() || Dreptunghi<T, R>::p2 != shape.get_p2())
        return false;
    return true;
}

template <typename T, typename R>
Shape<T, R> * Patrat<T, R>::create()
{
    return new Patrat<T, R>();
}

template <typename T, typename R>
void Patrat<T, R>::cli(ostream & out) const
{
     out << "Patrat avand coltul din stanga sus in punctul de coordonate " << \
           Dreptunghi<T, R>::p1.getX() << ' ' << Dreptunghi<T, R>::p1.getY() << " si coltul din dreapta jos in " << \
           Dreptunghi<T, R>::p2.getX() << ' ' << Dreptunghi<T, R>::p2.getY() << endl;
}


template <typename T, typename R>
ostream & operator<<(ostream & out, const Patrat<T, R> & patrat)
{
    patrat.cli(out);
    return out;
}
