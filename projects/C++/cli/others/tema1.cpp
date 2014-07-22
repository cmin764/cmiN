#include <iostream>
using namespace std;

int mirror(int nr)
{
    int mnr = 0, c;
    while (nr > 0) {
        c = nr % 10;
        nr /= 10;
        mnr = mnr * 10 + c;
    }
    return mnr;
}

char * prst(int nr)
{
    for (int i = 2; i < nr / 2; i++) {
        if (nr % i == 0) {
            return "nu este";
        }
    }
    return "este";
}

int main()
{
    int nr;
    cout << "Un numar: ";
    cin >> nr;
    cout << "Numarul introdus " << prst(nr) << " prim,";
    cout << " iar oglinditul sau este " << mirror(nr) << ".\n";
    system("pause >nul");
    return 0;
}
