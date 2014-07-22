#ifndef DREPTUNGHI_HPP_INCLUDED
#define DREPTUNGHI_HPP_INCLUDED


#include <iostream>
#include <istream>
#include <string>

#include "shape.hpp"
#include "punct.hpp"


using namespace std;


class Dreptunghi: public Shape {
private:
    Punct p1, p2;

public:
    static const string identifier;

    Dreptunghi(const Punct & = Punct(), const Punct & = Punct());
    ~Dreptunghi();

    void output(ostream &) const;
    void readFrom(istream &);

    void moveBy(int, int);

    string get_id() const;
    Punct get_p1() const;
    Punct get_p2() const;

    bool operator==(const Shape &) const;

    static Shape * create();

    void free_mem();

    friend ostream &operator<<(ostream &, const Dreptunghi &);
};


#endif // DREPTUNGHI_HPP_INCLUDED
