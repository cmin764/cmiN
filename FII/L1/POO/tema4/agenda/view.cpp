#include <iostream>
#include <iterator>
#include <string>

#include "view.hpp"
#include "model.hpp"
#include "utils.hpp"


using namespace std;


void IView::show_msg(string msg) const
{
    cout << msg << endl;
}


ViewContact::ViewContact(const ModelContact & modelContact): modelContact(modelContact) {}

int ViewContact::get_option() const
{
    cout << endl << modelContact << endl;
    cout << "1. Remove contact" << endl <<
            "2. Modify contact" << endl <<
            "0. Done" << endl <<
            "Option: ";

    int op;
    cin >> op;
    cout << endl;
    return op;
}

ModelContact ViewContact::modify_contact() const
{
    bool finish = false;
    ModelContact contact;

    while (!finish) {
        cout << endl;
        cout << "1. First name" << endl <<
                "2. Last name" << endl <<
                "3. Telephone number" << endl <<
                "4. Type" << endl <<
                "0. Save" << endl <<
                "Option: ";
        int op;
        cin >> op;
        cout << endl;

        switch (op) {
        case 1:
            cout << "Old: " << modelContact.get_first() << endl;
            cout << "New: ";
            {
            string first;
            cin >> first;
            contact.set_first(first);
            }
            break;
        case 2:
            cout << "Old: " << modelContact.get_last() << endl;
            cout << "New: ";
            {
            string last;
            cin >> last;
            contact.set_last(last);
            }
            break;
        case 3:
            cout << "Old: " << modelContact.get_number() << endl;
            cout << "New: ";
            {
            int number;
            cin >> number;
            contact.set_number(number);
            }
            break;
        case 4:
            cout << "Old: " << enum2str(modelContact.get_type()) << endl;
            cout << "New (1-Friend 2-Work 3-Other): ";
            {
            int _whois;
            cin >> _whois;
            contact.set_type(int2enum(_whois));
            }
            break;
        case 0:
            finish = true;
            break;
        default:
            show_msg("Invalid option");
        }
    }

    return contact;
}


ViewAgenda::ViewAgenda(const ModelAgenda & modelAgenda): modelAgenda(modelAgenda) {}

void ViewAgenda::show_name() const
{
    cout << "Current name: " << modelAgenda.get_name() << endl;
}

string ViewAgenda::set_name() const
{
    string fname;
    cout << "Agenda name: ";
    cin >> fname;
    return fname;
}

int ViewAgenda::get_option() const
{
    cout << endl;
    cout << "1. Rename agenda" << endl <<
            "2. View all contacts" << endl <<
            "3. Select one contact" << endl <<
            "4. Search for contacts" << endl <<
            "5. Add contact" << endl <<
            "6. Save agenda" << endl <<
            "7. Load agenda" << endl <<
            "0. Quit" << endl <<
            "Option: ";
    int op;
    cin >> op;
    cout << endl;
    return op;
}

void ViewAgenda::show_contacts() const
{
    ModelAgenda::container_t contacts(modelAgenda.search(""));
    for (ModelAgenda::container_t::const_iterator cit = contacts.cbegin();
         cit != contacts.cend(); ++cit)
        cout << **cit << endl;
}

ModelContact ViewAgenda::select_contact() const
{
    ModelAgenda::container_t contacts(modelAgenda.search(""));

    cout << "ID: ";
    int id;
    cin >> id;

    if (id < 1 || id > (int)contacts.size())
        return ModelContact();

    --id;
    ModelAgenda::container_t::const_iterator cit = contacts.cbegin();
    advance(cit, id);
    return **cit;
}

void ViewAgenda::search_contacts() const
{
    bool quit = false;
    ModelAgenda::container_t all(modelAgenda.search(""));

    while (!quit) {
        cout << endl;
        cout << "1. Prefix" << endl <<
                "2. First and last name" << endl <<
                "3. Telephone number" << endl <<
                "4. Type" << endl <<
                "0. End" << endl <<
                "Option: ";

        int op;
        cin >> op;
        cout << endl;
        ModelAgenda::container_t contacts;

        switch (op) {
        case 1:
            {
            string prefix;
            cout << "Prefix: ";
            cin >> prefix;
            contacts = modelAgenda.search(prefix);
            }
            break;
        case 2:
            {
            string first, last;
            cout << "First name: ";
            cin >> first;
            cout << "Last name: ";
            cin >> last;
            ModelContact modelContact(modelAgenda.search(first, last));
            if (modelContact.get_type() != ModelContact::NAT)
                contacts.push_back(new ModelContact(modelContact));
            }
            break;
        case 3:
            {
            int number;
            cout << "Telephone number: ";
            cin >> number;
            ModelContact modelContact(modelAgenda.search(number));
            if (modelContact.get_type() != ModelContact::NAT)
                contacts.push_back(new ModelContact(modelContact));
            }
            break;
        case 4:
            {
            int _whois;
            cout << "(1-Friend 2-Work 3-Other): ";
            cin >> _whois;

            ModelContact::ContactType whois;
            switch (_whois) {
            case ModelContact::FRIEND:
                whois = ModelContact::FRIEND;
                break;
            case ModelContact::WORK:
                whois = ModelContact::WORK;
                break;
            case ModelContact::OTHER:
                whois = ModelContact::OTHER;
                break;
            default:
                whois = ModelContact::NAT;
            }
            contacts = modelAgenda.search(whois);
            }
            break;
        case 0:
            quit = true;
            break;
        default:
            show_msg("Invalid option");
        }

        for (ModelAgenda::container_t::const_iterator cit = contacts.cbegin();
             cit != contacts.cend(); ++cit) {
            int id = 1;
            for (ModelAgenda::container_t::const_iterator cit2 = all.cbegin();
                 cit2 != all.cend(); ++cit2, ++id)
                if ((**cit) == (**cit2))
                    break;
            cout << "[" << id << "] " << (*cit)->get_first() << " " <<
                    (*cit)->get_last() << endl;
        }
        cout << endl;
    }
}

ModelContact ViewAgenda::add_contact() const
{
    ModelContact modelContact;
    cin >> modelContact;
    return modelContact;
}
