#include <stdio.h>

const unsigned int nr = 15;

int main()
{
    unsigned long int modes[128];
    modes[1] = 1;
    modes[2] = 2;
    for (int i = 3; i <= nr; i++) {
        modes[i] = modes[i - 1] + modes[i - 2];
    }
    printf("%d", modes[nr]);
    return 0;
}
