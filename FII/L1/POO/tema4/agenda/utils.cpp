#include "utils.hpp"


string enum2str(ModelContact::ContactType whois)
{
    switch (whois) {
    case ModelContact::FRIEND:
        return "Friend";
    case ModelContact::WORK:
        return "Work";
    case ModelContact::OTHER:
        return "Other";
    default:
        return "Invalid";
    }
}

ModelContact::ContactType int2enum(int whois)
{
    switch (whois) {
    case 1:
        return ModelContact::FRIEND;
    case 2:
        return ModelContact::WORK;
    case 3:
        return ModelContact::OTHER;
    default:
        return ModelContact::NAT;
    }
}
