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


class ShapeFactory {

    typedef Shape * (*shape_func_t)(void);
    typedef map<string, shape_func_t> mss_t;

    mss_t createdFunctions;

    ShapeFactory();

public:
    ~ShapeFactory();

    static ShapeFactory * get_instance();

    void register_function(const string &, const shape_func_t);

    Shape * create_shape(const string &) const;
    Shape * create_shape(istream &) const;
};


#endif // SHAPEFACTORY_HPP_INCLUDED
