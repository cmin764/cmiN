#include <iostream>
#include <string>
#include <sstream>

#include "arborebinar.hpp"


using namespace std;


int main()
{
    cout << "Expresie: ";
    string expr;
    getline(cin, expr);
    ArboreBinar arbin(expr);
    cout << "Validitate: " << arbin.EsteValid() << endl;
    cout << "Parcurgere: " << arbin.Parcurgere(0) << endl;
    cout << "Evaluare: " << arbin.Evalueaza() << endl;
    return 0;
}
