// h: succesorul unei date calendaristice


#include <stdio.h>
#include <stdlib.h>


#define DBG 0


typedef struct {
    /**
     * Structura pentru reprezentare datei
     * atat in format printabil cat si zecimal.
     */
    char str[16];
    int dd, mm, yy;
} Date;


void str2date(Date* date)
{
    // aflam ziua, luna si data din sir
    int d, m, y;
    d = m = y = 0;
    int at = 0;
    for (char* p = date->str; *p; ++p)
        if (*p == '.')
            ++at;
        else if (at == 0)
            d = d * 10 + *p - '0';
        else if (at == 1)
            m = m * 10 + *p - '0';
        else
            y = y * 10 + *p - '0';
    date->dd = d;
    date->mm = m;
    date->yy = y;
}


void write_unit(char* str, int* at, int unit)
{
    char tmp[8];
    sprintf(tmp, "%d", unit);
    for (char* p = tmp; *p; ++p)
        str[(*at)++] = *p;
}


void date2str(Date* date)
{
    int d, m, y;
    d = date->dd;
    m = date->mm;
    y = date->yy;
    int at = 0;
    write_unit(date->str, &at, d);
    date->str[at++] = '.';
    write_unit(date->str, &at, m);
    date->str[at++] = '.';
    write_unit(date->str, &at, y);
    date->str[at] = 0; // NULL
}


int leap(int year)
{
    // from wiki
    if (!(year % 400)) return 1;
    if (!(year % 100)) return 0;
    if (!(year % 4)) return 1;
    return 0;
}


void succesor(Date* date)
{
    int d, m, y;
    d = date->dd;
    m = date->mm;
    y = date->yy;
    int incm = 0, incy = 0;
    if (d < 28)
        ++d;
    else {
        if (m == 2)
            if (leap(y) && d == 28)
                ++d;
            else {
                d = 1;
                incm = 1;
            }
        else if (d == 31) {
            d = 1;
            incm = 1;
        } else if (m >= 1 && m <= 7)
            if (!(m % 2) && d == 30) {
                d = 1;
                incm = 1;
            } else
                ++d;
        else
            if (m % 2 && d == 30) {
                d = 1;
                incm = 1;
            } else
                ++d;
    }
    if (incm) {
        if (m == 12) {
            m = 1;
            incy = 1;
        } else
            ++m;
    }
    if (incy)
        ++y;
    date->dd = d;
    date->mm = m;
    date->yy = y;
    date2str(date);
}


int main()
{
    printf("Data (DD.MM.YYYY): ");
    Date date;
    scanf("%s", date.str);
    str2date(&date);
    #if DBG
    fprintf(stderr, "Debug: %d.%d.%d\n",
            date.dd, date.mm, date.yy);
    #endif
    succesor(&date);
    #if DBG
    fprintf(stderr, "Debug: %d.%d.%d\n",
            date.dd, date.mm, date.yy);
    #endif
    printf("Succesorul acesteia %s\n", date.str);
    return 0;
}
