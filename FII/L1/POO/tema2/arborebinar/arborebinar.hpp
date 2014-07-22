#ifndef ARBOREBINAR_HPP_INCLUDED
#define ARBOREBINAR_HPP_INCLUDED


#include <vector>
#include <string>
#include <stack>


using namespace std;


class ArboreBinar {
    char cOperator;
    double dNumber;

    vector<ArboreBinar*> fii;
    bool valid;

    ArboreBinar(double); // constructor pentru initializarea unui nod frontiera
    ArboreBinar(char); // constructor pentru initializarea unui nod intern
    void init(char);

    void dfs(string &, ArboreBinar &, int);
    double eval(ArboreBinar &);

    // metoda pentru transformarea in forma postfixata a unei expresii
    static string InfixToPostfix(const string& expresie);

public:

    // constructor pentru initializarea nodului radacina
    ArboreBinar( const string& expresie );

    // returneaza true daca arborele a fost construit (expresia era corecta)
    bool EsteValid() const;

    // returneaza expresia rezultata in urma parcurgerii arborelui
    // (inordine, preordine, postordine)
    string Parcurgere( int nCodParcurgere );

    // returneaza rezultatul evaluarii arborelui
    double Evalueaza();
};


#endif // ARBOREBINAR_HPP_INCLUDED
