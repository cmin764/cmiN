#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <utility>
#include <fstream>

#include <cctype>

#include "biblioteca.hpp"


using namespace std;


int Publicatie::UID = 0;

void Publicatie::gen_uid()
{
    ++Publicatie::UID;
    uid = Publicatie::UID;
}

int Publicatie::get_uid() const
{
    return uid;
}

Publicatie::Publicatie(): tip(0), valid(false)
{
    gen_uid();
}

Publicatie::Publicatie(const string & titlu, const string & editura,
                       int an, int tiraj): tip(0), valid(true),
                                            titlu(titlu), editura(editura),
                                            an(an), tiraj(tiraj)
{
    gen_uid();

    if (titlu.empty())
        valid = false;
    if (editura.empty())
        valid = false;
    if (an < 0)
        valid = false;
    if (tiraj < 0)
        valid = false;
}

Publicatie::Publicatie(const Publicatie & pub): uid(pub.get_uid()),
                                                tip(pub.get_tip()),
                                                valid(pub.get_valid()),
                                                titlu(pub.get_titlu()),
                                                editura(pub.get_editura()),
                                                an(pub.get_an()),
                                                tiraj(pub.get_tiraj()) {}

int Publicatie::get_tip() const
{
    return tip;
}

const string & Publicatie::get_titlu() const
{
    return titlu;
}

const string & Publicatie::get_editura() const
{
    return editura;
}

int Publicatie::get_an() const
{
    return an;
}

int Publicatie::get_tiraj() const
{
    return tiraj;
}

bool Publicatie::get_valid() const
{
    return valid;
}

pair<bool, bool> Publicatie::operator== \
    (const Publicatie & publicatie) const
{
    bool partial = true, full = true;

    if (uid != publicatie.get_uid())
        full = false;
    if (titlu.compare(publicatie.get_titlu()))
        full = partial = false;
    if (editura.compare(publicatie.get_editura()))
        full = partial = false;
    if (an != publicatie.get_an())
        full = partial = false;
    if (tiraj != publicatie.get_tiraj())
        full = partial = false;
    if (valid != publicatie.get_valid())
        full = partial = false;

    pair<bool, bool> ret(full, partial);
    return ret;
}


Carte::Carte(): Publicatie() {}

Carte::Carte(const string & titlu, const string & editura,
             int an, int tiraj, const AutorContainer & autori): \
                 Publicatie(titlu, editura, an, tiraj),
                 autori(autori)
{
    if (autori.empty())
        valid = false;
    tip = 1;
}

Carte::Carte(const Carte & carte): \
    Publicatie(dynamic_cast<const Publicatie &>(carte)), \
    autori(carte.autori) {}

inline bool Carte::predicate(const string & first,
                             const string & second)
{
    return !first.compare(second);
}

const Carte::AutorContainer & Carte::get_autori() const
{
    return autori;
}

pair<bool, bool> Carte::operator==(const Carte & carte) const
{
    // verifica numarul si autorii in sine
    pair<bool, bool> ret(dynamic_cast<const Publicatie &>(*this) == \
                         dynamic_cast<const Publicatie &>(carte));


    if (autori.size() != carte.get_autori().size())
        ret.first = ret.second = false;
    if (!equal(autori.cbegin(), autori.cend(),
               carte.get_autori().cbegin(), predicate))
        ret.first = ret.second = false;

    return ret;
}


Revista::Revista(): Publicatie() {}

Revista::Revista(const string & titlu, const string & editura,
                 int an, int tiraj, int numar, int frecventa): \
                     Publicatie(titlu, editura, an, tiraj),
                     numar(numar), frecventa(frecventa)
{
    tip = 2;
}

Revista::Revista(const Revista & revista): \
    Publicatie(dynamic_cast<const Publicatie &>(revista)),
    numar(revista.numar), frecventa(revista.frecventa) {}

int Revista::get_numar() const
{
    return numar;
}

int Revista::get_frecventa() const
{
    return frecventa;
}

pair<bool, bool> Revista::operator==(const Revista & revista) const
{
    pair<bool, bool> ret(dynamic_cast<const Publicatie &>(*this) == \
                         dynamic_cast<const Publicatie &>(revista));

    if (numar != revista.get_numar())
        ret.first = ret.second = false;
    if (frecventa != revista.get_frecventa())
        ret.first = ret.second = false;

    return ret;
}


const Publicatie Biblioteca::pNULL;
const Carte Biblioteca::cNULL;
const Revista Biblioteca::rNULL;

Biblioteca::Biblioteca(const string & nume): nume(nume),
    dCar(0), dRev(0) {}

Biblioteca::Biblioteca(const string & nume, const Biblioteca & biblioteca): \
    nume(nume), dCar(biblioteca.get_dCar()), dRev(biblioteca.get_dRev())
{
    /* "copiem" articolele bibliotecii pasate ca argument,
       creand si alocand memorie pentru fiecare nou pointer creat */

    const Biblioteca::PubContainer & publicatii = biblioteca.get_container();

    for (Biblioteca::PubContainer::const_iterator cit = publicatii.cbegin();
         cit != publicatii.cend(); ++cit) {

        Publicatie * publicatie;
        int tip = (*cit)->get_tip();

        if (tip == 1)
            publicatie = new Carte(*static_cast<const Carte *>(*cit));
        else
            publicatie = new Revista(*static_cast<const Revista *>(*cit));

        this->publicatii.push_back(publicatie);
    }
}

Biblioteca::~Biblioteca()
{
    clear();
}

void Biblioteca::clear()
{
    // elibereaza memoria alocata fiecarei publicatii
    for (PubContainer::const_iterator cit = publicatii.cbegin();
         cit != publicatii.cend(); ++cit)
        delete *cit;
    publicatii.clear();
}

int Biblioteca::get_dCar() const
{
    return dCar;
}

int Biblioteca::get_dRev() const
{
    return dRev;
}

const Biblioteca::PubContainer & Biblioteca::get_container() const
{
    return const_cast<const Biblioteca::PubContainer &>(publicatii);
}

int Biblioteca::cantitate() const
{
    return publicatii.size();
}

Biblioteca::finditer_type \
    Biblioteca::exista(const Publicatie * pubPnt)
{
    Biblioteca::finditer_type \
        ret(publicatii.end(), publicatii.end());

    // 1-Carte 2-Revista
    const Carte * cartePnt = static_cast<const Carte *>(pubPnt);
    const Revista * revPnt = static_cast<const Revista *>(pubPnt);

    for (Biblioteca::PubContainer::iterator cit = publicatii.begin();
         cit != publicatii.end(); ++cit) {
        int tip = (*cit)->get_tip();

        if (tip != pubPnt->get_tip())
            continue;

        if (tip == 1) {
            pair<bool, bool> e1 = (*cartePnt == *static_cast<const Carte *>(*cit));
            if (e1.second && ret.second == publicatii.end())
                ret.second = cit;
            if (e1.first && ret.first == publicatii.end())
                ret.first = cit;
        } else if (tip == 2) {
            pair<bool, bool> e2 = (*revPnt == *static_cast<const Revista *>(*cit));
            if (e2.second && ret.second == publicatii.end())
                ret.second = cit;
            if (e2.first && ret.first == publicatii.end())
                ret.first = cit;
        }
    }

    return ret;
}

bool Biblioteca::adauga(const Carte & carte)
{
    if (carte.get_tip() != 1)
        return false;
    if (!carte.get_valid())
        return false;

    Biblioteca::finditer_type \
        ret(exista(&carte));

    if (ret.first != publicatii.end())
        return false;

    publicatii.push_back(dynamic_cast<Publicatie *>(new Carte(carte)));
    if (ret.second == publicatii.end())
        ++dCar;

    return true;
}

bool Biblioteca::adauga(const Revista & revista)
{
    if (revista.get_tip() != 2)
        return false;
    if (!revista.get_valid())
        return false;

    Biblioteca::finditer_type \
        ret(exista(&revista));

    if (ret.first != publicatii.end())
        return false;

    publicatii.push_back(dynamic_cast<Publicatie *>(new Revista(revista)));
    if (ret.second == publicatii.end())
        ++dRev;

    return true;
}

bool Biblioteca::elimina(const Carte & carte)
{
    Biblioteca::finditer_type ret = exista(&carte);
    if (ret.first == publicatii.end())
        return false;

    publicatii.erase(ret.first);

    ret = exista(&carte);
    if (ret.second == publicatii.end())
        --dCar;

    return true;
}

bool Biblioteca::elimina(const Revista & revista)
{
    Biblioteca::finditer_type ret = exista(&revista);
    if (ret.first == publicatii.end())
        return false;

    publicatii.erase(ret.first);

    ret = exista(&revista);
    if (ret.second == publicatii.end())
        --dRev;

    return true;
}

const Publicatie & Biblioteca::cauta_titlu(const string & titlu) const
{
    for (Biblioteca::PubContainer::const_iterator cit = publicatii.cbegin();
         cit != publicatii.cend(); ++cit)
        if (!(*cit)->get_titlu().compare(titlu))
            return **cit;
    return Biblioteca::pNULL;
}

const Publicatie & Biblioteca::cauta_editura(const string & editura) const
{
    for (Biblioteca::PubContainer::const_iterator cit = publicatii.cbegin();
         cit != publicatii.cend(); ++cit)
        if (!(*cit)->get_editura().compare(editura))
            return **cit;
    return pNULL;
}

const Publicatie & Biblioteca::cauta_an(int an) const
{
    for (Biblioteca::PubContainer::const_iterator cit = publicatii.cbegin();
         cit != publicatii.cend(); ++cit)
        if ((*cit)->get_an() == an)
            return **cit;
    return pNULL;
}

const Publicatie & Biblioteca::cauta_tiraj(int tiraj) const
{
    for (Biblioteca::PubContainer::const_iterator cit = publicatii.cbegin();
         cit != publicatii.cend(); ++cit)
        if ((*cit)->get_tiraj() == tiraj)
            return **cit;
    return pNULL;
}

const Carte & Biblioteca::cauta_autori(const Carte::AutorContainer & autori) const
{
    for (Biblioteca::PubContainer::const_iterator cit = publicatii.cbegin();
         cit != publicatii.cend(); ++cit) {
        const Carte::AutorContainer & _autori = (static_cast<Carte *>(*cit))-> \
                                                get_autori();
        if (autori.size() == _autori.size() &&
            equal(autori.cbegin(), autori.cend(), _autori.cbegin()))
            return const_cast<const Carte &>(*static_cast<Carte *>(*cit));
    }
    return cNULL;
}

const Revista & Biblioteca::cauta_numar(int numar) const
{
    for (Biblioteca::PubContainer::const_iterator cit = publicatii.cbegin();
         cit != publicatii.cend(); ++cit)
        if (static_cast<Revista *>(*cit)->get_numar() == numar)
            return const_cast<const Revista &>(*static_cast<Revista *>(*cit));
    return rNULL;
}

const Revista & Biblioteca::cauta_frecventa(int frecventa) const
{
    for (Biblioteca::PubContainer::const_iterator cit = publicatii.cbegin();
         cit != publicatii.cend(); ++cit)
        if (static_cast<Revista *>(*cit)->get_frecventa() == frecventa)
            return const_cast<const Revista &>(*static_cast<Revista *>(*cit));
    return rNULL;
}


void Biblioteca::dump(const char * fname) const
{
    // salveaza in fisier continutul bibliotecii
    ofstream fout(fname);

    for (Biblioteca::PubContainer::const_iterator cit = publicatii.cbegin();
         cit != publicatii.cend(); ++cit) {
        // salveaza datele comune, fara uid
        int tip = (*cit)->get_tip();
        fout << tip << endl;
        fout << (*cit)->get_titlu() << endl;
        fout << (*cit)->get_editura() << endl;
        fout << (*cit)->get_an() << endl;
        fout << (*cit)->get_tiraj() << endl;

        // si acum informatiile particulare
        if (tip == 1) {
            const Carte::AutorContainer & autori = static_cast<Carte *>(*cit)->get_autori();
            copy(autori.cbegin(), autori.cend(), ostream_iterator<string>(fout, " "));
            fout << endl;
        } else {
            Revista * revPnt = static_cast<Revista *>(*cit);
            fout << revPnt->get_numar() << endl;
            fout << revPnt->get_frecventa() << endl;
        }
        fout << endl;
    }

    fout.close();
}

void Biblioteca::load(const char * fname)
{
    // golim continutul
    clear();
    dCar = dRev = 0;

    // incarca dintr-un fisier datele ce reprezinta continutul bibliotecii
    ifstream fin(fname);

    int tip;
    while (fin >> tip) {
        // luam datele comune
        string titlu, editura;
        int an, tiraj;

        Carte::AutorContainer autori;
        int numar, frecventa;

        fin >> titlu >> editura >> an >> tiraj;
        if (tip == 1) {
            // orice carte are cel putin un autor
            do {
                string autor;
                fin >> autor;
                autori.push_back(autor);
                // extragem si ignoram spatiile (nu si '\n')
                while (fin.peek() == ' ')
                    fin.ignore();
            } while (!isspace(fin.peek()));
            adauga(Carte(titlu, editura, an, tiraj, autori));
        } else {
            fin >> numar >> frecventa;
            adauga(Revista(titlu, editura, an, tiraj, numar, frecventa));
        }
    }

    fin.close();
}


istream & operator>>(istream & in, Publicatie & publicatie)
{
    publicatie.valid = true;
    in >> publicatie.titlu >> publicatie.editura \
       >> publicatie.an >> publicatie.tiraj;
    return in;
}

ostream & operator<<(ostream & out, const Publicatie & publicatie)
{
    if (!publicatie.valid)
        return out;
    out << "Publicatia #" << publicatie.uid << endl;
    out << "Titlu: " << publicatie.titlu << endl;
    out << "Editura: " << publicatie.editura << endl;
    out << "An: " << publicatie.an << endl;
    out << "Tiraj: " << publicatie.tiraj << endl;
    return out;
}

istream & operator>>(istream & in, Carte & carte)
{
    in >> dynamic_cast<const Publicatie &>(carte);
    copy(istream_iterator<string>(in), istream_iterator<string>(),
         back_inserter<Carte::AutorContainer>(carte.autori));
    return in;
}

ostream & operator<<(ostream & out, const Carte & carte)
{
    out << "[Carte]" << endl \
        << dynamic_cast<const Publicatie &>(carte);
    return out;
}

istream & operator>>(istream & in, Revista & revista)
{
    in >> dynamic_cast<const Publicatie &>(revista);
    in >> revista.numar >> revista.frecventa;
    return in;
}

ostream & operator<<(ostream & out, const Revista & revista)
{
    out << "[Revista]" << endl \
        << dynamic_cast<const Publicatie &>(revista);
    return out;
}
