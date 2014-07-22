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


template <typename T, typename R>
const string Grup<T, R>::identifier = "grup";

template <typename T, typename R>
Grup<T, R>::Grup() {}

template <typename T, typename R>
Grup<T, R>::~Grup() {}

template <typename T, typename R>
string Grup<T, R>::get_id() const
{
    return Grup<T, R>::identifier;
}

template <typename T, typename R>
const typename Grup<T, R>::vecshapepnt_t & Grup<T, R>::get_continut() const
{
    return continut;
}

template <typename T, typename R>
void Grup<T, R>::add(Shape<T, R> * shape)
{
    continut.push_back(shape);
}

template <typename T, typename R>
void Grup<T, R>::remove(Shape<T, R> * shape)
{
    for (typename Grup<T, R>::vecshapepnt_t::iterator it = continut.begin();
         it != continut.end(); ++it) {
        if (**it == *shape) {
            (*it)->free_mem();
            continut.erase(it);
            break;
        }
    }
}

template <typename T, typename R>
void Grup<T, R>::output(ostream & out) const
{
    out << get_id() << ' ' << continut.size() << endl;
    for (typename Grup<T, R>::vecshapepnt_t::const_iterator cit = continut.cbegin();
         cit != continut.cend(); ++cit)
        (*cit)->output(out);
}

template <typename T, typename R>
void Grup<T, R>::readFrom(istream & in)
{
    int nr;
    in >> nr;
    ShapeFactory<T, R> * factory = ShapeFactory<T, R>::get_instance();
    while (nr--) {
        Shape<T, R> * pshp = factory->create_shape(in);
        pshp->readFrom(in);
        add(pshp);
    }
}

template <typename T, typename R>
class MoveBy {

    T a, b;

public:
    MoveBy(T a = 0, T b = 0): a(a), b(b) {}

    void operator()(Shape<T, R> * pshp)
    {
        pshp->moveBy(a, b);
    }
};

template <typename T, typename R>
void Grup<T, R>::moveBy(T a, T b)
{
    MoveBy<T, R> moveby(a, b);
    for_each(continut.begin(), continut.end(), moveby);
}

template <typename T, typename R>
inline bool _comp(Shape<T, R> * a, Shape<T, R> * b)
{
    return *a == *b;
}

template <typename T, typename R>
bool Grup<T, R>::operator==(const Shape<T, R> & _shape) const
{
    if (get_id().compare(_shape.get_id()))
        return false;
    const Grup<T, R> & shape = static_cast<const Grup<T, R> &>(_shape);
    if (continut.size() != shape.get_continut().size())
        return false;
    return equal(continut.cbegin(), continut.cend(),
                 shape.get_continut().cbegin(), _comp<T, R>);
}

template <typename T, typename R>
Shape<T, R> * Grup<T, R>::create()
{
    return new Grup<T, R>();
}

template <typename T, typename R>
void Grup<T, R>::cli(ostream & out) const
{
    for (typename Grup<T, R>::vecshapepnt_t::const_iterator cit = continut.cbegin();
         cit != continut.cend(); ++cit)
        cout << (**cit);
}


template <typename T, typename R>
ostream &operator<<(ostream & out, const Grup<T, R> & grup)
{
    grup.cli(out);
    return out;
}
