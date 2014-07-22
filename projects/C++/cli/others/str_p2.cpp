#include <iostream>
using namespace std;

int main()
{
    char str[128], *pch;
    int nr = 0;
    bool flag;
    cout << "Fraza: ";
    cin.getline(str, 128);
    pch = str;
    flag = true;
    while (*pch) {
        if (*pch == ' ') {
            flag = true;
        } else {
            if (flag) {
                nr++;
                flag = false;
            }
        }
        pch++;
    }
    cout << nr << "\n";
    pch = str;
    flag = false;
    while (*pch) {
        if (*pch == ' ') {
            if (flag) {
                cout << "\n";
                flag = false;
            }
        } else {
            cout << *pch;
            flag = true;
        }
        pch++;
    }
    cout << "\n";
    return 0;
}
