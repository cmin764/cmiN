#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    char mystr[256], chr, *ptr;
    int count = 0;
    cout << "Fraza: ";
    cin.getline(mystr, 256);
    cout << "Caracterul cautat: ";
    cin >> chr;
    ptr = strchr(mystr, chr);
    while (ptr) {
        ptr = strchr(ptr + 1, chr);
        count++;
    }
    cout << "Caracterul '" << chr << "' apare de " << count << " ori.\n";
    return 0;
}
