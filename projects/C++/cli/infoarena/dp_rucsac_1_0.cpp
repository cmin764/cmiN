#include <stdio.h>

typedef unsigned int ui_t;
const ui_t maxlen = 128;
struct object {
    ui_t weight, value;
} objects[maxlen];
ui_t objnr, sacwg, cost[maxlen][maxlen];

ui_t maxcost(ui_t a, ui_t b)
{
    return a > b ? a : b;
}

void process()
{
    for (ui_t i = 1; i <= objnr; i++) {
        for (ui_t j = 1; j <= sacwg; j++) {
            if (objects[i].weight > j) {
                cost[i][j] = cost[i - 1][j];
            } else {
                cost[i][j] = maxcost(cost[i - 1][j], cost[i - 1][j - objects[i].weight] + objects[i].value);
            }
        }
    }
}

int main()
{
    freopen("dp_rucsac_1_0.in", "r", stdin);
    freopen("dp_rucsac_1_0.out", "w", stdout);
    scanf("%u %u", &sacwg, &objnr);
    for (ui_t i = 1; i <= objnr; i++) {
        scanf("%u %u", &(objects[i].weight), &(objects[i].value));
    }
    process();
    printf("%u", cost[objnr][sacwg]);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
