// bac 076
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    char str[32];
    int i = 0, j;
    cout << "Text: ";
    cin >> str;
    j = strlen(str);
    while (i < j) {
        str[j] = 0;
        cout << str + i << "\n";
        i++;
        j--;
    }
    return 0;
}
