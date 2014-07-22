// bac 066
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
        for (j = 0; j < i; j++) {
            cout << str[j];
        }
        cout << "\n";
    }
    return 0;
}
