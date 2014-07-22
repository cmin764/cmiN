#include <iostream>
#include <cmath>
#include <cfloat>

#include "triunghi.hpp"
#include "punct.hpp"


#define zero(x, y) (fabs((x)-(y)) < FLT_EPSILON)


using namespace std;


Triunghi::Triunghi(const Punct * a,
                   const Punct * b,
                   const Punct * c)
{
    palloc();
    if (a && b && c) {
        *(this->a) = *a;
        *(this->b) = *b;
        *(this->c) = *c;
        valid = !colin();
    } else
        valid = false;
}

Triunghi::~Triunghi()
{
    pfree();
}

void Triunghi::palloc()
{
    a = new Punct();
    b = new Punct();
    c = new Punct();
}

void Triunghi::pfree()
{
    delete a;
    delete b;
    delete c;
}

double Triunghi::edge_len(const Punct * first,
                          const Punct * second) const
{
    return first->dist(*second);
}

bool Triunghi::colin() const
{
    double ab = edge_ab();
    double ac = edge_ac();
    double bc = edge_bc();

    if (ab == ac + bc || ac == ab + bc || bc == ab + ac)
        return true;
    return false;
}

const Punct & Triunghi::get_a() const
{
    return *a;
}

const Punct & Triunghi::get_b() const
{
    return *b;
}

const Punct & Triunghi::get_c() const
{
    return *c;
}

void Triunghi::set_a(const Punct * a)
{
    *(this->a) = *a;
}

void Triunghi::set_b(const Punct * b)
{
    *(this->b) = *b;
}

void Triunghi::set_c(const Punct * c)
{
    *(this->c) = *c;
}

double Triunghi::edge_ab() const
{
    if (!valid)
        return -1;
    return edge_len(a, b);
}

double Triunghi::edge_ac() const
{
    if (!valid)
        return -1;
    return edge_len(a, c);
}

double Triunghi::edge_bc() const
{
    if (!valid)
        return -1;
    return edge_len(b, c);
}

double Triunghi::perim() const
{
    if (!valid)
        return -1;
    return edge_ab() + edge_ac() + edge_bc();
}

double Triunghi::area() const
{
    if (!valid)
        return -1;
    double p = perim() / 2;
    double a = edge_bc(), b = edge_ac(), c = edge_ab();
    // Heron rocks ^^
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

bool Triunghi::is_straight() const
{
    if (!valid)
        return -1;
    /* a^2 = b^2 + c^2 - 2*b*c*cos(A)
       A=pi/2 -> cos(A)=0 -> a^2 = b^2 + c^2 (Pitagora) */
    double x = pow(edge_bc(), 2);
    double y = pow(edge_ac(), 2);
    double z = pow(edge_ab(), 2);
    if (zero(x, (y+z)))
        return true;
    if (zero(y, (x+z)))
        return true;
    if (zero(z, (x+y)))
        return true;
    return false;
}


ostream& operator<<(ostream& out, const Triunghi& trg)
{
    if (trg.valid)
        out << trg.get_a() << trg.get_b() << trg.get_c();
    else
        out << "Invalid" << endl;
    return out;
}

istream& operator>>(istream& in, Triunghi& trg)
{
    in >> *trg.a >> *trg.b >> *trg.c;
    trg.valid = !trg.colin();
    return in;
}

bool also(const Triunghi& trg1, const Triunghi& trg2)
{
    double a1, b1, c1, a2, b2, c2;

    a1 = trg1.edge_bc();
    b1 = trg1.edge_ac();
    c1 = trg1.edge_ab();

    a2 = trg2.edge_bc();
    b2 = trg2.edge_ac();
    c2 = trg2.edge_ab();

    if ((zero(a1 / a2, b1 / b2) && zero(b1 / b2, c1 / c2)) ||
        (zero(a1 / a2, b1 / c2) && zero(b1 / c2, c1 / b2)) ||
        (zero(a1 / b2, b1 / a2) && zero(b1 / a2, c1 / c2)) ||
        (zero(a1 / b2, b1 / c2) && zero(b1 / c2, c1 / a2)) ||
        (zero(a1 / c2, b1 / a2) && zero(b1 / a2, c1 / b2)) ||
        (zero(a1 / c2, b1 / b2) && zero(b1 / b2, c1 / a2)))
            return true;

    return false;
}
