#ifndef VIEW_HPP_INCLUDED
#define VIEW_HPP_INCLUDED


#include <string>

#include "model.hpp"


using namespace std;


class IView {

public:
    virtual void show_msg(string) const;
};


class IViewContact: public IView {

public:
    virtual int get_option() const = 0;
    virtual ModelContact modify_contact() const = 0;
};


class IViewAgenda: public IView {

public:
    virtual void show_name() const = 0;

    virtual string set_name() const = 0;
    virtual int get_option() const = 0;
    virtual void show_contacts() const = 0;
    virtual void search_contacts() const = 0;
    virtual ModelContact select_contact() const = 0;
    virtual ModelContact add_contact() const = 0;
};


class ViewContact: public IViewContact {

    const ModelContact & modelContact;

public:
    ViewContact(const ModelContact &);

    int get_option() const;
    ModelContact modify_contact() const;
};


class ViewAgenda: public IViewAgenda {

    const ModelAgenda & modelAgenda;

public:
    ViewAgenda(const ModelAgenda &);

    void show_name() const;

    string set_name() const;
    int get_option() const;
    void show_contacts() const;
    void search_contacts() const;
    ModelContact select_contact() const;
    ModelContact add_contact() const;
};


#endif // VIEW_HPP_INCLUDED
