#include <cstdio>

const int nMax = 100;
struct camera {
    int mere, pere;
} camere[nMax];
int nr;

void init()
{
    printf("Camere: ");
    scanf("%d", &nr);
    for (int i = 0; i < nr - 1; i++) {
        printf("Merele din camera %d: ", i + 1);
        scanf("%d", &camere[i].mere);
        printf("Perele din camera %d: ", i + 1);
        scanf("%d", &camere[i].pere);
    }
}

void back(int poz, int tip, int fructe, int calorii)
{
    if (poz == nr - 1) {
        printf("Fructe: %d, Calorii: %d\n", fructe, calorii);
    } else {
        if (tip) { // 1-mere 0-pere
            camere[poz].mere += fructe;
        } else {
            camere[poz].pere += fructe;
        }
        back(poz + 1, 1, camere[poz].mere, calorii + camere[poz].mere);
        back(poz + 1, 0, camere[poz].pere, calorii + camere[poz].pere);
        if (tip) {
            camere[poz].mere -= fructe;
        } else {
            camere[poz].pere -= fructe;
        }
    }
}

int main()
{
    init();
    back(0, 0, 0, 0);
    return 0;
}
