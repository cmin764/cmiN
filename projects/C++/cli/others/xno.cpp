#include <iostream>
using namespace std;


/* tabla de X si 0
   0 inseamna ca celula este libera
   1 ocupata de utilizator (X)
   2 ocupata de computer (0) */
int tabla[3][3];


void show()
{
    /// Functia de afisare a tablei.
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
            if (tabla[i][j] == 1)
                cout << "X ";
            else if (tabla[i][j] == 2)
                cout << "0 ";
            else
                cout << "- ";
        cout << endl;
    }
    cout << endl;
}


int verifica()
{
    int gata = 0;
    // daca e vreo linie completa
    for (int i = 0; i < 3; ++i)
        if (tabla[i][0] == tabla[i][1] &&
            tabla[i][1] == tabla[i][2] &&
            tabla[i][0])
                gata = tabla[i][0];
    // daca e vreo coloana completa
    for (int j = 0; j < 3; ++j)
        if (tabla[0][j] == tabla[1][j] &&
            tabla[1][j] == tabla[2][j] &&
            tabla[0][j])
                gata = tabla[0][j];
    // daca e vreo diagonala
    if (tabla[0][0] == tabla[1][1] &&
        tabla[1][1] == tabla[2][2] &&
        tabla[0][0])
            gata = tabla[0][0];
    if (tabla[0][2] == tabla[1][1] &&
        tabla[1][1] == tabla[2][0] &&
        tabla[0][2])
            gata = tabla[0][2];

    if (gata == 1) {
        cout << "Utilizatorul a castigat" << endl;
        return 1;
    } else if (gata == 2) {
        cout << "Computerul a castigat" << endl;
        return 2;
    }

    // probabil e egalitate
    int liber = 0;
    for (int i = 0; i < 3 && !liber; ++i)
        for (int j = 0; j < 3 && !liber; ++j)
            if (tabla[i][j])
                continue;
            else
                liber = 1;
    if (!liber) {
        cout << "Egalitate" << endl;
        return 3;
    }

    return 0;    // mai e de jucat
}


int main()
{
    int gata = 0;
    /* cat timp jocul nu este gata, luam decizii,
       o data utilizatorul, o data calculatorul */
    while (gata == 0) {
        int ok = 0;
        do {
            /* cerem utilizatorului sa puna X pana cand
               alege o linie si o coloana valida */
            int linie, coloana;
            cout << "L C: ";
            cin >> linie >> coloana;
            --linie; --coloana;
            if (linie < 0 || linie > 2 ||    // valori invalida
                coloana < 0 || coloana > 2 ||     // sau
                tabla[linie][coloana])    // daca celula e ocupata
                    continue;    // continuam cu interogarea
            // celula nu e ocupata, deci o ocupam cu alegerea utilizatorului
            ok = 1;    // alegere corecta
            tabla[linie][coloana] = 1;
        } while (!ok);

        show();    // afisam tabla
        gata = verifica();    // verifica daca nu cumva s-a terminat jocul
        if (gata)
            continue;    // s-a terminat
        // jocul nu e gata, urmeaza ca si computerul sa faca o decizie
        /* pentru fiecare celula se verifica daca exista doi de 1 pe
           aceeasi dreapta si daca da, atunci acolo va pune "0", adica 2 */
        int ales = 0;    // daca a ales unde sa puna 2
        for (int i = 0; i < 3 && !ales; ++i)
            for (int j = 0; j < 3 && !ales; ++j) {
                if (tabla[i][j])
                    continue;    // celula e ocupata, deci mergem mai departe

                // verificam posibilii vecini

                // tratam cazurile cand locul liber e la mijloc
                if (j == 1 && tabla[i][j - 1] == 1 &&
                              tabla[i][j + 1] == 1)
                    // vecinii din stanga si din dreapta
                    ales = 1;
                // analog
                if (i == 1 && tabla[i - 1][j] == 1 &&
                              tabla[i + 1][j] == 1)
                    // vecinii de sus si de jos
                    ales = 1;
                if (i == 1 && j == 1) {    // luam in calcul si diagonalele
                    if (tabla[i - 1][j - 1] == 1 &&
                        tabla[i + 1][j + 1] == 1)
                            ales = 1;
                    else if (tabla[i - 1][j + 1] == 1 &&
                             tabla[i + 1][j - 1] == 1)
                            ales = 1;
                }

                // acum tratam cazurile cand vecinii pot fi unul dupa altul
                int dirl[8] = {-1, 1, 0, 0, 1, -1, -1, 1};   // directiile posibile pe linie
                int dirc[8] = {0, 0, -1, 1, 1, -1, 1, -1};   // si pe coloana
                for (int d = 0; d < 8 && !ales; ++d) {
                    /* acum aplicam aceeasi directie pentru a afla
                       vecinul celulei curente, dar si pe vecin pentru
                       a afla vecinul vecinului */
                    int i1 = i + dirl[d], j1 = j + dirc[d];
                    int i2 = i1 + dirl[d], j2 = j1 + dirc[d];

                    /* daca nu sunt posibile in acelasi timp ambele
                       directii, atunci nu avem cum sa testam cazul */
                    if (i1 < 0 || i1 > 2 || i2 < 0 || i2 > 2 ||
                        j1 < 0 || j1 > 2 || j2 < 0 || j2 > 2)
                            continue;
                    // vecinii sunt posibili
                    if (tabla[i1][j1] == 1 && tabla[i2][j2] == 1)
                        ales = 1;
                }

                if (ales)
                    tabla[i][j] = 2;
            }

        if (!ales) {
            /* daca nu am gasit o varianta prioritara atunci
               alegem prima celula libera */
            for (int i = 0; i < 3 && !ales; ++i)
                for (int j = 0; j < 3 && !ales; ++j) {
                    if (tabla[i][j])
                        continue;
                    tabla[i][j] = 2;
                    ales = 1;
                }
        }

        show();
        gata = verifica();
    }
    return 0;
}
