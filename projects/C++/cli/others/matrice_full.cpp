// Matrice: adunare, scadere, inmultire, putere, transpusa, urma
#include <iostream>
using namespace std;

int main()
{
    int i, j, k, l1, c1, c2, ans;
    long m1[100][100], m2[100][100], m3[100][100];
    // + - // ============================================================
    cout << "Adunati / Scadeti 2 matrice (1/0)? ";
    cin >> ans;
    if (ans) {
        cout << "Numar linii matrice: ";
        cin >> l1;
        cout << "Numar coloane matrice: ";
        cin >> c1;
        cout << "Elemente matrice1...\n";
        for (i = 0; i < l1; i++) {
            for (j = 0; j < c1; j++) {
                cin >> m1[i][j];
            }
            cout << "\n";
        }
        cout << "Elemente matrice2...\n";
        for (i = 0; i < l1; i++) {
            for (j = 0; j < c1; j++) {
                cin >> m2[i][j];
            }
            cout << "\n";
        }
        cout << "Adunati (1/0)? ";
        cin >> ans;
        if (ans) {
            for (i = 0; i < l1; i++) {
                for (j = 0; j < c1; j++) {
                    cout << m1[i][j] + m2[i][j] << " ";
                }
                cout << "\n";
            }
        }
        cout << "Scadeti (1/0)? ";
        cin >> ans;
        if (ans) {
            for (i = 0; i < l1; i++) {
                for (j = 0; j < c1; j++) {
                    cout << m1[i][j] - m2[i][j] << " ";
                }
                cout << "\n";
            }
        }
    }
    // * // ============================================================
    cout << "Inmultiti 2 matrice (1/0)? ";
    cin >> ans;
    if (ans) {
        cout << "Numar linii matrice1: ";
        cin >> l1;
        cout << "Numar coloane matrice1 si linii matrice2: ";
        cin >> c1;
        cout << "Numar coloane matrice2: ";
        cin >> c2;
        cout << "Elemente matrice1...\n";
        for (i = 0; i < l1; i++) {
            for (j = 0; j < c1; j++) {
                cin >> m1[i][j];
            }
            cout << "\n";
        }
        cout << "Elemente matrice2...\n";
        for (i = 0; i < c1; i++) {
            for (j = 0; j < c2; j++) {
                cin >> m2[i][j];
            }
            cout << "\n";
        }
        for (i = 0; i < l1; i++) {
            for (k = 0; k < c2; k++) {
                m3[0][0] = 0;
                for (j = 0; j < c1; j++) {
                    m3[0][0] += m1[i][j] * m2[j][k];
                }
                cout << m3[0][0] << " ";
            }
            cout << "\n";
        }
    }
    // ^ // ============================================================
    cout << "Ridicati la putere o matrice (1/0)? ";
    cin >> ans;
    if (ans) {
        cout << "Numar linii si coloane matrice: ";
        cin >> l1;
        cout << "Elemente matrice...\n";
        for (i = 0; i < l1; i++) {
            for (j = 0; j < l1; j++) {
                cin >> m1[i][j];
                m2[i][j] = m1[i][j];
            }
            cout << "\n";
        }
        cout << "Putere: ";
        cin >> c1;
        while (c1-- > 1) {
            for (i = 0; i < l1; i++) {
                for (k = 0; k < l1; k++) {
                    m3[i][k] = 0;
                    for (j = 0; j < l1; j++) {
                        m3[i][k] += m1[i][j] * m2[j][k];
                    }
                }
            }
            for (i = 0; i < l1; i++) {
                for (j = 0; j < l1; j++) {
                    m1[i][j] = m3[i][j];
                }
            }
        }
        for (i = 0; i < l1; i++) {
            for (j = 0; j < l1; j++) {
                cout << m3[i][j] << " ";
            }
            cout << "\n";
        }
    }
    // t // ============================================================
    cout << "Aflati transpusa unei matrice (1/0)? ";
    cin >> ans;
    if (ans) {
        cout << "Numar linii matrice: ";
        cin >> l1;
        cout << "Numar coloane matrice: ";
        cin >> c1;
        cout << "Elemente matrice...\n";
        for (i = 0; i < l1; i++) {
            for (j = 0; j < c1; j++) {
                cin >> m1[j][i];
            }
            cout << "\n";
        }
        for (i = 0; i < c1; i++) {
            for (j = 0; j < l1; j++) {
                cout << m1[i][j] << " ";
            }
            cout << "\n";
        }
    }
    // tr // ============================================================
    cout << "Aflati urma unei matrice (1/0)? ";
    cin >> ans;
    if (ans) {
        cout << "Numar linii si coloane matrice: ";
        cin >> l1;
        cout << "Elemente matrice...\n";
        m2[0][0] = 0;
        for (i = 0; i < l1; i++) {
            for (j = 0; j < l1; j++) {
                cin >> m1[i][j];
                if (i == j) {
                    m2[0][0] += m1[i][j];
                }
            }
            cout << "\n";
        }
        cout << m2[0][0] << "\n";
    }
    system("pause >nul");
    return 0;
}
