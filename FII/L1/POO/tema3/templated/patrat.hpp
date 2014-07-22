#ifndef PATRAT_HPP_INCLUDED
#define PATRAT_HPP_INCLUDED


#include "shape.hpp"
#include "dreptunghi.hpp"


template <typename T=int, typename R=int>
class Patrat;


template <typename T, typename R>
ostream & operator<<(ostream &, const Patrat<T, R> &);


template <typename T, typename R>
class Patrat: public Dreptunghi<T, R> /* public Shape<T>, private Dreptunghi<T> */ {

public:
    static const string identifier;

    Patrat(const Punct<T> & = Punct<T>(), const Punct<T> & = Punct<T>());
    ~Patrat();

    string get_id() const;
    void cli(ostream &) const;

    bool operator==(const Shape<T, R> &) const;

    static Shape<T, R> * create();

    friend ostream & operator<< <T, R>(ostream &, const Patrat<T, R> &);
};


#include "patrat.cpp"


#endif // PATRAT_HPP_INCLUDED
