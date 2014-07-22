// bac 067
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    char str[64];
    int i, j, len;
    cout << "Text: ";
    cin >> str;
    len = strlen(str);
    for (i = 1; i <= len; i++) {
        for (j = i - 1; j >= 0; j--) {
            cout << str[len - 1 - j];
        }
        cout << "\n";
    }
}
