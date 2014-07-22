#include <cstdio>
#include <cmath>

unsigned int numbers[3500], len;

inline bool prime(unsigned int x)
{
    unsigned int i, last = sqrt(x);
    for (i = 2; i <= last; i++) {
        if (!(x % i)) {
            return 0;
        }
    }
    return 1;
}

void generate()
{
    for (unsigned int i = 2; i < 32000; i++) {
        if (prime(i)) {
            numbers[len++] = i;
        }
    }
}

inline bool process(unsigned long x)
{
    unsigned int i, last = sqrt(x);
    for (i = 0; i < len && numbers[i] <= last; i++) {
        if (!(x % numbers[i])) {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int tests;
    unsigned long begin, end;
    generate();
    scanf("%d", &tests);
    while (tests-- > 0) {
        scanf("%u %u", &begin, &end);
        if (begin == 1) {
            begin++;
        }
        while (begin <= end) {
            if (process(begin)) {
                printf("%u\n", begin);
            }
            begin++;
        }
        printf("\n");
    }
    return 0;
}
