#include <iostream>
using namespace std;

const int n = 32;
struct vector {
    int vec[n];
    int len;
};

void setv(vector& v)
{
    cout << "Lungime: ";
    cin >> v.len;
    cout << "Dati elemente...\n";
    for (int i = 0; i < v.len; i++) {
        cin >> v.vec[i];
    }
    cin.ignore();
}

void printv(const vector& v)
{
    for (int i = 0; i < v.len; i++) {
        cout << v.vec[i] << " ";
    }
    cout << "\n";
}

bool search(const vector& v, const int x)
{
    for (int i = 0; i < v.len; i++) {
        if (v.vec[i] == x) {
            return true;
        }
    }
    return false;
}

vector reun(const vector& v1, const vector& v2)
{
    vector v3 = v1;
    for (int i = 0; i < v2.len; i++) {
        if (!search(v1, v2.vec[i])) {
            v3.vec[v3.len++] = v2.vec[i];
        }
    }
    return v3;
}

vector inte(const vector& v1, const vector& v2)
{
    vector v3;
    v3.len = 0;
    for (int i = 0; i < v1.len; i++) {
        if (search(v2, v1.vec[i])) {
            v3.vec[v3.len++] = v1.vec[i];
        }
    }
    return v3;
}

int main()
{
    vector v1, v2, v3;
    cout << "Prima multime.\n";
    setv(v1);
    cout << "A doua multime.\n";
    setv(v2);
    cout << "Reuniunea.\n";
    v3 = reun(v1, v2);
    printv(v3);
    cout << "Intersectia.\n";
    v3 = inte(v1, v2);
    printv(v3);
    cin.get();
    return 0;
}
