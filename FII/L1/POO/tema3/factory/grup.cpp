#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "punct.hpp"
#include "shape.hpp"
#include "cerc.hpp"
#include "triunghi.hpp"
#include "dreptunghi.hpp"
#include "grup.hpp"
#include "shapefactory.hpp"


const string Grup::identifier = "grup";

Grup::Grup() {}

Grup::~Grup() {}

string Grup::get_id() const
{
    return Grup::identifier;
}

const Grup::vecshapepnt_t & Grup::get_continut() const
{
    return continut;
}

void Grup::add(Shape * shape)
{
    continut.push_back(shape);
}

void Grup::remove(Shape * shape)
{
    for (Grup::vecshapepnt_t::iterator it = continut.begin();
         it != continut.end(); ++it) {
        if (**it == *shape) {
            continut.erase(it);
            break;
        }
    }
}

void Grup::output(ostream & out) const
{
    out << Grup::identifier << ' ' << continut.size() << endl;
    for (Grup::vecshapepnt_t::const_iterator cit = continut.cbegin();
         cit != continut.cend(); ++cit)
        (*cit)->output(out);
}

void Grup::readFrom(istream & in)
{
    int nr;
    in >> nr;
    ShapeFactory * factory = ShapeFactory::get_instance();
    while (nr--) {
        Shape * pshp = factory->create_shape(in);
        pshp->readFrom(in);
        add(pshp);
    }
}

class MoveBy {

    int a, b;

public:
    MoveBy(int a = 0, int b = 0): a(a), b(b) {}

    void operator()(Shape * pshp)
    {
        pshp->moveBy(a, b);
    }
};

void Grup::moveBy(int a, int b)
{
    MoveBy moveby(a, b);
    for_each(continut.begin(), continut.end(), moveby);
}

inline bool _comp(Shape * a, Shape * b)
{
    return *a == *b;
}

bool Grup::operator==(const Shape & _shape) const
{
    if (Grup::identifier.compare(_shape.get_id()))
        return false;
    const Grup & shape = static_cast<const Grup &>(_shape);
    if (continut.size() != shape.get_continut().size())
        return false;
    return equal(continut.cbegin(), continut.cend(),
                 shape.get_continut().cbegin(), _comp);
}

Shape * Grup::create()
{
    return new Grup();
}

void Grup::free_mem()
{
    delete this;
}


ostream &operator<<(ostream & out, const Grup & grup)
{
    for (Grup::vecshapepnt_t::const_iterator cit = grup.continut.cbegin();
         cit != grup.continut.cend(); ++cit)
        cout << (**cit);
    return out;
}
