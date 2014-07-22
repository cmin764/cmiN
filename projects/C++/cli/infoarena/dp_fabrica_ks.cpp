#include <stdio.h>

const unsigned int n = 128;
typedef unsigned int ui_t;
struct product {
    ui_t cost, value;
} prods[n];
ui_t nr, sum, sums[n], pick[n];

void read()
{
    scanf("%u %u", &nr, &sum);
    for (ui_t i = 1; i <= nr; i++) {
        scanf("%u %u", &prods[i].cost, &prods[i].value);
    }
}

void compute()
{
    for (ui_t i = 1; i <= nr; i++) {
        for (ui_t j = 1; j <= sum; j++) {
            if (prods[i].cost <= j && sums[j] < sums[j - prods[i].cost] + prods[i].value) {
                sums[j] = sums[j - prods[i].cost] + prods[i].value;
                pick[j] = i;
            }
        }
    }
}

void write()
{
    while (pick[sum]) {
        printf("%u ", pick[sum]);
        sum -= prods[pick[sum]].cost;
    }
}

int main()
{
    freopen("dp_fabrica_ks.in", "r", stdin);
    freopen("dp_fabrica_ks.out", "w", stdout);
    read();
    compute();
    write();
    fclose(stdin);
    fclose(stdout);
    return 0;
}
