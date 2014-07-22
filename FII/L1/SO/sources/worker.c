#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char * argv[])
{
    if (argc != 2) {
        printf("Usage: %s IN\n", argv[0]);
        exit(1);
    }

    FILE* fin = fopen(argv[1], "r");
    int sum = 0;
    while (1) {
        int nr;
        fscanf(fin, "%d", &nr);
        if (!nr)
            break;
        sum += nr;
    }
    fclose(fin);

    char fname[8];
    strcpy(fname, argv[1]);
    *(strchr(fname, 'i')) = 'o';
    FILE* fout = fopen(fname, "w");
    fprintf(fout, "%d\n", sum);
    fclose(fout);
}
