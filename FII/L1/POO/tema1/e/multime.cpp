#include <iostream>
#include <vector>
#include <algorithm>

#include "multime.hpp"


using namespace std;


Multime::Multime() {}

Multime::Multime(const Multime::cont_type & vec)
{
    this->vec.assign(vec.cbegin(), vec.cend());
    sort(this->vec.begin(), this->vec.end());
    this->vec.resize(distance(this->vec.begin(),
                              unique(this->vec.begin(),
                                     this->vec.end())));
}

Multime::Multime(const Multime & mul)
{
    this->vec.assign(mul.get_vec().cbegin(), mul.get_vec().cend());
}

const Multime::cont_type & Multime::get_vec() const
{
    return vec;
}

bool Multime::operator+=(int elem)
{
    Multime::cont_type::iterator it = lower_bound(vec.begin(), vec.end(),
                                                  elem);
    if (it != vec.end() && *it == elem)
        return false;    // `elem` already exists
    vec.insert(it, elem);
    return true;
}

bool Multime::operator-=(int elem)
{
    Multime::cont_type::iterator it = lower_bound(vec.begin(), vec.end(),
                                                  elem);
    if (*it != elem)
        return false;    // `elem` doesn't exist
    vec.erase(it);
    return true;
}


Multime operator+(const Multime & mul1, const Multime & mul2)
{
    Multime ret;
    const Multime::cont_type & vec1 = mul1.get_vec(), & vec2 = mul2.get_vec();
    set_union(vec1.cbegin(), vec1.cend(),
              vec2.cbegin(), vec2.cend(), ret.vec.begin());
    return ret;
}


bool operator==(const Multime & mul1, const Multime & mul2)
{
    const Multime::cont_type & vec1 = mul1.get_vec(), & vec2 = mul2.get_vec();
    if (vec1.size() != vec2.size())
        return false;
    return equal(vec1.cbegin(), vec1.cend(), vec2.cbegin());
}


ostream& operator<<(ostream& out, const Multime & mul)
{
    const Multime::cont_type & vec = mul.get_vec();
    for (Multime::cont_type::const_iterator it = vec.cbegin();
         it != vec.cend(); ++it)
        out << *it << ' ';
    out << endl;
    return out;
}
