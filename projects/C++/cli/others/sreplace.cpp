#include <iostream>
#include <string>
using namespace std;


void replace(const string& from, const string& to, string& mystr)
{
    int pos = 0;
    while ((pos = mystr.find(from, pos)) != string::npos) {
        mystr.replace(pos, from.size(), to);
        pos += to.size();
    }
}


int main(int argc, char* argv[])
{
    string from, to, mystr;
    bool fromOn = false, toOn = false, mystrOn = false;
    int last = 0;
    for (int i = 1; i < argc; ++i) {
        string tmp(argv[i]);
        if (!tmp.compare("-f")) {
            fromOn = true;
            last = 1;
        } else if (!tmp.compare("-t")) {
            toOn = true;
            last = 2;
        } else if (!tmp.compare("-s")) {
            mystrOn = true;
            last = 3;
        } else {
            if (last == 1) from.append(tmp + " ");
            else if (last == 2) to.append(tmp + " ");
            else if (last == 3) mystr.append(tmp + " ");
        }
    }
    if (mystrOn) {
        mystr.erase(--mystr.end());
        if (toOn) to.erase(--to.end());
        if (fromOn) {
            from.erase(--from.end());
            replace(from, to, mystr);
        }
        cout << mystr << endl;
    } else {
        cerr << "Usage: " << argv[0] << " [...] -s <string>\n";
        cerr << "Example: " << argv[0] << " -f mere -t portocale -s ana are mere\n\n";
        cerr << "Options:\n";
        cerr << "    -s <string>    input text\n";
        cerr << "    -f <string>    chunk to modify\n";
        cerr << "    -t <string>    with what to replace" << endl;
    }
    return 0;
}
