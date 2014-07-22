#ifndef AUTOTURISM_HPP_INCLUDED
#define AUTOTURISM_HPP_INCLUDED


#include <vector>


using namespace std;


class Motor {

    /* 1 - pornit
       0 - oprit */
    bool status;

public:
    void start();
    void stop();
    bool stare() const;
};


class Electromotor {

public:
    void start(Motor &);
};


class SistemPornire {

protected:
    Motor m;
    Electromotor e;

    bool complet;

public:
    SistemPornire();
    SistemPornire(Motor &, Electromotor &);

    virtual void porneste_motor();
    void opreste_motor();

    bool este_complet() const;
};


class SistemPornireCuPreincalzire: public SistemPornire {

public:
    SistemPornireCuPreincalzire();
    SistemPornireCuPreincalzire(Motor &, Electromotor &);

    void porneste_motor();
};


class Anvelopa {

    /* [v]ara
       [i]arna */
    char tip;

public:
    Anvelopa(char);

    char get_tip() const;
};


class Autoturism {

    bool pornit;
    int drumuri;

    Electromotor electromotor;
    Motor motor;
    SistemPornire * sistemPornire;
    vector<Anvelopa> anvelope;

public:
    Autoturism(bool, char);
    ~Autoturism();

    void porneste_autoturism();
    void condu_la_destinatie();
    void parcheaza_autoturism();
};


#endif // AUTOTURISM_HPP_INCLUDED
