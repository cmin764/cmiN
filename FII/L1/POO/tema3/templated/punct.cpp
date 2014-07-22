#include <iostream>

#include "punct.hpp"


using namespace std;


template<typename T>
Punct<T>::Punct(T x, T y): x(x), y(y) {}

template<typename T>
Punct<T>::Punct(const Punct<T> & pnt): Punct(pnt.getX(), pnt.getY()) {}

template<typename T>
T Punct<T>::getX() const
{
    return x;
}

template<typename T>
T Punct<T>::getY() const
{
    return y;
}

template<typename T>
void Punct<T>::setX(T x)
{
    this->x = x;
}

template<typename T>
void Punct<T>::setY(T y)
{
    this->y = y;
}

template<typename T>
void Punct<T>::moveBy(T a, T b)
{
    setX(getX() + a);
    setY(getY() + b);
}

template<typename T>
bool Punct<T>::operator==(const Punct<T> & pnt) const
{
    if (x != pnt.getX() || y != pnt.getY())
        return false;
    return true;
}

template<typename T>
bool Punct<T>::operator!=(const Punct<T> & pnt) const
{
    return !(*this == pnt);
}

template<typename T>
istream & operator>>(std::istream & in, Punct<T> & punct)
{
    T x, y;
    in >> x >> y;
    punct.setX(x);
    punct.setY(y);
    return in;
}

template<typename T>
ostream &operator<<(std::ostream & out, const Punct<T> & punct)
{
    out << "Punct: " << punct.getX() << " " << punct.getY();
    return out;
}
