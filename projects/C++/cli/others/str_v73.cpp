// bac 073
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    char str[256], * pChar = str, voc[] = "aeiou", wCount = 0, vCount = 0;
    bool flag = true;
    cout << "Text: ";
    cin.getline(str, 256);
    while (*pChar) {
        if (*pChar == ' ') {
            if (!flag) {
                flag = true;
            }
        } else {
            if (flag) {
                wCount++;
                if (strchr(voc, *pChar)) {
                    vCount++;
                }
                flag = false;
            }
        }
        pChar++;
    }
    cout << int(wCount) << " " << int(vCount) << "\n";
    return 0;
}
