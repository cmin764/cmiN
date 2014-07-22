#include "controller.hpp"
#include "model.hpp"
#include "view.hpp"


ControllerContact::ControllerContact(ModelContact & modelContact,
                                     ViewContact & viewContact,
                                     ModelAgenda & modelAgenda): modelContact(modelContact),
                                                                 viewContact(viewContact),
                                                                 modelAgenda(modelAgenda) {}

void ControllerContact::loop()
{
    enum vcOptions {REMOVE=1, MODIFY, QUIT=0};
    bool quit = false;

    while (!quit) {
        int op = viewContact.get_option();

        switch (op) {
        case REMOVE:
            {
            bool status = modelAgenda.remove(modelContact);
            if (status) {
                viewContact.show_msg("Removed successfully");
                quit = true;
            }
            }
            break;
        case MODIFY:
            {
            ModelContact contact(viewContact.modify_contact());
            bool status = modelAgenda.modify(modelContact, contact);
            if (status) {
                modelContact = contact;
                viewContact.show_msg("Modified successfully");
            } else
                viewContact.show_msg("Number, first or last name already in use or invalid type");
            }
            break;
        case QUIT:
            quit = true;
            break;
        default:
            viewContact.show_msg("Invalid option");
        }
    }
}


ControllerAgenda::ControllerAgenda(ModelAgenda & modelAgenda,
                                   ViewAgenda & viewAgenda): modelAgenda(modelAgenda),
                                                             viewAgenda(viewAgenda) {}

void ControllerAgenda::loop()
{
    enum vaOptions {RENAME=1, VIEW, SELECT, SEARCH, ADD, SAVE, LOAD, QUIT=0};
    bool quit = false;

    while (!quit) {
        int op = viewAgenda.get_option();

        switch (op) {
        case RENAME:
            viewAgenda.show_name();
            {
            string fname(viewAgenda.set_name());
            modelAgenda.set_name(fname);
            }
            break;
        case VIEW:
            viewAgenda.show_contacts();
            break;
        case SELECT:
            {
            ModelContact modelContact(viewAgenda.select_contact());
            if (modelContact.get_type() == ModelContact::NAT) {
                viewAgenda.show_msg("Contact doesn't exist");
                break;
            }
            ViewContact viewContact(modelContact);
            ControllerContact controllerContact(modelContact, viewContact, modelAgenda);
            controllerContact.loop();
            }
            break;
        case SEARCH:
            viewAgenda.search_contacts();
            break;
        case ADD:
            {
            ModelContact modelContact(viewAgenda.add_contact());
            bool status = modelAgenda.add(modelContact);
            if (status)
                viewAgenda.show_msg("Added successfully");
            else
                viewAgenda.show_msg("Number, first or last name already in use or invalid type");
            }
            break;
        case SAVE:
            modelAgenda.save();
            break;
        case LOAD:
            {
                string fname(viewAgenda.set_name());
                modelAgenda.load(fname);
            }
            break;
        case QUIT:
            quit = true;
            break;
        default:
            viewAgenda.show_msg("Error: Invalid option");
        }
    }
}
