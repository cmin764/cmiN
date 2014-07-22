#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


#define N 3


int main()
{
    FILE * fvec[N];
    for (int i = 0; i < N; ++i) {
        char fname[8];
        sprintf(fname, "f%di", i + 1); 
        fvec[i] = fopen(fname, "w");
    }

    printf("Numere: ");
    int nr, ind = 0;
    while (1) {
        scanf("%d", &nr);
        if (!nr)
            break;
        fprintf(fvec[ind % N], "%d ", nr);
        ++ind;
    }

    for (int i = 0; i < N; ++i) {
        fprintf(fvec[i], "0");
        fclose(fvec[i]);

        pid_t pid = fork();
        if (pid == 0) {
            char fname[8];
            sprintf(fname, "f%di", i + 1);
            execl("worker", "worker", fname);
            exit(0);
        }
    }

    for (int i = 0; i < N; ++i)
        wait(NULL);

    int total = 0;
    for (int i = 0; i < N; ++i) {
        int nr;
        char fname[8];
        sprintf(fname, "f%do", i + 1);
        FILE * fin = fopen(fname, "r");
        fscanf(fin, "%d", &nr);
        fclose(fin);
        total += nr;
    }

    printf("Total: %d\n", total);
    return 0;
}
