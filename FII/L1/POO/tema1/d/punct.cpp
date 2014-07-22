#include <iostream>
#include <utility>
#include <cmath>

#include "punct.hpp"


using namespace std;


const Punct Punct::Origine;
const Punct Punct::UnuZero(1);
const Punct Punct::ZeroUnu(0, 1);


Punct::Punct(int x, int y): x(x), y(y) {}
Punct::~Punct() {}


int Punct::GetX() const
{
    return x;
}

int Punct::GetY() const
{
    return y;
}

void Punct::MutaX(int x)
{
    this->x = x;
}

void Punct::MutaY(int y)
{
    this->y = y;
}

void Punct::MutaXY(int x, int y)
{
    MutaX(x);
    MutaY(y);
}

bool Punct::equals(const Punct& pct) const
{
    if (GetX() == pct.GetX() && GetY() == pct.GetY())
        return true;
    return false;
}

bool Punct::is_origin() const
{
    return equals(Punct::Origine);
}

void Punct::swaps(Punct& pct)
{
    int _x, _y;
    _x = GetX();
    _y = GetY();
    MutaXY(pct.GetX(), pct.GetY());
    pct.MutaXY(_x, _y);
}

double Punct::dist(const Punct& pct) const
{
    return sqrt(pow(GetX() - pct.GetX(), 2) +\
                pow(GetY() - pct.GetY(), 2));
}

Punct::corners_t Punct::rectangle(const Punct& upLeft,
                                  const Punct& downRight)
{
    /// Returns `upRight` and `downLeft`
    Punct::corners_t ret;
    // upRight
    ret.first.MutaXY(downRight.GetX(), upLeft.GetY());
    // downLeft
    ret.second.MutaXY(upLeft.GetX(), downRight.GetY());
    return ret;
}


ostream& operator<<(ostream& out, const Punct& pct)
{
    out << pct.GetX() << ' ' << pct.GetY() << endl;
    return out;
}


istream& operator>>(istream& in, Punct& pct)
{
    int x, y;
    in >> x >> y;
    pct.MutaXY(x, y);
    return in;
}


bool operator==(const Punct& pct1, const Punct& pct2)
{
    return pct1.equals(pct2);
}


bool operator!=(const Punct& pct1, const Punct& pct2)
{
    return !(pct1 == pct2);
}
