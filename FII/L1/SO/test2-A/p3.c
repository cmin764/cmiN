/*******************************************************************************************************
Enunt a treia problema:

Sa se scrie un program C care va creea 2 procese fiu. 
Parintele va genera 2 numere aleatoare a si b, mai mici decat 10, si le va transmite fiilor. 
Primul fiu va calcula a la puterea b, iar al doilea va calcula b la puterea a. 
Rezultatele vor fi trimise inapoi parintelui care va afisa diferenta in modul dintre rezultate. 
Pentru comunicarea intre procese, folositi canale anonime.

*******************************************************************************************************/


#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{
    srand(time(NULL));
    int a = rand() % 10, b = rand() % 10;
    fprintf(stderr, "Debug: %d %d\n", a, b);

    pid_t f1, f2;
    int ps1[2], ps2[2];
    int sp1[2], sp2[2];

    pipe(ps1);
    pipe(ps2);
    pipe(sp1);
    pipe(sp2);

    f1 = fork();
    if (f1 == 0) {
        // fiul 1
        int a, b;
        read(ps1[0], &a, sizeof(int));
        read(ps1[0], &b, sizeof(int));
        int res = pow(a, b);
        write(sp1[1], &res, sizeof(int));
        exit(0);
    }

    f2 = fork();

    if (f2 == 0) {
        // fiul 2
        int a, b;
        read(ps2[0], &a, sizeof(int));
        read(ps2[0], &b, sizeof(int));
        int res = pow(b, a);
        write(sp2[1], &res, sizeof(int));
        exit(0);
    }

    write(ps1[1], &a, sizeof(int));
    write(ps1[1], &b, sizeof(int));
    write(ps2[1], &a, sizeof(int));
    write(ps2[1], &b, sizeof(int));

    int res1, res2;
    read(sp1[0], &res1, sizeof(int));
    read(sp2[0], &res2, sizeof(int));

    wait(NULL);
    wait(NULL);

    printf("%d\n", abs(res1 - res2));

    return 0;
}
