#ifndef COMPLEX_HPP_INCLUDED
#define COMPLEX_HPP_INCLUDED


#include <iostream>


using namespace std;


class Complex {

    double re;
    double im;

public:
    Complex(double=0, double=0);

    double real() const;
    double imag() const;
    double modul() const;

    void modificaRe(double=0);
    void modificaIm(double=0);
    void modifica(double=0, double=0);

    static double distanta(const Complex&, const Complex&);

    double distanta(const Complex&) const;

    Complex& operator+=(const Complex&);
    Complex& operator+=(double);

    Complex& operator*=(const Complex&);
    Complex& operator*=(double);
};


ostream& operator<<(ostream&, const Complex&);
istream& operator>>(istream&, Complex&);

const Complex operator+(const Complex&, const Complex&);
const Complex operator*(const Complex&, double);
const Complex operator*(double, const Complex&);

bool operator==(const Complex&, const Complex&);
bool operator!=(const Complex&, const Complex&);


#endif // COMPLEX_HPP_INCLUDED
