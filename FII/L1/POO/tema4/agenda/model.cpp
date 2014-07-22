#include <string>
#include <fstream>
#include <iostream>

#include "model.hpp"
#include "utils.hpp"


#define SUF ".txt"


using namespace std;


ModelContact::ModelContact(string first, string last,
                           int number,
                           ModelContact::ContactType whois): first(first),
                                                             last(last),
                                                             number(number),
                                                             whois(whois) {}

ModelContact::ModelContact(const ModelContact & modelContact)
{
    set_first(modelContact.get_first());
    set_last(modelContact.get_last());
    set_number(modelContact.get_number());
    set_type(modelContact.get_type());
}

void ModelContact::set_first(string first)
{
    this->first = first;
}

void ModelContact::set_last(string last)
{
    this->last = last;
}

void ModelContact::set_number(int number)
{
    this->number = number;
}

void ModelContact::set_type(ModelContact::ContactType whois)
{
    this->whois = whois;
}

string ModelContact::get_first() const
{
    return first;
}

string ModelContact::get_last() const
{
    return last;
}

int ModelContact::get_number() const
{
    return number;
}

ModelContact::ContactType ModelContact::get_type() const
{
    return whois;
}

bool ModelContact::operator==(const ModelContact & modelContact) const
{
    if (get_number() != modelContact.get_number())
        return false;
    if (get_first() != modelContact.get_first())
        return false;
    if (get_last() != modelContact.get_last())
        return false;
    if (get_type() != modelContact.get_type())
        return false;
    return true;
}

bool ModelContact::operator!=(const ModelContact & modelContact) const
{
    return !(*this == modelContact);
}

void ModelContact::operator=(const ModelContact & modelContact)
{
    string first = modelContact.get_first(), last = modelContact.get_last();
    int number = modelContact.get_number();
    ModelContact::ContactType whois = modelContact.get_type();

    if (first.length())
        set_first(first);
    if (last.length())
        set_last(last);
    if (number)
        set_number(number);
    if (whois != ModelContact::NAT)
        set_type(whois);
}

istream & operator>>(istream & in, ModelContact & modelContact)
{
    string first, last;
    int number;
    ModelContact::ContactType whois;
    int _whois;

    cout << "First name: ";
    in >> first;
    cout << "Last name: ";
    in >> last;
    cout << "Number: ";
    in >> number;
    cout << "Type (1-Friend 2-Work 3-Other): ";
    cin >> _whois;
    whois = int2enum(_whois);

    modelContact.set_first(first);
    modelContact.set_last(last);
    modelContact.set_number(number);
    modelContact.set_type(whois);

    return in;
}

ostream & operator<<(ostream & out, const ModelContact & modelContact)
{
    out << "First name: " << modelContact.get_first() << endl <<
           "Last name: " << modelContact.get_last() << endl <<
           "Number: " << modelContact.get_number() << endl <<
           "Type: " << enum2str(modelContact.get_type()) << endl;

    return out;
}


ModelAgenda::ModelAgenda(string name): name(name) {}

ModelAgenda::ModelAgenda(string name, string fname): name(name)
{
    load(fname);
}

ModelAgenda::ModelAgenda(string name, const ModelAgenda & modelAgenda): name(name)
{
    for (container_t::const_iterator cit = modelAgenda.contacts.cbegin();
         cit != modelAgenda.contacts.cend(); ++cit)
        add(**cit);
}

ModelAgenda::ModelAgenda(const ModelAgenda & modelAgenda): ModelAgenda(modelAgenda.name,
                                                                       modelAgenda) {}

ModelAgenda::~ModelAgenda()
{
    clear();
}

ModelContact ModelAgenda::search(const ModelContact & modelContact) const
{
    for (container_t::const_iterator cit = contacts.cbegin();
         cit != contacts.cend(); ++cit)
        if (**cit == modelContact)
            return **cit;
    return ModelContact();
}

ModelContact ModelAgenda::search(string first, string last) const
{
    for (container_t::const_iterator cit = contacts.cbegin();
         cit != contacts.cend(); ++cit)
        if (!first.compare((*cit)->get_first()) &&
            !last.compare((*cit)->get_last()))
            return **cit;

    return ModelContact();
}

ModelContact ModelAgenda::search(int number) const
{
    for (container_t::const_iterator cit = contacts.cbegin();
         cit != contacts.cend(); ++cit)
        if ((*cit)->get_number() == number)
            return **cit;

    return ModelContact();
}

ModelAgenda::container_t ModelAgenda::search(string prefix) const
{
    container_t ret;
    for (container_t::const_iterator cit = contacts.cbegin();
         cit != contacts.cend(); ++cit) {
        ModelContact modelContact(**cit);
        int indf = modelContact.get_first().find(prefix);
        int indl = modelContact.get_last().find(prefix);
        if (indf == 0 || indl == 0)
            ret.push_back(new ModelContact(modelContact));
    }
    return ret;
}

ModelAgenda::container_t ModelAgenda::search(ModelContact::ContactType whois) const
{
    container_t ret;
    for (container_t::const_iterator cit = contacts.cbegin();
         cit != contacts.cend(); ++cit) {
        ModelContact modelContact(**cit);
        ModelContact::ContactType _whois = modelContact.get_type();
        if (_whois == whois)
            ret.push_back(new ModelContact(modelContact));
    }
    return ret;
}

bool ModelAgenda::add(const ModelContact & modelContact)
{
    if (modelContact.get_type() == ModelContact::NAT)
        return false;

    if (search(modelContact.get_first(),
               modelContact.get_last()).get_type() != ModelContact::NAT ||
        search(modelContact.get_number()).get_type() != ModelContact::NAT)
        return false;

    contacts.push_back(new ModelContact(modelContact));
    return true;
}

bool ModelAgenda::remove(const ModelContact & modelContact)
{
    for (container_t::iterator it = contacts.begin();
         it != contacts.end(); ++it) {
        ModelContact _modelContact(**it);
        if (_modelContact == modelContact) {
            delete *it;
            contacts.erase(it);
            return true;
        }
    }
    return false;
}

bool ModelAgenda::modify(const ModelContact & modelContact, string first,
                         string last, int number,
                         ModelContact::ContactType whois)
{
    ModelContact _modelContact = search(modelContact);

    if (_modelContact.get_type() == ModelContact::NAT)
        return false;
    remove(modelContact);

    if (first.length())
        _modelContact.set_first(first);
    if (last.length())
        _modelContact.set_last(last);
    if (number)
        _modelContact.set_number(number);
    if (whois != ModelContact::NAT)
        _modelContact.set_type(whois);

    bool status = add(_modelContact);
    if (!status)
        add(modelContact);
    return status;
}

bool ModelAgenda::modify(const ModelContact & modelContact,
                         const ModelContact & contact)
{
    return modify(modelContact, contact.get_first(), contact.get_last(),
                  contact.get_number(), contact.get_type());
}

void ModelAgenda::save() const
{
    ofstream fout(string(name).append(SUF));
    for (container_t::const_iterator cit = contacts.cbegin();
         cit != contacts.cend(); ++cit) {
        ModelContact modelContact(**cit);
        fout << modelContact.get_first() << " " <<
                modelContact.get_last() << " " <<
                modelContact.get_number() << " " <<
                modelContact.get_type() << endl;
    }
    fout.close();
}

void ModelAgenda::load(string fname)
{
    ifstream fin(string(fname).append(SUF));
    clear();

    while (fin.good()) {
        string first, last;
        int number;
        ModelContact::ContactType whois;

        fin >> first >> last >> number;
        if (fin.eof())
            break;
        int _whois;
        fin >> _whois;
        whois = int2enum(_whois);

        contacts.push_back(new ModelContact(first, last, number, whois));
    }

    fin.close();
}

void ModelAgenda::clear()
{
    for (container_t::iterator it = contacts.begin(); it != contacts.end();
         ++it)
        delete *it;

    contacts.clear();
}

void ModelAgenda::set_name(string fname)
{
    name = fname;
}

string ModelAgenda::get_name() const
{
    return name;
}
