#ifndef TRIUNGHI_HPP_INCLUDED
#define TRIUNGHI_HPP_INCLUDED


#include <iostream>

#include "punct.hpp"


using namespace std;


class Triunghi {

    Punct * a, * b, * c;
    bool valid;

    double edge_len(const Punct *, const Punct *) const;
    bool colin() const;
    void palloc();
    void pfree();

    friend ostream& operator<<(ostream&, const Triunghi&);
    friend istream& operator>>(istream&, Triunghi&);

public:
    Triunghi(const Punct * =NULL,
             const Punct * =NULL,
             const Punct * =NULL);
    ~Triunghi();

    const Punct & get_a() const;
    const Punct & get_b() const;
    const Punct & get_c() const;

    void set_a(const Punct *);
    void set_b(const Punct *);
    void set_c(const Punct *);

    double edge_ab() const;
    double edge_ac() const;
    double edge_bc() const;

    double perim() const;
    double area() const;

    bool is_straight() const;
};


ostream& operator<<(ostream&, const Triunghi&);
istream& operator>>(istream&, Triunghi&);

bool also(const Triunghi&, const Triunghi&);


#endif // TRIUNGHI_HPP_INCLUDED
