#include <cstdio>

const long nmax = 200001, mmax = 400000;
long total;
long nr_noduri, nr_muchii, nmselect;
long ciclu[nmax];
struct muchie {
    long x, y;
    int c;
} muchii[mmax], temp[mmax];

void merge(long begin, long mid, long end)
{
    long i, j, k;
    for (i = begin, j = mid, k = begin; i < mid && j < end; k++) {
        if (muchii[i].c < muchii[j].c) {
            temp[k] = muchii[i++];
        } else {
            temp[k] = muchii[j++];
        }
    }
    while (i < mid) {
        temp[k++] = muchii[i++];
    }
    while (j < end) {
        temp[k++] = muchii[j++];
    }
    for (i = begin; i < end; i++) {
        muchii[i] = temp[i];
    }
}

void mergesort(long begin, long end)
{
    if (begin < end - 1) {
        long mid = (begin + end) / 2;
        mergesort(begin, mid);
        mergesort(mid, end);
        merge(begin, mid, end);
    }
}

void kruskal()
{
    long i, j, nod1, nod2;
    for (i = 1; i <= nr_noduri; i++) {
        ciclu[i] = i;
    }
    i = 0;
    while (nmselect < nr_noduri - 1) {
        if ((nod1 = ciclu[muchii[i].x]) != (nod2 = ciclu[muchii[i].y])) {
            total += muchii[i].c;
            temp[nmselect++] = muchii[i];
            for (j = 1; j <= nr_noduri; j++) {
                if (ciclu[j] == nod2) {
                    ciclu[j] = nod1;
                }
            }
        }
        i++;
    }
}

void write(FILE* fout)
{
    fprintf(fout, "%ld\n", total);
    fprintf(fout, "%ld\n", nmselect);
    for (long i = 0; i < nmselect; i++) {
        fprintf(fout, "%ld %ld\n", temp[i].x, temp[i].y);
    }
}

int main()
{
    FILE* fin = fopen("apm.in", "rt");
    FILE* fout = fopen("apm.out", "wt");
    fscanf(fin, "%ld %ld", &nr_noduri, &nr_muchii);
    for (long i = 0; i < nr_muchii; i++) {
        fscanf(fin, "%ld %ld %d", &muchii[i].x, &muchii[i].y, &muchii[i].c);
    }
    mergesort(0, nr_muchii);
    kruskal();
    write(fout);
    fclose(fin);
    fclose(fout);
    return 0;
}
