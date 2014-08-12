#include <stdio.h>
#include <unistd.h>

#define OUT "mesaj.txt"
#define TIME 1


int main()
{
    sleep(1);
    FILE *fout = fopen(OUT, "w");
    fprintf(fout, "%s\n", "Ana are mere.");
    fflush(fout);
    sleep(TIME);
    fprintf(fout, "%s\n", "Ana are mere 2.");
    fclose(fout);
    return 0;
}
