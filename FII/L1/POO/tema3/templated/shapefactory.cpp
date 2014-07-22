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


template <typename T, typename R>
ShapeFactory<T, R>::ShapeFactory()
{
    register_function(Grup<T, R>::identifier, Grup<T, R>::create);
    register_function(Cerc<T, R>::identifier, Cerc<T, R>::create);
    register_function(Triunghi<T, R>::identifier, Triunghi<T, R>::create);
    register_function(Dreptunghi<T, R>::identifier, Dreptunghi<T, R>::create);
}

template <typename T, typename R>
ShapeFactory<T, R>::~ShapeFactory()
{
    createdFunctions.clear();
}

template <typename T, typename R>
ShapeFactory<T, R> * ShapeFactory<T, R>::get_instance()
{
    static ShapeFactory<T, R> instance;
    return &instance;
}

template <typename T, typename R>
void ShapeFactory<T, R>::register_function(const string & funcName,
                                           const shape_func_t func)
{
    createdFunctions[funcName] = func;
}

template <typename T, typename R>
Shape<T, R> * ShapeFactory<T, R>::create_shape(const string & funcName) const
{
    typename mss_t::const_iterator cit = createdFunctions.find(funcName);
    if (cit == createdFunctions.cend()) {
        throw WrongFormatException();
        //return NULL;
    }
    return cit->second();
}

template <typename T, typename R>
Shape<T, R> * ShapeFactory<T, R>::create_shape(istream & in) const
{
    string funcName;
    in >> funcName;
    return create_shape(funcName);
}
