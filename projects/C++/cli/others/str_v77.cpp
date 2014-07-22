// bac 077
#include <iostream>
using namespace std;

int main()
{
    char str[64], * pChar = str, dif = 'a' - 'A';
    bool flag = true;
    cout << "Text: ";
    cin.getline(str, 64);
    while (*pChar) {
        if (*pChar == ' ') {
            if (!flag) {
                flag = true;
            }
        } else {
            if (flag) {
                *pChar -= dif;
                flag = false;
            }
        }
        pChar++;
    }
    cout << str << "\n";
    return 0;
}
