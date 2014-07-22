// bac 062
#include <iostream>
using namespace std;

char vChar[256];

int main()
{
    char str[256], * pChar = str;
    cout << "Text: ";
    cin.getline(str, 256);
    while (*pChar) {
        if (*pChar > 96 && *pChar < 123) {
            if (!vChar[*pChar]) {
                cout << *pChar << " ";
                vChar[*pChar] = 1;
            }
        }
        pChar++;
    }
    cout << "\n";
    return 0;
}
