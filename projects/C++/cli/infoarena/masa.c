#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define iname "masa.in"
#define oname "masa.out"
#define N 101

const short H = 1, C = 12, O = 16;
short len;
char sir[N], * pnt = sir;
short serial();
short paralel();

short getm(char chr)
{
    if (chr == 'H') {
        return H;
    } else if (chr == 'C') {
        return C;
    } else if (chr == 'O') {
        return O;
    } else {
        fprintf(stderr, "Invalid input.");
        exit(EXIT_FAILURE);
    }
}

short paralel()
{
    short sum;
    ++pnt;
    sum = serial();
    ++pnt;
    if (*pnt >= '0' && *pnt <= '9') {
        sum *= *pnt - '0';
    }
    return sum;
}

short serial()
{
    short sum = 0;
    char tmp = *pnt;
    while (*pnt && *pnt != ')') {
        if (*pnt == '(') {
            sum += paralel();
        } else {
            if (*pnt >= '0' && *pnt <= '9') {
                sum += getm(tmp) * (*pnt - '1');
            } else {
                sum += getm(*pnt);
                tmp = *pnt;
            }
        }
        ++pnt;
    }
    return sum;
}

int main()
{
    freopen(iname, "rt", stdin);
    freopen(oname, "wt", stdout);
    gets(sir);
    len = strlen(sir);
    printf("%hd", serial());
    fclose(stdin);
    fclose(stdout);
    return 0;
}
