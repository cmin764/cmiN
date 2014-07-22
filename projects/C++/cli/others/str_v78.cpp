#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    char str[128], word[16], * pos;
    int len, i;
    cout << "Text: ";
    cin.getline(str, 128);
    cout << "Cuvant: ";
    cin >> word;
    pos = strstr(str, word);
    len = strlen(str);
    while (pos) {
        while (*pos != ' ' && *pos != 0) {
            pos++;
        }
        for (i = len; i >= pos - str; i--) {
            str[i + 1] = str[i];
        }
        str[i + 1] = '?';
        pos = strstr(pos + 1, word);
        len++;
    }
    cout << str << "\n";
    return 0;
}
