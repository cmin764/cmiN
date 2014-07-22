#ifndef TRIUNGHI_HPP_INCLUDED
#define TRIUNGHI_HPP_INCLUDED


#include <iostream>
#include <string>

#include "shape.hpp"
#include "punct.hpp"


using namespace std;


class Triunghi: public Shape {
private:
    Punct p1, p2, p3;

public:
    static const string identifier;

    Triunghi(const Punct & = Punct(), const Punct & = Punct(),
             const Punct & = Punct());
    ~Triunghi();

    void output(ostream &) const;
    void readFrom(istream &);

    void moveBy(int, int);

    friend ostream &operator<<(ostream &, const Triunghi &);
};


#endif // TRIUNGHI_HPP_INCLUDED
