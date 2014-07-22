#include <iostream>
#include <sstream>
#include <iterator>
#include <stack>
#include <cstdio>
#include <algorithm>

#include "arborebinar.hpp"


#define DEBUG 0


using namespace std;
typedef stack<string> expr_type;


const string OPERS("+-*/");
expr_type split;


bool is_oper(char x)
{
    if (OPERS.find(x) != string::npos)
        return true;    // am gasit operator
    return false;
}

bool is_nr(const char * str)
{
    // asumand ca este sir valid terminat in NULL
    while (*str) {
        if (!((*str >= '0' && *str <= '9') || *str == '-' || \
              *str == '+'))
            return false;
        ++str;
    }
    return true;
}


void ArboreBinar::init(char op)
{
    // presupunem ca-i valid
    valid = true;

    // eliminam nodul curent
    split.pop();

    #if DEBUG
    cout << op << endl;
    #endif

    cOperator = op;

    // cream cei doi fii
    fii.resize(2);
    for (int i = 1; i >= 0; --i) {
        char peek = split.top().front();
        if (is_oper(peek)) {    // avem operator
            fii[i] = new ArboreBinar(peek);
            if (!fii[i]->valid) {
                valid = false;
                break;
            }
        } else {
            // sau numar
            const char * str = split.top().c_str();
            if (!is_nr(str)) {
                // numar invalid
                valid = false;
                break;
            }
            double tmpNr;
            sscanf(str, "%lf", &tmpNr);
            fii[i] = new ArboreBinar(tmpNr);
        }
    }
}

ArboreBinar::ArboreBinar(double leaf)
{
    valid = true;
    split.pop();
    #if DEBUG
    cout << leaf << endl;
    #endif
    cOperator = '\0';    // astfel marcam ca sigur nu e operator
    dNumber = leaf;
}


ArboreBinar::ArboreBinar(char op)
{
    init(op);
}


ArboreBinar::ArboreBinar(const string & expr)
{
    // golim vechea stiva
    while (!split.empty())
        split.pop();

    // alcatuim expresia postfixata
    string postfix = ArboreBinar::InfixToPostfix(expr);

    #if DEBUG
    cout << "Constructor: " << postfix << endl;
    #endif

    // scriem cuvintele in stiva
    istringstream sin(postfix);
    string token;
    while (sin >> token) {
        split.push(token);
    }

    init(split.top().front());
}


bool ArboreBinar::EsteValid() const
{
    if (!valid)
        return false;
    if (!fii.empty())
        return fii[0]->EsteValid() && fii[1]->EsteValid();
    return true;
}


void ArboreBinar::dfs(string & ret, ArboreBinar & root,
                      int mode)
{
    char str[32] = {0};
    if (!root.cOperator) {
        sprintf(str, "%lf ", root.dNumber);
        ret.append(str);
        return;
    } else {
        str[0] = root.cOperator;
        str[1] = ' ';
        str[2] = '\0';
    }

    if (mode == 0)
        ret.append(str);
    dfs(ret, *root.fii[0], mode);
    if (mode == 1)
        ret.append(str);
    dfs(ret, *root.fii[1], mode);
    if (mode == 2)
        ret.append(str);
}


string ArboreBinar::Parcurgere(int mode)
{
    string ret;
    dfs(ret, *this, mode);
    return ret;
}


double ArboreBinar::eval(ArboreBinar & root)
{
    if (root.fii.empty())
        return root.dNumber;
    else {
        double first, second;
        first = eval(*root.fii[0]);
        second = eval(*root.fii[1]);
        switch (root.cOperator) {
        case '+':
            return first + second;
        case '-':
            return first - second;
        case '*':
            return first * second;
        case '/':
            return first / second;
        }
    }
}


double ArboreBinar::Evalueaza()
{
    return eval(*this);
}


string ArboreBinar::InfixToPostfix(const string & expresie)
{
    // implementarea unui algoritm de tip shunting-yard

    stringstream stream;
    stream << expresie;

    stack<string> aStack;
    string postExpresie;
    char chSpace = ' ';

    while (stream) {
        string strNumar;
        string strOperator;

        // flux deschis simultan pentru scriere si citire
        // scriem expresia in flux

        char aChar = stream.peek();

        switch (aChar) {
        case ' ':
            stream.ignore();
            continue;

        case '.':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            stream >> strNumar;
            postExpresie += strNumar;
            postExpresie += chSpace;
            break;

        case '+' :
        case '-' :
            stream >> strOperator;
            // citim operatorul
            while ( ( ! aStack.empty() ) && \
                ( ( aStack.top() == "*" ) || ( aStack.top() == "/" ) || \
                ( aStack.top() == "+" ) || ( aStack.top() == "-" ))) {
                postExpresie += aStack.top();
                // scriem operatorul
                postExpresie += chSpace;
                aStack.pop();
                // eliminam din stiva
            }
            aStack.push( strOperator );
            break;

        case '*' :
        case '/' :
            stream >> strOperator;
            while ( ( ! aStack.empty() ) && \
                ( ( aStack.top() == "*" ) || ( aStack.top() == "/" ) )) {
                postExpresie += aStack.top();
                // scriem operatorul
                postExpresie += chSpace;
                aStack.pop();
                // eliminam din stiva
            }
            aStack.push( strOperator );
            // introducem operatorul in stiva
            break;

        case '(':
            // introducem operatorul in stiva
            // citim operatorul
            stream.ignore();
            aStack.push( "(" ); // introducem '(' in stiva
            break;
        case ')' :
            stream.ignore();
            while ( ( ! aStack.empty() ) && ( aStack.top() != "(" ) ) {
                postExpresie += aStack.top();
                // scriem in post-expresie
                postExpresie += chSpace;
                aStack.pop();
                // eliminam din stiva
            }
            aStack.pop();
            // eliminam '(' din stiva
            break;

        case EOF: continue;
        default: return "Eroare la parsarea expresiei!";
        }
    }

    // golim stiva
    while ( ! aStack.empty() ) {
        postExpresie += aStack.top();
        postExpresie += chSpace;
        aStack.pop();
    }

    return postExpresie;
}
