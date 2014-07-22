// b.c: I1


#include <stdio.h>


int leap(int year)
{
    // from wiki
    if (!(year % 400)) return 1;
    if (!(year % 100)) return 0;
    if (!(year % 4)) return 1;
    return 0;
}


int process(int month, int year)
{
    // special case
    if (month == 2) {
        if (leap(year)) return 29;
        return 28;
    }
    // 1-7 -> 31, 30, 31, ...
    if (month <= 7) {
        if (month % 2) return 31;
        return 30;
    }
    // 8-12 -> 31, 30, 31, ...
    if (month % 2) return 30;
    return 31;
}


int main()
{
    printf("MM-YYYY: ");
    int month, year;
    scanf("%d-%d", &month, &year);
    printf("Numarul de zile: %d\n",
           process(month, year));
    return 0;
}
