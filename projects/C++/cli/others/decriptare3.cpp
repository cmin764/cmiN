#include <iostream>
#include <string>
#include <cstring>
using namespace std;

string mystr, vowels("AEIOU");

void normalize()
{
    string::iterator it;
    for (it = mystr.begin(); it != mystr.end(); ++it) {
        *it = toupper(*it);
    }
}

bool isvow(char chr)
{
    if (vowels.find(chr) == string::npos) {
        return 0;
    } else {
        return 1;
    }
}

char rotate(char chr, short len)
{
    if (len > 0) {
        do {
            if (chr == 'Z') {
                chr = 'A';
            } else {
                ++chr;
            }
        } while (--len);
    } else if (len < 0) {
        do {
            if (chr == 'A') {
                chr = 'Z';
            } else {
                --chr;
            }
        } while (++len);
    }
    return chr;
}

void dec()
{
    bool tmp;
    short it, torot = 0;
    for (it = 0; it < mystr.length(); ++it) {
        mystr[it] = rotate(mystr[it], -4);
        tmp = isvow(mystr[it]);
        mystr[it] = rotate(mystr[it], torot);
        if (tmp) {
            mystr.erase(it + 1, 1);
            --torot;
        }
    }
}

void enc()
{
    bool tmp;
    short it, tt;
    for (it = 0; it < mystr.length(); ++it) {
        tmp = isvow(mystr[it]);
        mystr[it] = rotate(mystr[it], 4);
        if (tmp) {
            mystr.insert(it + 1, 1, rotate(mystr[it], 10));
            for (tt = ++it + 1; tt < mystr.length(); ++tt) {
                mystr[tt] = rotate(mystr[tt], 1);
            }
        }
    }
}

int main()
{
    short ans;
    cout << "1. Encode\n2. Decode\n3. Exit\n";
    cin >> ans;
    if (ans == 1 || ans == 2) {
        cout << "Input: ";
        cin >> mystr;
        normalize();
        if (ans == 1) {
            enc();
        } else {
            dec();
        }
        cout << "Output: " << mystr << endl;
        main();
    }
    return 0;
}
