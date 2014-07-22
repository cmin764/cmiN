#ifndef MULTIME_HPP_INCLUDED
#define MULTIME_HPP_INCLUDED


#include <iostream>
#include <vector>


using namespace std;


class Multime {

public:
    typedef vector<int> cont_type;

private:
    cont_type vec;

    friend Multime operator+(const Multime &, const Multime &);
    friend bool operator==(const Multime &, const Multime &);
    friend ostream& operator<<(ostream&, const Multime &);

public:
    Multime();
    Multime(const cont_type &);
    Multime(const Multime &);

    const cont_type & get_vec() const;

    bool operator+=(int);
    bool operator-=(int);
};


Multime operator+(const Multime &, const Multime &);
bool operator==(const Multime &, const Multime &);

ostream& operator<<(ostream&, const Multime &);


#endif // MULTIME_HPP_INCLUDED
