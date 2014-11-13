#include "exercises.h"


unsigned int computeDigitSum(unsigned int number)
{
    unsigned int total = 0;
    while (number) {
        total += number % 10;
        number /= 10;
    }
    return total;
}


bool isLeap(unsigned int year)
{
    if (year % 4 != 0)
        return false;
    if (year % 100 != 0)
        return true;
    if (year % 400 != 0)
        return false;
    return true;
}


bool isPalindrome(int number)
{
    int inv = 0;
    int nr = number;
    while (nr) {
        inv = inv * 10 + nr % 10;
        nr /= 10;
    }
    return inv == number;
}


unsigned int computeNumberOfDays(unsigned int year, unsigned int month)
{
    int days[12];
    int nr = 1;
    for (int i = 0; i < 12; ++i) {
        days[i] = nr;
        if (i != 6)
            nr = !nr;
    }
    days[1] = 2;
    int ind = days[month - 1];
    if (ind == 1)
        return 31;
    if (ind == 0)
        return 30;
    if (isLeap(year))
        return 29;
    return 28;
}


unsigned int computeControlDigit(unsigned int number)
{
    while (number / 10) {
        int total = 0;
        while (number) {
            total += number % 10;
            number /= 10;
        }
        number = total;
    }
    return number;
}


bool isPerfect(unsigned int number)
{
    unsigned int total = 0;
    for (unsigned int i = 1; i < number; ++i) {
        if (number % i == 0)
            total += i;
        if (total > number)
            break;
    }
    return total == number;
}

vector getPerfects(unsigned int upperLimit)
{
    vector vec;
    vec.length = 0;
    for (unsigned int i = 1; i < upperLimit; ++i)
        if (isPerfect(i))
            vec.values[vec.length++] = (int)i;
    return vec;
}


bool isPrime(int number)
{
    if (number < 2)
        return false;
    if (number == 2)
        return true;
    if (!(number % 2))
        return false;
    for (int i = 3; i <= sqrt(number); i += 2)
        if (!(number % i))
            return false;
    return true;
}


bool areTwinPrimes(unsigned int number1, unsigned int number2)
{
    if (isPrime(number1) && isPrime(number2))
        return true;
    return false;
}

matrix getTwinPrimes(unsigned int count)
{
    matrix mat;
    mat.lines = 0;
    mat.columns = 2;
    unsigned int first = 3, second = 5;
    while (mat.lines < count) {
        if (areTwinPrimes(first, second)) {
            mat.values[mat.lines][0] = first;
            mat.values[mat.lines][1] = second;
            ++mat.lines;
        }
        first += 2;
        second += 2;
    }
    return mat;
}


unsigned int getMaxDifference(vector v)
{
    int minNr = 0x7FFFFFFF;
    int maxNr = 0x80000000;
    for (int i = 0; i < v.length; ++i) {
        int nr = v.values[i];
        if (nr < minNr)
            minNr = nr;
        if (nr > maxNr)
            maxNr = nr;
    }
    long long ret = (long long)maxNr - (long long)minNr;
    return (unsigned int)ret;
}


sequence getMaxSequence(vector v)
{
    sequence seq;
    seq.startPosition = seq.length = 0;
    if (v.length == 0)
        return seq;
    int pos = 0, len = 1;
    int last = v.values[0];
    seq.startPosition = pos;
    seq.length = len;
    for (int i = 1; i < v.length; ++i) {
        int crt = v.values[i];
        if (crt == last) {
            ++len;
        } else {
            if (len > seq.length) {
                seq.length = len;
                seq.startPosition = pos;
            }
            pos = i;
            len = 1;
            last = crt;
        }
    }
    return seq;
}


sequence getMaxSumSequence(vector v)
{
    sequence seq;
    int total_max = 0;
    for (int pos = 0; pos < v.length; ++pos) {
        for (int len = 1; len <= v.length - pos; ++len) {
            int total = 0;
            for (int i = pos; i < pos + len; ++i) {
                total += v.values[i];
            }
            if (total >= total_max) {
                total_max = total;
                seq.startPosition = pos;
                seq.length = len;
            }
        }
    }
    return seq;
}


vector orderElements(vector v)
{
    vector ret;
    ret.length = 0;
    for (int r = 0; r < 2; ++r) {
        for (int i = 0; i < v.length; ++i) {
            int nr = v.values[i];
            if (nr % 2 == r)
                ret.values[ret.length++] = nr;
        }
    }
    return ret;
}


bool containsMajorElement(vector v)
{
    for (int i = 0; i < v.length; ++i) {
        int nr = v.values[i];
        int cnt = 0;
        for (int j = 0; j < v.length; ++j)
            if (v.values[j] == nr)
                cnt += 1;
        if (cnt > v.length / 2)
            return true;
    }
    return false;
}

/* Exercitiul 14
   Se considera o matrice patratica cu n elemente.
   Sa se interschimbe liniile si coloanele acesteia astfel incat, in matricea finala, elementele de pe diagonala principala sa fie in ordine descrescatoare.
   Sa se afiseze matricea initiala si matricea dupa fiecare operatie.
*/

matrix sortDiagonalElements(matrix m)
{
}


vector getSpiralVector(matrix m)
{
    vector vec;
    vec.length = 0;
    int n = m.lines;
    for (int d = 0; d < n / 2; ++d) {
        int i;
        for (i = d; i < n - d; ++i) {
            vec.values[vec.length++] = m.values[d][i];
        }
        for (i = d + 1; i < n - d; ++i) {
            vec.values[vec.length++] = m.values[i][n - d - 1];
        }
        for (i = n - d - 2; i >= d; --i) {
            vec.values[vec.length++] = m.values[n - 1 - d][i];
        }
        for (i = n - 2 - d; i > d; --i) {
            vec.values[vec.length++] = m.values[i][d];
        }
    }
    return vec;
}

/* Exercitiul 16
   Sa se defineasca un tip pentru reprezentarea datelor calendaristice.
   Sa se scrie o functie care primeste la intrare o data calendaristica si returneaza succesorul acesteia.
   Exemplu: succesorul datei "31.10.2014" este "1.11.2014".
*/

date getNextDate(date currentDate)
{
}

/* Exercitiul 17
   Sa se determine ecuatia unei drepte care trece prin doua puncte in plan.
   Exemplu: pentru punctele (2, 1) si (5, 7), ecuatia dreptei este 2x – y – 3 = 0.
   Precizia pentru a, b si c va fi de 2 zecimale.
   Ecuatia va fi redusa.
*/

equation computeEquation(point point1, point point2)
{
}
