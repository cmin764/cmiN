#include <iostream>
using namespace std;

unsigned long fib(unsigned int n, unsigned long a, unsigned long b)
{
    if (n > 1) {
        return fib(n - 1, b, a + b);
    }
    return a;
}

void fibonacci()
{
    unsigned int n;
    cout << "Numarul de pe pozitia n din sirul lui Fibonacci.\n";
    cout << "n: ";
    cin >> n;
    cout << fib(n, 0, 1) << "\n";
}

unsigned long fac(unsigned int n)
{
    if (n > 1) {
        return n * fac(n - 1);
    }
    return 1;
}

void factorial()
{
    unsigned int n;
    cout << "Numarul n factorial.\n";
    cout << "n: ";
    cin >> n;
    cout << fac(n) << "\n";
}

void aranjamente()
{
    unsigned int n, k;
    cout << "Aranjamente de n luate cate k.\n";
    cout << "n: ";
    cin >> n;
    cout << "k: ";
    cin >> k;
    cout << fac(n) / fac(n - k) << "\n";
}

unsigned long com(unsigned int n, unsigned int k)
{
    if (n == k || k == 0) {
        return 1;
    }
    return com(n - 1, k) + com(n - 1, k - 1);
}

void combinari()
{
    unsigned int n, k;
    cout << "Combinari de n luate cate k.\n";
    cout << "n: ";
    cin >> n;
    cout << "k: ";
    cin >> k;
    cout << com(n, k) << "\n";
}

double pot(int b, int e)
{
    if (e > 0) {
        return b * pot(b, e - 1);
    }
    return 1;
}

void putere()
{
    int b, e;
    double x;
    cout << "Baza b la puterea exponentului e.\n";
    cout << "b: ";
    cin >> b;
    cout << "e: ";
    cin >> e;
    if (e > 0) {
        e = e > 0 ? e : -1 * e;
        x = pot(b, e);
    } else {
        e = e > 0 ? e : -1 * e;
        x = 1 / pot(b, e);
    }
    cout << x << "\n";
}

void start()
{
    int op;
    cout << "1 - Fibonacci\n"
         << "2 - Factorial\n"
         << "3 - Aranjamente\n"
         << "4 - Combinari\n"
         << "5 - Putere\n"
         << "0 - Iesire\n";
    cout << "Optiune: ";
    cin >> op;
    cout << "\n";
    switch (op) {
        case 1:
            fibonacci();
            break;
        case 2:
            factorial();
            break;
        case 3:
            aranjamente();
            break;
        case 4:
            combinari();
            break;
        case 5:
            putere();
            break;
        case 0:
            exit(0);
        default:
            cout << "Optiune incorecta.\n";
    }
}

int main()
{
    while (true) {
        system("cls");
        start();
        system("pause >nul");
    }
    return 0;
}
