#ifndef BIBLIOTECA_HPP_INCLUDED
#define BIBLIOTECA_HPP_INCLUDED


#include <string>
#include <list>
#include <vector>
#include <iostream>


using namespace std;


class Publicatie {

    /**
     * Clasa de baza folosita pentru crearea
     * si costumizarea publicatiilor specifice
     * ca `Revista` sau `Carte` ce contine
     * informatiile comune.
     */

    static int UID;

    void gen_uid();

    friend istream & operator>>(istream &, Publicatie &);
    friend ostream & operator<<(ostream &, const Publicatie &);

protected:
    int uid;
    /* 0 - publicatie
       1 - carte
       2 - revista */
    int tip;
    bool valid;

    string titlu, editura;
    int an, tiraj;

public:
    Publicatie();
    Publicatie(const string &, const string &, int, int);
    Publicatie(const Publicatie &);

    int get_uid() const;
    int get_tip() const;
    const string & get_titlu() const;
    const string & get_editura() const;
    int get_an() const;
    int get_tiraj() const;
    bool get_valid() const;

    pair<bool, bool> operator==(const Publicatie &) const;
};


class Carte: public Publicatie {

public:
    typedef vector<string> AutorContainer;

private:
    AutorContainer autori;

    static inline bool predicate(const string &, const string &);

    friend istream & operator>>(istream &, Carte &);
    friend ostream & operator<<(ostream &, const Carte &);

public:

    Carte();
    Carte(const string &, const string &, int, int,
          const vector<string> &);
    Carte(const Carte &);

    const AutorContainer & get_autori() const;

    pair<bool, bool> operator==(const Carte &) const;
};


class Revista: public Publicatie {

    int numar, frecventa;

    friend istream & operator>>(istream &, Revista &);
    friend ostream & operator<<(ostream &, const Revista &);

public:
    Revista();
    Revista(const string &, const string &, int, int,
            int, int);
    Revista(const Revista &);

    int get_numar() const;
    int get_frecventa() const;

    pair<bool, bool> operator==(const Revista &) const;
};


class Biblioteca {

public:
    typedef list<Publicatie *> PubContainer;
    typedef pair<PubContainer::iterator, PubContainer::iterator> finditer_type;

private:
    string nume;
    PubContainer publicatii;

    int dCar, dRev;

public:
    static const Publicatie pNULL;
    static const Carte cNULL;
    static const Revista rNULL;

    Biblioteca(const string &);
    Biblioteca(const string &, const Biblioteca &);
    ~Biblioteca();

    void clear();
    const PubContainer & get_container() const;
    int get_dCar() const;    // numar carti distincte
    int get_dRev() const;    // numar reviste distincte

    int cantitate() const;
    finditer_type exista(const Publicatie *);

    bool adauga(const Carte &);
    bool adauga(const Revista &);

    bool elimina(const Carte &);
    bool elimina(const Revista &);

    const Publicatie & cauta_titlu(const string &) const;
    const Publicatie & cauta_editura(const string &) const;
    const Publicatie & cauta_an(int) const;
    const Publicatie & cauta_tiraj(int) const;

    const Carte & cauta_autori(const Carte::AutorContainer &) const;

    const Revista & cauta_numar(int) const;
    const Revista & cauta_frecventa(int) const;

    void dump(const char *) const;
    void load(const char *);
};


istream & operator>>(istream &, Publicatie &);
ostream & operator<<(ostream &, const Publicatie &);

istream & operator>>(istream &, Carte &);
ostream & operator<<(ostream &, const Carte &);

istream & operator>>(istream &, Revista &);
ostream & operator<<(ostream &, const Revista &);


#endif // BIBLIOTECA_HPP_INCLUDED
