#include "exercises.h"

#define PI 3.14159
#define EPS 0.001


unsigned int computeFactorial(unsigned int number)
{
    if (number > 1)
        return number * computeFactorial(number - 1);
    return 1;
}

unsigned int countTrailingZeroes(unsigned int number)
{
    unsigned int start = 5, zeros = 0;
    while (start <= number) {
        zeros += number / start;
        start *= 5;
    }
    return zeros;
}


double max(double a, double b, double c)
{
    double r1 = a > b ? a : b;
    return r1 > c ? r1 : c;
}

double min(double a, double b, double c)
{
    double r1 = a < b ? a : b;
    return r1 < c ? r1 : c;
}


double arithmeticMean(double a, double b, double c)
{
    return (a + b + c) / 3;
}

double geometricMean(double a, double b, double c)
{
    double prod = a * b * c, sign = 1;
    if (prod < 0)
        sign = -1;
    return sign * pow(fabs(prod), 1.0/3);
}

double harmonicMean(double a, double b, double c)
{
    return 3 / (1 / a + 1 / b + 1 / c);
}


int cmp(double a, double b)
{
    if (fabs(a - b) < EPS)
        return 0;
    if (a > b)
        return 1;
    return -1;
}

bool canBeTriangle(double a, double b, double c)
{
    if (a <= 0)
        return false;
    if (b <= 0)
        return false;
    if (c <= 0)
        return false;
    if (cmp(a, b + c) == 1)
        return false;
    if (cmp(b, a + c) == 1)
        return false;
    if (cmp(c, a + b) == 1)
        return false;
    return true;
}


TriangleShapeByAngle classifyTriangleByAngle(Triangle t)
{
    TriangleShapeByAngle trtype = NoAngleTriangleType;
    if (!canBeTriangle(t.a, t.b, t.c))
        return trtype;
    // c^2 = a^2 + b^2 - 2ab*cos(C) -> cos(C) = (a^2 + b^2 - c^2)/2ab
    double cosC = (pow(t.a, 2) + pow(t.b, 2) - pow(t.c, 2)) / (2 * t.a * t.b);
    double C = acos(cosC) * 180 / PI;
    double cosB = (pow(t.a, 2) + pow(t.c, 2) - pow(t.b, 2)) / (2 * t.a * t.c);
    double B = acos(cosB) * 180 / PI;
    double A = 180 - (B + C);
    if (A < 90 && B < 90 && C < 90) {
        trtype = AcuteTriangle;
    } else if (!cmp(A, 90) || !cmp(B, 90) || !cmp(C, 90)) {
        trtype = RightTriangle;
    } else if (A > 90 || B > 90 || C > 90) {
        trtype = ObtuseTriangle;
    }
    return trtype;
}

TriangleShapeBySide classifyTriangleBySide(Triangle t)
{
    if (!canBeTriangle(t.a, t.b, t.c))
        return NoSideTriangleType;
    if (!cmp(t.a, t.b) && !cmp(t.b, t.c))
        return EquilateralTriangle;
    if (!cmp(t.a, t.b) || !cmp(t.a, t.c) || !cmp(t.b, t.c))
        return IsoscelesTriangle;
    return ScaleneTriangle;
}

double computePerimeter(Triangle t)
{
    if (!canBeTriangle(t.a, t.b, t.c))
        return 0;
    return t.a + t.b + t.c;
}

double computeArea(Triangle t)
{
    if (!canBeTriangle(t.a, t.b, t.c))
        return 0;
    double s = computePerimeter(t) / 2;
    return sqrt(s * (s - t.a) * (s - t.b) * (s - t.c));
}

double getMedian(double a, double b, double c)
{
    return sqrt((2 * pow(b, 2) + 2 * pow(c, 2) - pow(a, 2)) / 4);
}

double getMaxMedian(Triangle t)
{
    if (!canBeTriangle(t.a, t.b, t.c))
        return 0;
    return max(getMedian(t.a, t.b, t.c), getMedian(t.b, t.a, t.c),
               getMedian(t.c, t.a, t.b));
}

double getMinHeight(Triangle t)
{
    if (!canBeTriangle(t.a, t.b, t.c))
        return 0;
    double darea = 2 * computeArea(t);
    double h1 = darea / t.a;
    double h2 = darea / t.b;
    double h3 = darea / t.c;
    return min(h1, h2, h3);
}

Vector getSquares(double a, double b, double c)
{
    return getNthRoots(a, b, c, 2);
}

Vector getCubes(double a, double b, double c)
{
    return getNthRoots(a, b, c, 3);
}

Vector getNthRoots(double a, double b, double c, int n)
{
    if (n % 2 == 0) {
        a = fabs(a);
        b = fabs(b);
        c = fabs(c);
    }
    double lo = min(a, b, c);
    double hi = max(a, b, c);
    Vector vec;
    vec.length = 0;
    double sign = 1;
    if (lo < 0)
        sign = -1;
    int value = sign * ceil(pow(fabs(lo), 1.0 / n));
    if (!cmp(value, lo))
        ++value;
    while (true) {
        if (pow(value, n) >= hi)
            break;
        vec.values[vec.length++] = value;
        if (n % 2 == 0 && !cmp(value, 0))
            vec.values[vec.length++] = -1 * value;
        value++;
    }
    return vec;
}

DiophantineSolution solveDiophantineEquation(DiophantineEquation e)
{
    DiophantineSolution dios;
    dios.hasSolutions = false;
    dios.ax = dios.ay = dios.bx = dios.by = 0;
    return dios;
}


Complex sum(Complex c1, Complex c2)
{
    Complex s;
    s.a = c1.a + c2.a;
    s.b = c1.b + c2.b;
    return s;
}

Complex product(Complex c1, Complex c2)
{
    Complex p;
    p.a = c1.a * c2.a - c1.b * c2.b;
    p.b = c1.a * c2.b + c1.b * c2.a;
    return p;
}
