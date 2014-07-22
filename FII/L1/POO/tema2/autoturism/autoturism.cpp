#include <iostream>
#include <cstdlib>
#include <ctime>

#include <unistd.h>

#include "autoturism.hpp"


using namespace std;


void Motor::start()
{
    // pornim motorul
    sleep(1.3);
    if (rand() % 2)    // poate porni din prima sau nu
        status = true;
}

void Motor::stop()
{
    // il oprim
    status = false;
}

bool Motor::stare() const
{
    return status;
}


void Electromotor::start(Motor & motor)
{
    /* incearca sa porneasca motorul pana
       porneste cu succes */
    int i = 1;
    while (!motor.stare()) {
        sleep(0.2);
        cout << "Incercarea #" << i << endl;
        ++i;
        motor.start();
    }
    // motorul a fost pornit
}


SistemPornire::SistemPornire(): complet(false) {}

SistemPornire::SistemPornire(Motor & m, Electromotor & e): \
               m(m), e(e), complet(true) {}

void SistemPornire::porneste_motor()
{
    // folosim electromotorul pentru a porni motorul
    e.start(m);
}

void SistemPornire::opreste_motor()
{
    cout << "Opreste motorul." << endl;
    m.stop();
}

bool SistemPornire::este_complet() const
{
    return complet;
}


SistemPornireCuPreincalzire::SistemPornireCuPreincalzire(): \
                             SistemPornire() {}

SistemPornireCuPreincalzire::SistemPornireCuPreincalzire(Motor & m,
                                                         Electromotor & e): \
                             SistemPornire(m, e) {}

void SistemPornireCuPreincalzire::porneste_motor()
{
    cout << "Incalzeste carburantul..." << endl;
    sleep(3);
    SistemPornire::porneste_motor();
}


Anvelopa::Anvelopa(char tip): tip(tip) {}

char Anvelopa::get_tip() const
{
    return tip;
}


Autoturism::Autoturism(bool cuPreincalzire, char tip): pornit(false), drumuri(0),
                                                        anvelope(4, Anvelopa(tip))
{
    
    if (cuPreincalzire)
        sistemPornire = new SistemPornireCuPreincalzire(motor, electromotor);
    else
        sistemPornire = new SistemPornire(motor, electromotor);
    cout << "Autoturism creat cu urmatoarele dotari: " << endl;
    cout << "Anvelope: ";
    for (unsigned int i = 0; i < anvelope.size(); ++i)
        cout << anvelope[i].get_tip();
    cout << endl;
    cout << "Preincalzire: ";
    if (cuPreincalzire)
        cout << "Da";
    else
        cout << "Nu";
    cout << endl;

	// seed unic la fiecare instantiere
	srand(time(NULL));
}

Autoturism::~Autoturism()
{
    delete sistemPornire;
}

void Autoturism::porneste_autoturism()
{
    cout << "Se verifica starea autoturismului..." << endl;
    sleep(1);
    if (sistemPornire->este_complet()) {
        cout << "Autoturism OK." << endl;
        sleep(1);
        cout << "Autoturism pornit?" << endl;
        if (pornit) {
            cout << "Da. Autoturismul deja este pornit!" << endl;
            return;
        }
        cout << "Se porneste motorul..." << endl;
        sistemPornire->porneste_motor();
        pornit = true;
        cout << "Motorul a fost pornit." << endl;
    } else {
        cout << "Autoturism invalid." << endl;
    }
}

void Autoturism::condu_la_destinatie()
{
    cout << "Autoturism pornit?" << endl;
    if (!pornit) {
        cout << "Nu. Autoturismul trebuie pornit!" << endl;
        return;
    }
    sleep(0.6);
    if (drumuri == 2) {
        drumuri = 0;
        cout << "Schimba anvelopele..." << endl;
        char tip = anvelope[0].get_tip();
        sleep(0.3);
        anvelope.assign(4, Anvelopa(tip));
        sleep(0.8 * 4);
    }
    cout << "Ia-o din loc!" << endl;
    sleep(1.2);
    int nrManevre = rand() % 10;
    while (nrManevre--) {
        sleep(0.3 * (rand() % 10 + 1));
        int manevra = rand() % 7;
        switch (manevra) {
        case 0:
            cout << "M: Stanga" << endl;
            break;
        case 1:
            cout << "M: Dreapta" << endl;
            break;
        case 2:
            cout << "M: Accelereaza" << endl;
            break;
        case 3:
            cout << "M: Franeaza" << endl;
            break;
        case 4:
            cout << "M: Intoarce" << endl;
            break;
		case 5:
			cout << "M: Claxon" << endl;
			break;
        case 6:
            cout << "M: Merge cu spatele" << endl;
        }
    }
    cout << "Autoturismul a ajuns la destinatie." << endl;
    ++drumuri;
}

void Autoturism::parcheaza_autoturism()
{
    cout << "Autoturism pornit?" << endl;
    if (!pornit) {
        cout << "Nu. Autoturismul nu este pornit." << endl;
        return;
    }
    cout << "Cauta loc de parcare..." << endl;
    sleep(2);
    if (rand() % 2) {
        cout << "Loc de parcare gasit!" << endl;
        sleep(0.8);
        if (rand() % 2)
            cout << "Parcheaza lateral." << endl;
        else
            cout << "Parcheaza cu spatele." << endl;
            sleep(2);
    } else {
        cout << "Stationeaza pe bordura din dreapta :)." << endl;
        sleep(1);
    }

    // acum trebuie oprit motorul
    cout << "Las-o-n prima treapta." << endl;
    sistemPornire->opreste_motor();
    sleep(0.5);
    pornit = false;
    cout << "Trage frana de mana si scoate centura!" << endl;
}
