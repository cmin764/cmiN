#include <iostream>
#include <vector>
#include <iterator>

#include "punct.hpp"
#include "triunghi.hpp"
#include "poligon.hpp"


using namespace std;


Poligon::Poligon() {}

Poligon::Poligon(const Poligon::cont_type & vec)
{
    this->vec.clear();
    this->vec.assign(vec.cbegin(), vec.cend());
}

double Poligon::get_area() const
{
    if (vec.size() < 3)
        return -1;
    int gx = 0, gy = 0;
    for (Poligon::cont_type::const_iterator it = vec.cbegin();
         it != vec.cend(); ++it) {
        gx += it->GetX();
        gy += it->GetY();
    }
    Punct gspot(gx / vec.size(), gy / vec.size());

    double totalArea = 0;
    Poligon::cont_type::const_iterator fit = vec.cend();
    advance(fit, -1);
    for (Poligon::cont_type::const_iterator it = vec.cbegin();
         it != fit; ++it) {
        Poligon::cont_type::const_iterator _it = it;
        advance(_it, 1);
        Triunghi trg(&*it, &*_it, &gspot);
        totalArea += trg.area();
    }
    Triunghi trg(&vec.front(), &vec.back(), &gspot);
    totalArea += trg.area();
    return totalArea;
}


static double cross_prod(double Ax, double Ay, double Bx, double By,
                         double Cx, double Cy)
{
    // not mine
    float BAx = Ax - Bx;
    float BAy = Ay - By;
    float BCx = Cx - Bx;
    float BCy = Cy - By;

    return (BAx * BCy - BAy * BCx);
}


bool Poligon::is_convex() const
{
    bool negative = false;
    bool positive = false;
    int nr = vec.size();
    if (nr < 3)
        return false;
    for (int i = 0, j, k; i < nr; ++i) {
        j = (i + 1) % nr;
        k = (j + 1) % nr;
        double res = cross_prod(vec[i].GetX(), vec[i].GetY(),
                                vec[j].GetX(), vec[j].GetY(),
                                vec[k].GetX(), vec[k].GetY());
        if (res < 0)
            negative = true;
        else if (res > 0)
            positive = true;
        if (negative && positive)
            return false;
    }
    return true;
}


ostream & operator<<(ostream & out, const Poligon & plg)
{
    for (Poligon::cont_type::const_iterator it = plg.vec.cbegin();
         it != plg.vec.cend(); ++it) {
        out << *it;
    }
    return out;
}

istream & operator>>(istream & in, Poligon & plg)
{
    int nr;
    cin >> nr;
    plg.vec.resize(nr);
    for (int i = 0; i < nr; ++i) {
        Punct tmp;
        cin >> tmp;
        plg.vec[i].swaps(tmp);
    }
    return in;
}
