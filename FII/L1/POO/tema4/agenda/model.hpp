#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED


#include <list>
#include <string>
#include <iostream>


using namespace std;


class ModelContact {

public:
    enum ContactType {FRIEND=1, WORK, OTHER, NAT};

private:
    string first, last;
    int number;
    ContactType whois;

public:
    ModelContact(string = "", string = "", int = 0, ContactType = NAT);
    ModelContact(const ModelContact &);

    void set_first(string);
    void set_last(string);
    void set_number(int);
    void set_type(ContactType);

    string get_first() const;
    string get_last() const;
    int get_number() const;
    ContactType get_type() const;

    bool operator==(const ModelContact &) const;
    bool operator!=(const ModelContact &) const;
    void operator=(const ModelContact &);

    friend istream & operator>>(istream &, ModelContact &);
    friend ostream & operator<<(ostream &, const ModelContact &);
};


class ModelAgenda {

public:
    typedef list<ModelContact *> container_t;

private:
    string name;
    container_t contacts;

public:
    ModelAgenda(string);
    ModelAgenda(string, string);
    ModelAgenda(string, const ModelAgenda &);
    ModelAgenda(const ModelAgenda &);

    ~ModelAgenda();

    ModelContact search(const ModelContact &) const;
    ModelContact search(string, string) const;
    ModelContact search(int) const;
    container_t search(string) const;
    container_t search(ModelContact::ContactType) const;

    bool add(const ModelContact &);
    bool remove(const ModelContact &);
    bool modify(const ModelContact &, string = "", string = "", int = 0,
                ModelContact::ContactType = ModelContact::NAT);
    bool modify(const ModelContact &,
                const ModelContact &);

    void save() const;
    void load(string);
    void clear();

    void set_name(string);
    string get_name() const;
};


#endif // MODEL_HPP_INCLUDED
