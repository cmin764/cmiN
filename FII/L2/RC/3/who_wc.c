/* who_wc.c

   Simularea constructiei shell "who | wc" folosind un pipe si 
   duplicarea descriptorilor.
   
   Autor: Sabin-Corneliu Buraga <busaco@infoiasi.ro> (c)1998-2002, 2005
   Versiunea: 1.1 (ultima actualizare: 17 februarie 2005)
*/   
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void
who_wc () /* who | wc -l */
{
  int pfd[2];                        /* un pipe */

  /* cream pipe-ul */
  if (pipe (pfd) == -1)         
    {
      fprintf (stderr, "pipe\n");
      exit (1);
    }
  /* cream primul copil */  
  switch (fork ())              
    {
    case -1:
      fprintf (stderr, "fork - 1\n");
      exit (1);
    case 0:                        /* copilul */
      close (1);
      /* duplicam descriptorul de scriere al pipe-ului
         la iesirea standard (1) */
      if (dup (pfd[1]) != 1)    
        {
          fprintf (stderr, "dup - 1\n");
          exit (1);
        }
      /* putem inchide descriptorii pipe-ului,
         din moment ce am realizat duplicarea */        
      close (pfd[0]);
      close (pfd[1]);
      /* se  executa comanda "who"
         datele vor fi trimise descriptorului de scriere
         al pipe-ului */
      execlp ("who", "who", NULL);
      fprintf (stderr, "exec - 1\n");
      exit (1);
    }
  /* cream al doilea copil */  
  switch (fork ())
    {
    case -1:
      fprintf (stderr, "fork - 2\n");
      exit (1);
    case 0:                        /* copilul */
      close (0);
      /* duplicam descriptorul de intrare al pipe-ului
         care va fi asociat intrarii standard */
      if (dup (pfd[0]) != 0)
        {
          fprintf (stderr, "dup - 2\n");
          exit (1);
        }
      /* descriptorii pipe-ului pot fi inchisi */
      close (pfd[0]);
      close (pfd[1]);
      /* executam comanda "wc" care va citi datele
         de la intrarea standard, acum redirectata
         la descriptorul de intrare al pipe-ului */
      execlp ("wc", "wc", "-l", NULL);
      fprintf (stderr, "exec - 2\n");
      exit (1);
    }
  /* parintele */
  /* inchidem pipe-ul, nu-l folosim deloc */
  close (pfd[0]);
  close (pfd[1]);
  /* asteptam terminarea copiilor */
  while (wait (NULL) != -1)
    ;
}

int
main () /* programul principal */
{
  who_wc ();
  return 0;
} 