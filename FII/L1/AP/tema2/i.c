// i: ecuatia dreptei dandu-se doua puncte


#include <stdio.h>
#include <stdlib.h>


#define DBG 0 // debug
#define DIM 64


typedef struct {
    /// Coordonatele unui punct.
    int x, y;
} Pct;


int cmmdc(int a, int b)
{
    // euclid cu impartiri
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}


void sign(char* buffer)
{
    if (buffer[0] != '-')
        return;
    char tmp[DIM];
    sprintf(tmp, "%s", buffer + 1);
    #if DBG
    fprintf(stderr, "Trunc: %s\n", tmp);
    #endif
    sprintf(buffer, "%s", tmp);
    for (; *buffer; ++buffer)
        if (*buffer == '-')
            *buffer = '+';
        else if (*buffer == '+')
            *buffer = '-';
}


void process(Pct a, Pct b, char* buffer)
{
    // construim "fractia"
    int nr1 = -a.x; // cfx*X+nr1   cfy*Y+nr2
    int nr2 = -a.y; // --------- = ---------
    int cfx = 1;    //    nm1         nm2
    int cfy = 1;
    int nm1 = b.x - a.x;
    int nm2 = b.y - a.y;
    // punctele nu-s distincte
    if (!(nm1 || nm2)) {
        sprintf(buffer, "N/A");
        return;
    }
    // produsul mezilor == produsul extremelor
    cfx *= nm2;
    cfy *= -nm1;
    int rem = nm2 * nr1 - nm1 * nr2;
    if (!cfx) { // y1 = y2 -> y = y1
        int at = 0;
        buffer[at++] = 'y';
        buffer[at++] = ' ';
        // trecem in stanga sau in dreapta cu semn schimbat
        if (a.y > 0) {
            buffer[at++] = '-';
            buffer[at++] = ' ';
            sprintf(buffer + at, "%d", abs(a.y));
            while (buffer[at]) ++at;
        } else if (a.y < 0) {
            buffer[at++] = '+';
            buffer[at++] = ' ';
            sprintf(buffer + at, "%d", abs(a.y));
            while (buffer[at]) ++at;
        }
        sprintf(buffer + at, "%s", " = 0");
        return;
    } else if (!cfy) { // x1 = x2
        int at = 0;
        buffer[at++] = 'x';
        buffer[at++] = ' ';
        // trecem in stanga sau in dreapta cu semn schimbat
        if (a.x > 0) {
            buffer[at++] = '-';
            buffer[at++] = ' ';
            sprintf(buffer + at, "%d", a.x);
            while (buffer[at]) ++at;
        } else if (a.x < 0) {
            buffer[at++] = '+';
            buffer[at++] = ' ';
            sprintf(buffer + at, "%d", a.x);
            while (buffer[at]) ++at;
        }
        sprintf(buffer + at, "%s", " = 0");
        return;
    }
    // cfx*X + cfy*Y + rem = 0
    int cm = cmmdc(cmmdc(abs(cfx), abs(cfy)),
                   abs(rem));
    #if DBG
    fprintf(stderr, "cm, cfx, cfy, rem: %d %d %d %d\n",
            cm, cfx, cfy, rem);
    #endif
    cfx /= cm;
    cfy /= cm;
    rem /= cm;
    // stabilirea semnelor
    char sx, sy, sr;
    if (cfx < 0)
        sx = '-';
    else
        sx = '+';
    if (cfy < 0)
        sy = '-';
    else
        sy = '+';
    if (rem < 0)
        sr = '-';
    else
        sr = '+';
    // construirea ecuatiei
    int at = 0, tmp;
    buffer[at] = 0;
    // X
    if (sx == '-') {
        buffer[at++] = sx;
        buffer[at] = 0;
    }
    tmp = abs(cfx);
    if (tmp != 1)
        sprintf(buffer + at, "%d", tmp);
    while (buffer[at]) ++at;
    buffer[at++] = 'x';
    buffer[at++] = ' ';
    // Y
    buffer[at++] = sy;
    buffer[at++] = ' ';
    buffer[at] = 0;
    tmp = abs(cfy);
    if (tmp != 1)
        sprintf(buffer + at, "%d", tmp);
    while (buffer[at]) ++at;
    buffer[at++] = 'y';
    buffer[at++] = ' ';
    buffer[at] = 0;
    // R
    tmp = abs(rem);
    if (tmp) {
        buffer[at++] = sr;
        buffer[at++] = ' ';
        sprintf(buffer + at, "%d", tmp);
    }
    while(buffer[at]) ++at;
    // = 0
    buffer[at++] = ' ';
    buffer[at++] = '=';
    buffer[at++] = ' ';
    buffer[at++] = '0';
    buffer[at] = 0;
    sign(buffer);
}


int main()
{
    Pct a, b;
    printf("A (x, y): ");
    scanf("%d %d", &a.x, &a.y);
    printf("B (x, y): ");
    scanf("%d %d", &b.x, &b.y);
    // aici stocam ecuatia
    char buffer[DIM];
    process(a, b, buffer);
    printf("Ecuatia %s\n", buffer);
    return 0;
}
