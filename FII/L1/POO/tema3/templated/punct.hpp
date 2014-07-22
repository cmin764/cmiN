#ifndef PUNCT_H_INCLUDED
#define PUNCT_H_INCLUDED


#include <iostream>


using namespace std;


template <typename T=int>
class Punct;


template <typename T>
istream &operator>>(istream &, Punct<T> &);

template <typename T>
ostream &operator<<(ostream &, const Punct<T> &);


template <typename T>
class Punct {

private:
    T x, y;

public:
    Punct(T = 0, T = 0);
    Punct(const Punct<T> &);

    T getX() const;
    T getY() const;

    void setX(T);
    void setY(T);

    void moveBy(T, T);

    bool operator==(const Punct<T> &) const;
    bool operator!=(const Punct<T> &) const;

    friend istream &operator>> <T>(istream &, Punct<T> &);
    friend ostream &operator<< <T>(ostream &, const Punct<T> &);
};


#include "punct.cpp"

#endif // PUNCT_H_INCLUDED
