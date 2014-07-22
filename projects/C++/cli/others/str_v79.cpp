// bac 079
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    char str[128], * pChar = str;
    char voc[] = {'a', 'A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U'};
    int len, i;
    cout << "Text: ";
    cin.getline(str, 128);
    len = strlen(str);
    while (*pChar) {
        if (strchr(voc, *pChar)) {
            for (i = len; i > pChar - str; i--) {
                str[i + 1] = str[i];
            }
            *(pChar + 1) = '*';
            len++;
        }
        pChar++;
    }
    cout << str << "\n";
    return 0;
}
