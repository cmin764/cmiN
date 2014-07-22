// d.c: I1


#include <stdio.h>
#include <math.h>


#define N 50000


int div[N];


int perfect(int nr)
{
    int k = 1, sq = (int)sqrt(nr);
    for (int i = 2; i <= sq; ++i)
        if (!(nr % i)) {
            div[k++] = i;
            div[k++] = nr / i;
        }
    int sum = 0;
    for (int i = 0; i < k; ++i)
        sum += div[i];
    if (sum == nr) return 1;
    return 0;
}


int main()
{
    // O(NsqrtN)
    printf("Numarul n: ");
    int nr;
    scanf("%d", &nr);
    div[0] = 1;
    for (int i = 6; i < nr; ++i)
        if (perfect(i))
            printf("%d\n", i);
    return 0;
}

