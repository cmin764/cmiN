#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

string mystr;
short pos;

string process()
{
    if (mystr[pos] == '(') {
        string a, b, c;
        ++pos;
        a = process();
        b = mystr.substr(pos++, 1);
        c = process();
        ++pos;
        return a + c + b;
    } else {
        return mystr.substr(pos++, 1);
    }
}

int main()
{
    //freopen("onp.in", "rt", stdin);
    short nr;
    cin >> nr;
    cin.ignore();
    for (; nr; --nr) {
        getline(cin, mystr);
        pos = 0;
        cout << process() << endl;
    }
    return 0;
}
