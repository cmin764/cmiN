#include <stdio.h>
#include <stdlib.h>

short a, b, min = 25, gm, nr, * vec;

void process(short ob, short cmin)
{
    short flag = 1, tmp;
    if (ob == nr) {
        if (cmin < min) {
            min = cmin;
        }
    } else {
        if (vec[ob] + a <= gm) {
            flag = 0;
            a += vec[ob];
            process(ob + 1, cmin);
            a -= vec[ob];
        }
        if (vec[ob] + b <= gm) {
            flag = 0;
            b += vec[ob];
            process(ob + 1, cmin);
            b -= vec[ob];
        }
        if (flag) {
            if (a < b) {
                tmp = a;
                a = b;
                b = tmp;
            }
            tmp = a;
            a = 0;
            process(ob, cmin + 1);
            a = tmp;
        }
    }
}

int main()
{
    short i;
    freopen("banda.in", "rt", stdin);
    freopen("banda.out", "wt", stdout);
    scanf("%hd %hd", &nr, &gm);
    vec = (short*)malloc(nr * sizeof(short));
    for (i = 0; i < nr; ++i) {
        scanf("%hd", vec + i);
    }
    process(0, 2);
    printf("%hd", min);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
