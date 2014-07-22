#include <iostream>
#include <cmath>

#include "complex.hpp"


using namespace std;


Complex::Complex(double re, double im): re(re), im(im) {}

double Complex::real() const
{
    return re;
}

double Complex::imag() const
{
    return im;
}

double Complex::modul() const
{
    return sqrt(pow(real(), 2) + pow(imag(), 2));
}

void Complex::modificaRe(double re)
{
    this->re = re;
}

void Complex::modificaIm(double im)
{
    this->im = im;
}

void Complex::modifica(double re, double im)
{
    this->re = re;
    this->im = im;
}

double Complex::distanta(const Complex& nr1, const Complex& nr2)
{
    return sqrt(pow(nr1.real() - nr2.real(), 2) +\
                pow(nr1.imag() - nr2.imag(), 2));
}

double Complex::distanta(const Complex& nr) const
{
    return Complex::distanta(*this, nr);
}

Complex& Complex::operator+=(const Complex& nr)
{
    modifica(real() + nr.real(), imag() + nr.imag());
    return *this;
}

Complex& Complex::operator+=(double nr)
{
    return (*this) += Complex(nr);
}

Complex& Complex::operator*=(const Complex& nr)
{
    modifica(real() * nr.real() - imag() * nr.imag(),
             real() * nr.imag() + imag() * nr.real());
    return *this;
}

Complex& Complex::operator*=(double nr)
{
    return (*this) *= Complex(nr);
}


ostream& operator<<(ostream& out, const Complex& nr)
{
    out << nr.real();
    if (nr.imag()) {
        if (nr.imag() > 0)
            out << "+";
        out << nr.imag() << "i";
    }
    return out;
}


istream& operator>>(istream& in, Complex& nr)
{
    double re, im;
    in >> re >> im;
    nr.modifica(re, im);
    return in;
}

const Complex operator+(const Complex& nr1, const Complex& nr2)
{
    return Complex(nr1.real() + nr2.real(), nr1.imag() + nr1.imag());
}


const Complex operator*(const Complex& nr, double n)
{
    return Complex(nr.real() * n, nr.imag() * n);
}


const Complex operator*(double n, const Complex& nr)
{
    return nr * n;
}


bool operator==(const Complex& nr1, const Complex& nr2)
{
    return nr1.real() == nr2.real() && nr1.imag() == nr1.imag();
}


bool operator!=(const Complex& nr1, const Complex& nr2)
{
    return !(nr1 == nr2);
}
