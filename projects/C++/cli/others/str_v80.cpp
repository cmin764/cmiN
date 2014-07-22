// bac 080
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    char str[32], temp;
    int i, j, len;
    cout << "Text: ";
    cin >> str;
    len = strlen(str);
    i = 0;
    j = (len / 2) + (len % 2);
    while (str[j]) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j++;
    }
    cout << str << "\n";
    return 0;
}
