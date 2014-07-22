#ifndef CERC_HPP_INCLUDED
#define CERC_HPP_INCLUDED


#include <iostream>
#include <string>

#include "shape.hpp"
#include "punct.hpp"


using namespace std;


template <typename T=int, typename R=int>
class Cerc;


template <typename T, typename R>
ostream &operator<< (ostream &, const Cerc<T, R> &);


template <typename T, typename R>
class Cerc: public Shape<T, R> {

private:
    Punct<T> pnt;
    R radius;

public:
    static const string identifier;

    Cerc(const Punct<T> & = Punct<T>(), const R = 0);
    ~Cerc();

    void output(ostream &) const;
    void cli(ostream &) const;
    void readFrom(istream &);
    void moveBy(T, T);

    string get_id() const;

    bool operator==(const Shape<T, R> &) const;

    static Shape<T, R> * create();

    Punct<T> get_pnt() const;
    R get_radius() const;

    friend ostream &operator<< <T, R>(ostream &, const Cerc<T, R> &);
};


#include "cerc.cpp"


#endif // CERC_HPP_INCLUDED
