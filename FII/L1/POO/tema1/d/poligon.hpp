#ifndef POLIGON_HPP_INCLUDED
#define POLIGON_HPP_INCLUDED


#include <iostream>
#include <vector>

#include "punct.hpp"


using namespace std;


class Poligon {

public:
    typedef vector<Punct> cont_type;

private:
    cont_type vec;

    friend ostream & operator<<(ostream &, const Poligon &);
    friend istream & operator>>(istream &, Poligon &);

public:
    Poligon();
    Poligon(const cont_type &);

    double get_area() const;
    bool is_convex() const;
};


ostream & operator<<(ostream &, const Poligon &);
istream & operator>>(istream &, Poligon &);


#endif // POLIGON_HPP_INCLUDED
