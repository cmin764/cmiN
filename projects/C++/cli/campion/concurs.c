#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define inf 0xFFff

typedef struct {
    uint8_t nr, * ind;
    int16_t wg;
} echipa;

uint8_t cnr, ctot, enr, * cvec, sz, * used;
echipa* evec;
uint16_t smin = inf, sum;
char* mystr, tmp[3];
void gen_echipa(uint8_t, uint8_t);

inline uint16_t absv(int16_t param)
{
    if (param < 0) {
        param *= -1;
    }
    return (uint16_t)param;
}

void init()
{
    uint8_t i;
    scanf("%u %u", &cnr, &enr);
    ctot = cnr;
    cvec = (uint8_t*)malloc(cnr * sizeof(uint8_t));
    used = (uint8_t*)malloc(cnr * sizeof(uint8_t));
    evec = (echipa*)malloc(enr * sizeof(echipa));
    for (i = 0; i < cnr; ++i) {
        scanf("%u", cvec + i);
        used[i] = 0;
    }
    for (i = 0; i < enr; ++i) {
        evec[i].nr = 0;
        evec[i].ind = 0;
        evec[i].wg = 0;
    }
}

void add(uint8_t cur, uint8_t poz, uint8_t nMax)
{
    uint8_t i;
    if (poz == evec[cur].nr) {
        gen_echipa(cur + 1, nMax - evec[cur].nr + 1);
    } else {
        for (i = 0; i < cnr; ++i) {
            if (!used[i]) {
                evec[cur].ind[poz] = i + 1;
                used[i] = 1;
                --ctot;
                evec[cur].wg += cvec[i];
                add(cur, poz + 1, nMax);
                evec[cur].wg -= cvec[i];
                ++ctot;
                used[i] = 0;
            }
        }
    }
}

void gen_echipa(uint8_t cur, uint8_t nMax)
{
    uint8_t i, j;
    if (cur == enr) {
        if (ctot) {
            return;
        }
        sum = 0;
        for (i = 0; i < enr - 1; ++i) {
            for (j = i + 1; j < enr; ++j) {
                sum += absv(evec[i].wg - evec[j].wg);
            }
        }
        if (sum < smin) {
            smin = sum;
            sz = 1;
            mystr = (char*)realloc(mystr, sz * sizeof(char));
            mystr[sz - 1] = '\0';
            for (i = 0; i < enr; ++i) {
                sz += 2 * evec[i].nr;
                mystr = (char*)realloc(mystr, sz * sizeof(char));
                for (j = 0; j < evec[i].nr; ++j) {
                    sprintf(tmp, "%u ", evec[i].ind[j]);
                    strcat(mystr, tmp);
                }
                mystr[sz - 2] = '\n';
            }
        }
    } else {
        for (i = 1; i <= nMax; ++i) {
            evec[cur].wg = 0;
            evec[cur].nr = i;
            evec[cur].ind = (uint8_t*)realloc(evec[cur].ind, evec[cur].nr * sizeof(uint8_t));
            add(cur, 0, nMax);
        }
    }
}

int main()
{
    freopen("concurs.in", "rt", stdin);
    freopen("concurs.out", "wt", stdout);
    init();
    gen_echipa(0, cnr - enr + 1);
    printf("%u\n%s", smin, mystr);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
