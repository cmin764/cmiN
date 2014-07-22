#ifndef CERC_HPP_INCLUDED
#define CERC_HPP_INCLUDED


#include <iostream>
#include <string>

#include "shape.hpp"
#include "punct.hpp"


using namespace std;


class Cerc: public Shape {

private:
    Punct pnt;
    int radius;

public:
    static const string identifier;

    Cerc(const Punct & = Punct(), const int = 0);
    ~Cerc();

    void output(ostream &) const;
    void readFrom(istream &);
    void moveBy(int, int);

    friend ostream &operator<<(ostream &, const Cerc &);
};


#endif // CERC_HPP_INCLUDED
