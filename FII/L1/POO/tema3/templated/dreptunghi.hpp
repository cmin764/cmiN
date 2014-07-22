#ifndef DREPTUNGHI_HPP_INCLUDED
#define DREPTUNGHI_HPP_INCLUDED


#include <iostream>
#include <istream>
#include <string>

#include "shape.hpp"
#include "punct.hpp"


using namespace std;


template <typename T=int, typename R=int>
class Dreptunghi;


template <typename T, typename R>
ostream & operator<<(ostream &, const Dreptunghi<T, R> &);


template <typename T, typename R>
class Dreptunghi: public Shape<T, R> {

protected:
    Punct<T> p1, p2;

public:
    static const string identifier;

    Dreptunghi(const Punct<T> & = Punct<T>(), const Punct<T> & = Punct<T>());
    ~Dreptunghi();

    void output(ostream &) const;
    void cli(ostream &) const;
    void readFrom(istream &);

    void moveBy(T, T);

    virtual string get_id() const;
    Punct<T> get_p1() const;
    Punct<T> get_p2() const;

    virtual bool operator==(const Shape<T, R> &) const;

    static Shape<T, R> * create();

    friend ostream & operator<< <T>(ostream &, const Dreptunghi<T, R> &);
};


#include "dreptunghi.cpp"


#endif // DREPTUNGHI_HPP_INCLUDED
