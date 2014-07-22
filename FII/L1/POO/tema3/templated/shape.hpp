#ifndef SHAPE_HPP_INCLUDED
#define SHAPE_HPP_INCLUDED


#include <iostream>
#include <string>


using namespace std;


template<typename T=int, typename R=int>
class Shape;


template<typename T, typename R>
ostream & operator<< (ostream &, const Shape<T, R> &);


template<typename T, typename R>
class Shape {

public:
    virtual void output(ostream &) const = 0;
    virtual void cli(ostream &) const = 0;
    virtual void moveBy(T, T) = 0;
    virtual void readFrom(istream &) = 0;
    virtual ~Shape() = 0;

    virtual bool operator==(const Shape<T, R> &) const = 0;

    virtual string get_id() const = 0;

    virtual void free_mem();

    friend ostream & operator<< <T, R>(ostream &, const Shape<T, R> &);
};


#include "shape.cpp"


#endif // SHAPE_HPP_INCLUDED
