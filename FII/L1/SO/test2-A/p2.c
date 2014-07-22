/*******************************************************************************************************
Enunt a doua problema:

Programul de mai jos contine trei erori sintactice (adica, detectabile la compilare), si ar trebui sa ofere
urmatoarea functionalitate: se creaza un nou proces ; procesul nou creat citeste de la tastatura doua numere n si m si le scrie valorile intr-un pipe; dupa terminarea de executat a fiului, procesul parinte calculeaza valoarea lui n^m si o afiseaza pe ecran.

Corectati in programul de mai jos cele trei erori introduse voluntar in asa fel incat sa obtineti un program corect.
Dupa linia pe care ati facut o corectie, includeti si o explicatie ca si comentariu pentru a obtine punctajul integral.


NOTA: pastrati enuntul in acest comentariu si scrieti rezolvarea mai jos.
*******************************************************************************************************/

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>   // necesar pentru i/o cu printf/scanf
#include<sys/types.h>
#include<sys/stat.h>
#include <sys/wait.h>    // pentru a folosi wait explicit

int power(int,int);
int main()
{
int p[2],n,m;
pid_t pid;    // pid-ul trebuie sa fie de tipul pid_t
int nr1,nr2,t;
if (-1 == pipe(p))
{
printf("Error on creating pipe");
exit(1);
}

if (-1 == (pid = fork()))    // fork in loc de pfork (pentru a crea un nou proces)
{
printf("Error on creating new process");
exit(3);
}
if (pid == 0)
{
		printf("n=");
		scanf("%d",&n);
                write(p[1],&n,sizeof(int));
                printf("m=");
		scanf("%d",&m);
                write(p[1],&m,sizeof(int));
  	 
 return 0;
}
if (pid !=0)
{
wait(NULL);   // nu exista null ci NULL din stdlib.h
read(p[0],&nr1,sizeof(int));
read(p[0],&nr2,sizeof(int));
t=power(nr1,nr2);
printf("n ^ m = %d",t);
}

return 0;
}

int power(int n,int m)
{
    int d =1;
    int i;
    for (i = 0; i < m; i++)
       d=d*n;
    return d;
}
