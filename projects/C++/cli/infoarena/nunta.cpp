#include <cstdio>

unsigned short petitori[50], v, n;
bool valori[21];

void remove(unsigned short pos) {
    for (unsigned short i = pos + 1; i < n; i++) {
        petitori[i - 1] = petitori[i];
    }
    n--;
}

void insert(unsigned short pos, unsigned short value)
{
    for (unsigned short i = n; i > pos; i--) {
        petitori[i] = petitori[i - 1];
    }
    petitori[pos] = value;
    n++;
}

void back()
{
    if (n == 1) {
        if (!valori[petitori[0]]) {
            v++;
            valori[petitori[0]] = 1;
        }
    } else {
        unsigned short i, win, los, oldv;
        for (i = 0; i < n - 1; i++) {
            win = los = i;
            if (petitori[i] > petitori[i + 1]) {
                los++;
            } else {
                win++;
            }
            oldv = petitori[los];
            petitori[win] -= oldv;
            remove(los);
            back();
            insert(los, oldv);
            petitori[win] += oldv;
        }
    }
}

int main()
{
    unsigned short i;
    freopen("nunta.in", "rt", stdin);
    freopen("nunta.out", "wt", stdout);
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &petitori[i]);
    }
    back();
    printf("%d\n", v);
    for (i = 0; i < 21; i++) {
        if (valori[i]) {
            printf("%d ", i);
        }
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
