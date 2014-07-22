#include <iostream>

#include "shape.hpp"
#include "cerc.hpp"
#include "triunghi.hpp"
#include "dreptunghi.hpp"


#define DBG 0


using namespace std;


Shape::~Shape()
{
    #if DBG
    cerr << "Shape destroyed" << endl;
    #endif
}


ostream &operator<<(ostream & out, const Shape & _shape)
{
    if (!Cerc::identifier.compare(_shape.get_id()))
        return out << static_cast<const Cerc &>(_shape);
    if (!Triunghi::identifier.compare(_shape.get_id()))
        return out << static_cast<const Triunghi &>(_shape);
    if (!Dreptunghi::identifier.compare(_shape.get_id()))
        return out << static_cast<const Dreptunghi &>(_shape);
}
