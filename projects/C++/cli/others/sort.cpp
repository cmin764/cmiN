#include <cstdio>
#include <cstdlib>
#include <cstring>

const int n = 128;

void write(int vec[], int len)
{
    for (int i = 0; i < len; i++) {
        printf("%d ", vec[i]);
    }
}

void merge(int vec[], int begin, int mid, int end)
{
    int tmp[n], i, j, k;
    for (i = begin, j = mid, k = begin; i < mid && j < end; k++) {
        if (vec[i] < vec[j]) {
            tmp[k] = vec[i++];
        } else {
            tmp[k] = vec[j++];
        }
    }
    while (i < mid) {
        tmp[k++] = vec[i++];
    }
    while (j < end) {
        tmp[k++] = vec[j++];
    }
    for (i = begin; i < end; i++) {
        vec[i] = tmp[i];
    }
}

void mergesort(int vec[], int begin, int end)
{
    if (begin < end - 1) {
        int mid = (begin + end) / 2;
        mergesort(vec, begin, mid);
        mergesort(vec, mid, end);
        merge(vec, begin, mid, end);
    }
}

void quicksort(int vec[], int low, int high)
{
    int i = low, j = high, piv;
    piv = vec[low + rand() % (high - low)];
    while (i <= j) {
        while (vec[i] < piv) {
            i++;
        }
        while (vec[j] > piv) {
            j--;
        }
        if (i <= j) {
            int tmp = vec[i];
            vec[i] = vec[j];
            vec[j] = tmp;
            i++;
            j--;
        }
    }
    if (low < j) {
        quicksort(vec, low, j);
    }
    if (i < high) {
        quicksort(vec, i, high);
    }
}

int main(int argc, char* argv[])
{
    int vec[n], len = 0;
    char* mode;
    if (argc > 2) {
        mode = argv[1];
        while (argc-- > 2) {
            vec[argc - 2] = atoi(argv[argc]);
            len++;
        }
    } else {
        printf("Usage: sort.exe <mode> <space separated numbers>\n");
        return 0;
    }
    if (!strcmp(mode, "merge")) {
        mergesort(vec, 0, len);
    } else if (!strcmp(mode, "quick")) {
        quicksort(vec, 0, len - 1);
    } else {
        printf("Invalid mode %s. Must be \"quick\" or \"merge\".\n", mode);
        return 0;
    }
    write(vec, len);
    return 0;
}
