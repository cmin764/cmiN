#include <iostream>

#include "punct.hpp"


using namespace std;


Punct::Punct(int x, int y): x(x), y(y) {}

Punct::Punct(const Punct & pnt): Punct(pnt.getX(), pnt.getY()) {}

int Punct::getX() const
{
    return x;
}

int Punct::getY() const
{
    return y;
}

void Punct::setX(int x)
{
    this->x = x;
}

void Punct::setY(int y)
{
    this->y = y;
}

void Punct::moveBy(int a, int b)
{
    setX(getX() + a);
    setY(getY() + b);
}


istream &operator>>(std::istream & in, Punct & punct)
{
    int x, y;
    in >> x >> y;
    punct.setX(x);
    punct.setY(y);
    return in;
}

ostream &operator<<(std::ostream & out, const Punct & punct)
{
    out << "Punct: " << punct.getX() << " " << punct.getY();
    return out;
}
