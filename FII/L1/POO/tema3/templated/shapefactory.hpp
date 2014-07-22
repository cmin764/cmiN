#ifndef SHAPEFACTORY_HPP_INCLUDED
#define SHAPEFACTORY_HPP_INCLUDED


#include <istream>
#include <map>
#include <string>
#include <exception>

#include "shape.hpp"


using namespace std;


class WrongFormatException: public exception {

    virtual const char * what() const throw();
};


template <typename T=int, typename R=int>
class ShapeFactory {

    typedef Shape<T, R> * (*shape_func_t)(void);
    typedef map<string, shape_func_t> mss_t;

    mss_t createdFunctions;

    ShapeFactory();

public:
    ~ShapeFactory();

    static ShapeFactory<T, R> * get_instance();

    void register_function(const string &, const shape_func_t);

    Shape<T, R> * create_shape(const string &) const;
    Shape<T, R> * create_shape(istream &) const;
};


#include "shapefactory.cpp"


#endif // SHAPEFACTORY_HPP_INCLUDED
