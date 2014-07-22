#ifndef TRIUNGHI_HPP_INCLUDED
#define TRIUNGHI_HPP_INCLUDED


#include <iostream>
#include <string>

#include "shape.hpp"
#include "punct.hpp"


using namespace std;


template <typename T=int, typename R=int>
class Triunghi;


template <typename T, typename R>
ostream &operator<< (ostream &, const Triunghi<T, R> &);


template <typename T, typename R>
class Triunghi: public Shape<T, R> {
private:
    Punct<T> p1, p2, p3;

public:
    static const string identifier;

    Triunghi(const Punct<T> & = Punct<T>(), const Punct<T> & = Punct<T>(),
             const Punct<T> & = Punct<T>());
    ~Triunghi();

    void output(ostream &) const;
    void cli(ostream &) const;
    void readFrom(istream &);

    void moveBy(T, T);

    string get_id() const;
    Punct<T> get_p1() const;
    Punct<T> get_p2() const;
    Punct<T> get_p3() const;

    bool operator==(const Shape<T, R> &) const;

    static Shape<T, R> * create();

    friend ostream &operator<< <T, R>(ostream &, const Triunghi<T, R> &);
};


#include "triunghi.cpp"


#endif // TRIUNGHI_HPP_INCLUDED
