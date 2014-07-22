#include <stdio.h>

const unsigned int nmax = 128;
unsigned int n, sum, num[nmax], smax, sums1[nmax], sums2[nmax], pick[nmax];

void read()
{
    smax = 0;
    FILE* fin = fopen("dp_sume.in", "r");
    fscanf(fin, "%u %u", &n, &sum);
    for (unsigned int i = 0; i < n; i++) {
        fscanf(fin, "%u", num + i);
        smax += num[i];
    }
    fclose(fin);
}

void write(bool flag)
{
    FILE* fout = fopen("dp_sume.out", "w");
    if (flag) {
        while (sum) {
            fprintf(fout, "%u ", pick[sum]);
            sum -= pick[sum];
        }
    } else {
        fprintf(fout, "IMPOSIBIL");
    }
    fclose(fout);
}

void process()
{
    for (unsigned int i = 0; i < n; i++) {
        sums2[num[i]] = 1;
        unsigned int j;
        for (j = 0; j <= sum; j++) {
            if (sums1[j] == 1) {
                sums2[j + num[i]] = 1;
            }
        }
        for (j = 0; j <= sum; j++) {
            if (sums2[j] == 1 && sums1[j] == 0) {
                sums1[j] = 1;
                pick[j] = num[i];
                sums2[j] = 0;
            }
        }
    }
}

int main()
{
    read();
    if (sum > smax) {
        write(false);
    } else {
        process();
        write(true);
    }
    return 0;
}
