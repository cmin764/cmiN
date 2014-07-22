// bac 060
#include <iostream>
using namespace std;

int vChar[128];

int main()
{
    char str[64], * pChar = str;
    int max = 1, i;
    bool flag = true;
    cout << "Text: ";
    cin.getline(str, 64);
    while (*pChar) {
        if (*pChar > 96 && *pChar < 123) {
            vChar[*pChar]++;
            if (vChar[*pChar] > max) {
                max = vChar[*pChar];
            }
        }
        pChar++;
    }
    for (i = 0; i < 128; i++) {
        if (vChar[i] == max) {
            cout << char(i) << "\n";
            flag = false;
            break;
        }
    }
    if (flag) {
        cout << "nu\n";
    }
    return 0;
}
