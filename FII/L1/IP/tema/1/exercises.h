#include <iostream>
#include <cmath>
using namespace std;

#define MAX_ARRAY_LENGTH 100

struct vector
{
	unsigned int length;
	int values[MAX_ARRAY_LENGTH];
};

struct matrix
{
	unsigned int lines;
	unsigned int columns;
	int values[MAX_ARRAY_LENGTH][MAX_ARRAY_LENGTH];
};

struct sequence
{
	unsigned int startPosition;
	unsigned int length;
};

struct point
{
	double x;
	double y;
};

struct equation
{
	double a;
	double b;
	double c;
};

struct date
{
	unsigned int year;
	unsigned int month;
	unsigned int day;
};

/* Tema 1 */

/* Exercitiul 1
   Scrieti o functie care sa calculeze suma cifrelor unui numar natural.
*/

unsigned int computeDigitSum(unsigned int number);

/* Exercitiul 2
   Scrieti o functie care verifica daca un an este bisect.
*/

bool isLeap(unsigned int year);

/* Exercitiul 3
   Scrieti o functie care sa testeze daca un numar este palindrom.
   Un numar este palindrom daca citit de la dreapta la stanga este egal cu numarul citit de la stanga la dreapta.
   Exemple: 36463 este palindrom, dar 2646 nu este palindrom.
*/

bool isPalindrome(int number);

/* Exercitiul 4
   Scrieti un program, care, pentru o luna si un an date, calculeaza numarul de zile din luna respectiva
   (folositi o functie separata care verifica daca un an este bisect).
   Exemplu: pentru luna februarie din anul 2004, numarul de zile este 29.
*/

unsigned int computeNumberOfDays(unsigned int year, unsigned int month);

/* Exercitiul 5
   Scrieti o functie care calculeaza cifra de control a unui numar natural.
   Cifra de control se obtine calculand suma cifrelor numarului,
   apoi suma cifrelor numarului obtinut etc., pana se ajunge la o singura cifra.
   Exemplu: 4879 -> 28 -> 10 -> 1.
*/

unsigned int computeControlDigit(unsigned int number);

/* Exercitiul 6
   Spunem ca un numar natural este perfect daca este egal cu suma divizorilor sai strict mai mici decat el.
   Scrieti o functie care verifica daca un numar este perfect.
   Exemplu: 28 este un numar perfect deoarece 28 = 1 + 2 + 4 + 7 + 14. 
   Sa se determine toate numerele perfecte mai mici ca un numar natural n dat.
   Exemplu: pentru n = 1000, se vor determina numerele 6, 28, 496.
*/

bool isPerfect(unsigned int number);
vector getPerfects(unsigned int upperLimit);

/* Exercitiul 7
   Sa se testeze daca un numar este prim.
   Exemple: 1000003 este prim, dar 1000002 este compus deoarece este divizibil prin 3.
*/

bool isPrime(int number);

/* Exercitiul 8
   Doua numere naturale impare consecutive si prime se numesc numere prime gemene.
   Folosind testul de primalitate implementat anterior, determinati primele n perechi de numere prime gemene.
   Exemplu: Primele n = 3 perechi de numere prime gemene sunt (3, 5), (5, 7) si (11, 13).
*/

bool areTwinPrimes(unsigned int number1, unsigned int number2);
matrix getTwinPrimes(unsigned int count);

/* Exercitiul 9
   Se citeste un tablou de numere intregi.
   Scrieti o functie care determina diferenta maxima (in modul) dintre oricare doua elemente ale vectorului.
   Exemplu: pentru tabloul (1, 3, 2, 7, 11, 3, 2), diferenta maxima (in modul) este 12. 
*/

unsigned int getMaxDifference(vector v);

/* Exercitiul 10
   Se citeste un tablou de numere intregi.
   Sa se determine, printr-o singura parcurgere a sa, pozitia de inceput si lungimea celei mai lungi secvente de elemente egale.
   Daca exista mai multe secvente de lungimi egale, se va determina secventa cu pozitia de inceput minima.
   Exemplu: pentru tabloul (1, 2, 3, 3, 3, 2, 1, 5, 5, 5), se vor determina pozitia 2 si lungimea 3.
*/

sequence getMaxSequence(vector v);

/* Exercitiul 11
   Se da un vector de numere intregi.
   Sa se determine subsecventa pentru care suma elementelor componente este maxima.
   Daca exista mai multe subsecvente cu aceasta proprietate, se va determina ultima subsecventa gasita.
   Exemplu: pentru tabloul (2, 3, 4, 2, 9, 2, 1, 7, 3), subsecventa este (9, 2, 1, 7). 
*/

sequence getMaxSumSequence(vector v);

/* Exercitiul 12
   Se citeste un tablou de numere intregi.
   Sa se rearanjeze elementele astfel incat cele pare sa apara inaintea celor impare.
   In cadrul subsecventei de numere pare, respectiv impare, elementele trebuie sa apara in ordinea in care erau in tabloul initial.
   Exemplu: tabloul (2, 3, 4, 2, 9, 2, 1, 7, 3) va fi rearanjat in (2, 4, 2, 2, 3, 9, 1, 7, 3).
*/

vector orderElements(vector v);

/* Exercitiul 13
   Se considera un tablou cu n elemente.
   Sa se decida daca exista un element majoritar (cu numarul de aparitii mai mare decat n/2).
*/

bool containsMajorElement(vector v);

/* Exercitiul 14
   Se considera o matrice patratica cu n elemente.
   Sa se interschimbe liniile si coloanele acesteia astfel incat, in matricea finala, elementele de pe diagonala principala sa fie in ordine descrescatoare.
   Sa se afiseze matricea initiala si matricea dupa fiecare operatie.
*/

matrix sortDiagonalElements(matrix m);

/* Exercitiul 15
   Scrieti o functie care citeste elementele unei matrici patratice de dimensiune n.
   Afisati sirul format prin parcurgerea acesteia in spirala, pornind din coltul stanga sus catre dreapta pana in centrul matricei.
*/

vector getSpiralVector(matrix m);

/* Exercitiul 16
   Sa se defineasca un tip pentru reprezentarea datelor calendaristice.
   Sa se scrie o functie care primeste la intrare o data calendaristica si returneaza succesorul acesteia.
   Exemplu: succesorul datei "31.10.2014" este "1.11.2014".
*/

date getNextDate(date currentDate);

/* Exercitiul 17
   Sa se determine ecuatia unei drepte care trece prin doua puncte in plan.
   Exemplu: pentru punctele (2, 1) si (5, 7), ecuatia dreptei este 2x â€“ y â€“ 3 = 0.
   Precizia pentru a, b si c va fi de 2 zecimale.
   Ecuatia va fi redusa.
*/

equation computeEquation(point point1, point point2);