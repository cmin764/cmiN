#ifndef SHAPE_HPP_INCLUDED
#define SHAPE_HPP_INCLUDED


#include <iostream>


using namespace std;


class Shape {

public:
    virtual void output(ostream &) const = 0;
    virtual void moveBy(int, int) = 0;
    virtual void readFrom(istream &) = 0;
    virtual ~Shape() = 0;

    friend ostream &operator<<(ostream &, const Shape &);
};


#endif // SHAPE_HPP_INCLUDED
