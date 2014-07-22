#include <iostream>

#include "shape.hpp"
#include "cerc.hpp"
#include "triunghi.hpp"
#include "dreptunghi.hpp"
#include "grup.hpp"
#include "patrat.hpp"


#define DBG 0


using namespace std;


template<typename T, typename R>
Shape<T, R>::~Shape()
{
    #if DBG
    cerr << "Shape destroyed" << endl;
    #endif
}

template<typename T, typename R>
void Shape<T, R>::free_mem()
{
    delete this;
}


template<typename T, typename R>
ostream & operator<<(ostream & out, const Shape<T, R> & _shape)
{
    _shape.cli(out);
    return out;
}
