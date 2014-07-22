#ifndef GRUP_HPP_INCLUDED
#define GRUP_HPP_INCLUDED


#include <iostream>
#include <string>
#include <vector>

#include "shape.hpp"


template <typename T=int, typename R=int>
class Grup;


template <typename T, typename R>
ostream & operator<<(ostream &, const Grup<T, R> &);


template <typename T, typename R>
class Grup: public Shape<T, R> {

public:
    typedef vector<Shape<T, R> *> vecshapepnt_t;

private:
    vecshapepnt_t continut;

public:
    static const string identifier;

    Grup();
    ~Grup();

    void add(Shape<T, R> *);
    void remove(Shape<T, R> *);

    void output(ostream &) const;
    void cli(ostream &) const;
    void readFrom(istream &);

    void moveBy(T, T);

    string get_id() const;
    const vecshapepnt_t & get_continut() const;

    bool operator==(const Shape<T, R> &) const;

    static Shape<T, R> * create();

    friend ostream &operator<< <T, R>(ostream &, const Grup<T, R> &);
};


#include "grup.cpp"


#endif // GRUP_HPP_INCLUDED
