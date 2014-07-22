#include <iostream>

#include "biblioteca.hpp"

using namespace std;


int main()
{
    // cream biblioteca
    Biblioteca b1("b1");
    Carte carte("t1", "e1", 1900, 100, {"A1", "A2"});

    {
        cout << b1.adauga(Carte("t1", "e1", 1900, 100, {"A1", "A2"})) << endl;
        // incercam sa adaugam acelasi articol
        cout << b1.adauga(carte) << endl;
        // si e ok fiindca e o alta carte la fel, dar daca introducem aceeasi carte:
        cout << b1.adauga(carte) << endl;
        // va arata 0 (fiindca are acelasi uid)
    }

    {
        Revista revista("t1", "e2", 1800, 10, 13, 128);
        b1.adauga(revista);

        cout << revista << carte;

        cout << b1.elimina(revista) << endl;
        cout << b1.elimina(revista) << endl;
    }

    {
        // adauga publicatie invalida/neinitializata
        cout << b1.adauga(Carte()) << endl;

        Carte carteCautata(b1.cauta_autori({"A1", "A2"}));
        if (carteCautata.get_valid())
            cout << carteCautata;
        else
            cout << "Cartea nu a fost gasita";
    }

    Revista revista("t1", "e2", 1801, 10, 13, 128);
    b1.adauga(revista);

    b1.dump("biblioteca.txt");
    b1.load("biblioteca.txt");

    Revista revistaCautata(static_cast<const Revista &>(b1.cauta_an(1801)));
    if (revistaCautata.get_valid())
        cout << revistaCautata;
    else
        cout << "Revista nu a fost gasita" << endl;
    cout << b1.get_dRev() << endl;
    return 0;
}
