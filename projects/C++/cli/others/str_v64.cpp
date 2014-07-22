// bac 064
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    char voc[] = "aAeEiIoOuU", str[256], * pChar = str;
    bool flag = true, vocChar;
    int count = 0;
    cout << "Text: ";
    cin.getline(str, 256);
    while (*pChar) {
        if (*pChar == ' ') {
            if (!flag) {
                if (vocChar && strchr(voc, *(pChar - 1))) {
                    count++;
                }
                flag = true;
            }
        } else {
            if (flag) {
                vocChar = strchr(voc, *pChar);
                flag = false;
            }
        }
        pChar++;
    }
    if (!flag) {
        if (vocChar && strchr(voc, *(pChar - 1))) {
            count++;
        }
        flag = true;
    }
    cout << count << "\n";
    return 0;
}
