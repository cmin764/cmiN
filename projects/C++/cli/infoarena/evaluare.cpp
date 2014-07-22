#include <cstdio>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;


string exp;
int pos;


int nr()
{
    int res = 0;
    while (isdigit(exp[pos])) {
        res = res * 10 + exp[pos] - '0';
        ++pos;
    }
    return res;
}


int eval(int a, int b, char sign)
{
    switch (sign) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
}


int calc(bool lev)
{
    int ret = 0;
    char sign = '+';
    while (pos < exp.size()) {
        if (isdigit(exp[pos])) {
            ret = eval(ret, nr(), sign);
        } else if (exp[pos] == '*') {
            ++pos;
            sign = '*';
        } else if (exp[pos] == '/') {
            ++pos;
            sign = '/';
        } else if (exp[pos] == '+') {
            if (lev) return ret;
            ++pos;
            sign = '+';
            ret = eval(ret, calc(true), sign);
        } else if (exp[pos] == '-') {
            if (lev) return ret;
            ++pos;
            sign = '-';
            ret = eval(ret, calc(true), sign);
        } else if (exp[pos] == '(') {
            ++pos;
            ret = eval(ret, calc(false), sign);
        } else if (exp[pos] == ')') {
            if (!lev) ++pos;
            return ret;
        }
    }
    return ret;
}


int main()
{
    freopen("evaluare.in", "r", stdin);
    freopen("evaluare.out", "w", stdout);
    cin >> exp;
    cout << calc(false);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
