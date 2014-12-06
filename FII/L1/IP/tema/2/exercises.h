
// Tema 2

#include <iostream>
#include <cmath>
using namespace std;

#define MAX_ARRAY_LENGTH 100

struct Complex
{
	double a;
	double b;
};

struct DiophantineEquation
{
	int a;
	int b;
	int c;
};

// x = ax + bx * k, y = ay + by * k, pentru orice k intreg
// daca ecuatia are solutii, atunci hasSolutions trebuie sa fie true, iar ax, bx, ay, si by trebuie setati corespunzator
// altfel, hasSolutions trebuie sa fie false, iar ax, bx, ay si by trebuie sa fie 0
struct DiophantineSolution
{
	bool hasSolutions;
	int ax;
	int bx;
	int ay;
	int by;
};

struct Vector
{
	unsigned int length;
	int values[MAX_ARRAY_LENGTH];
};

struct Triangle
{
	double a;
	double b;
	double c;
};

enum TriangleShapeByAngle
{
	NoAngleTriangleType,
	AcuteTriangle,
	RightTriangle,
	ObtuseTriangle
};

enum TriangleShapeBySide
{
	NoSideTriangleType,
	EquilateralTriangle,
	IsoscelesTriangle,
	ScaleneTriangle
};

// Exercitiul 1

// Pentru un numar natural n, sa se determine numarul de zero-uri de la sfarsitul numarului n! (factorialul lui n).
unsigned int computeFactorial(unsigned int number);
unsigned int countTrailingZeroes(unsigned int number);

// Exercitiul 2

// a)

// Sa se determine maximul a trei numere.
double max(double a, double b, double c);

// Sa se determine minimul a trei numere.
double min(double a, double b, double c);

// b)

// Sa se determine media aritmetica a trei numere.
double arithmeticMean(double a, double b, double c);

// Sa se determine media geometrica a trei numere.
double geometricMean(double a, double b, double c);

// Sa se determine media armonica a trei numere.
double harmonicMean(double a, double b, double c);

// c)

// Sa se determine daca trei numere pot constitui laturile unui triunghi.
bool canBeTriangle(double a, double b, double c);

// Sa se clasifice triunghiul dupa unghiuri.
TriangleShapeByAngle classifyTriangleByAngle(Triangle t);

// Sa se clasifice triunghiul dupa laturi.
TriangleShapeBySide classifyTriangleBySide(Triangle t);

// Sa se calculeze perimetrul unui triunghi.
double computePerimeter(Triangle t);

// Sa se calculeze aria unui triunghi.
double computeArea(Triangle t);

// Sa se determine lungimea celei mai lungi mediane.
double getMaxMedian(Triangle t);

// Sa se determine lungimea celei mai scurte inaltimi.
double getMinHeight(Triangle t);

// d)

// Sa se determine toate numerele ale caror patrate se afla intre cea mai mica si cea mai mare valoare absoluta a trei numere.
Vector getSquares(double a, double b, double c);

// Sa se determine toate numerele ale caror cuburi se afla intre cea mai mica si cea mai mare valoare a trei numere.
Vector getCubes(double a, double b, double c);

// e)

// Sa se generalizeze subpunctul d) considerand puterea a n-a.
Vector getNthRoots(double a, double b, double c, int n);

// f)

// Sa se determine solutiile intregi ale ecuatiei ax + by = c. Hint: Euclid Extins, https://www.cs.cmu.edu/~adamchik/21-127/lectures/divisibility_5_print.pdf
DiophantineSolution solveDiophantineEquation(DiophantineEquation e);

/* Exercitiul 3 */

// Sa se calculeze suma a doua numere complexe.
Complex sum(Complex c1, Complex c2);

// Sa se calculeze produsul a doua numere complexe.
Complex product(Complex c1, Complex c2);
