#ifndef GRUP_HPP_INCLUDED
#define GRUP_HPP_INCLUDED


#include <iostream>
#include <string>
#include <vector>

#include "shape.hpp"


class Grup: public Shape {

public:
    typedef vector<Shape *> vecshapepnt_t;

private:
    vecshapepnt_t continut;

public:
    static const string identifier;

    Grup();
    ~Grup();

    void add(Shape *);
    void remove(Shape *);

    void output(ostream &) const;
    void readFrom(istream &);

    void moveBy(int, int);

    string get_id() const;
    const vecshapepnt_t & get_continut() const;

    bool operator==(const Shape &) const;

    static Shape * create();

    friend ostream &operator<<(ostream &, const Grup &);
};


#endif // GRUP_HPP_INCLUDED
