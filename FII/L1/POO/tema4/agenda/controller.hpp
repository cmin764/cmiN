#ifndef CONTROLLER_HPP_INCLUDED
#define CONTROLLER_HPP_INCLUDED


#include "model.hpp"
#include "view.hpp"


class ControllerContact {

    ModelContact & modelContact;
    ViewContact & viewContact;

    ModelAgenda & modelAgenda;

public:
    ControllerContact(ModelContact &, ViewContact &, ModelAgenda &);

    void loop();
};


class ControllerAgenda {

    ModelAgenda & modelAgenda;
    ViewAgenda & viewAgenda;

public:
    ControllerAgenda(ModelAgenda &, ViewAgenda &);

    void loop();
};


#endif // CONTROLLER_HPP_INCLUDED
