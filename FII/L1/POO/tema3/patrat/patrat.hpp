#ifndef PATRAT_HPP_INCLUDED
#define PATRAT_HPP_INCLUDED


#include "shape.hpp"
#include "dreptunghi.hpp"


class Patrat: public Dreptunghi /* public Shape, private Dreptunghi */ {

public:
    static const string identifier;

    Patrat(const Punct & = Punct(), const Punct & = Punct());
    ~Patrat();

    string get_id() const;

    bool operator==(const Shape &) const;

    static Shape * create();

    friend ostream & operator<<(ostream &, const Patrat &);
};


#endif // PATRAT_HPP_INCLUDED
