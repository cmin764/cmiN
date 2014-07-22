#include <istream>
#include <map>
#include <string>

#include "shape.hpp"
#include "shapefactory.hpp"
#include "grup.hpp"
#include "cerc.hpp"
#include "triunghi.hpp"
#include "dreptunghi.hpp"


using namespace std;


const char * WrongFormatException::what() const throw()
{
    return "Function not registered";
}


ShapeFactory::ShapeFactory()
{
    register_function(Grup::identifier, Grup::create);
    register_function(Cerc::identifier, Cerc::create);
    register_function(Triunghi::identifier, Triunghi::create);
    register_function(Dreptunghi::identifier, Dreptunghi::create);
}

ShapeFactory::~ShapeFactory()
{
    createdFunctions.clear();
}

ShapeFactory * ShapeFactory::get_instance()
{
    static ShapeFactory instance;
    return &instance;
}

void ShapeFactory::register_function(const string & funcName,
                                     const shape_func_t func)
{
    createdFunctions[funcName] = func;
}

Shape * ShapeFactory::create_shape(const string & funcName) const
{
    mss_t::const_iterator cit = createdFunctions.find(funcName);
    if (cit == createdFunctions.cend()) {
        throw WrongFormatException();
        //return NULL;
    }
    return cit->second();
}

Shape * ShapeFactory::create_shape(istream & in) const
{
    string funcName;
    in >> funcName;
    return create_shape(funcName);
}
