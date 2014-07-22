#include <iostream> // fluxul de intrare iesire (cin cout)
#include <fstream> // lucreaza cu fisierele
#include <string> // functii pentru siruri
using namespace std; // ca sa folosesti de ex. cout in loc de std::cout

void reverse(char * pChar, int len)
{ // definim functia reverse care returneaza nimic (void) si
    int i; // primeste ca parametri un pointer la caracter si un intreg
    char temp;
    for (i = 0; i < len / 2; i++) { // inlocuim toate caracterele din jumatatea
        temp = pChar[i]; // unui cuvant cu caracterele din jumatatea celuilalt cuvant
        pChar[i] = pChar[len - i - 1]; // astfel inversam literele intr-un cuvant
        pChar[len - i - 1] = temp; // cunoscandu-se atat pozitia lui in fraza cat si lungimea lui
    }
}

int main()
{ // functia principala
    int len, linelen; // declaram variabile pentru lungimi
    char line[128], * pChar; // linii citite din fisier si un manipulator
    ifstream myfile("tinv.in"); // deschidem fisierul de intrare cu numele tinv.in
    while (!myfile.eof()) { // atentie myfile este obiectul identificator
        myfile.getline(line, 127); // cat timp nu a ajuns cursorul la sfarsitul fisierului
        linelen = strlen(line); // citim caractere pana dam de '\n' sau sarim de 126
        line[linelen] = ' '; // ceva ajustari a liniei citite din fisier
        line[linelen + 1] = '\0';
        pChar = line; // atribuim pointerului adresa de memorie a primului caracter din vector
        while (*pChar) { // cat timp nu dam de null byte prelucram cuvintele
            len = 0;
            while (*pChar != ' ') { // identificam cuvintele stiind ca sunt separate de spatii
                len++; // si incrementam variabila pentru a afla lungimea lor
                pChar++;
            }
            reverse(pChar - len, len); // chemam functia pentru a prelucra cuvantul (inversare)
            pChar++;
        }
        cout << line << "\n"; // afisam linia prelucrata, adica cuvintele inversate si
    } // "\n" pentru mutarea cursorului pe urmatoarea linie
    myfile.close(); // inchidem fisierul prin functia close aplicata ca metoda pe obiect
    system("pause >nul"); // folosindu-ne de shell punem pauza pentru a vedea afisarea
    return 0; // returnam 0 aratand ca executia a decurs fara erori
}
