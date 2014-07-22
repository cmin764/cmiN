/* cliTCP.c - Exemplu de client TCP 
   Trimite un nume la server; primeste de la server "Hello nume".
         
   Autor: Lenuta Alboaie  <adria@infoiasi.ro> (c)2009

*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>

/* codul de eroare returnat de anumite apeluri */
extern int errno;

/* portul de conectare la server*/
int port;

int main (int argc, char *argv[])
{
  int sd;			// descriptorul de socket
  struct sockaddr_in server;	// structura folosita pentru conectare 
  char msg[100];		// mesajul trimis

  /* exista toate argumentele in linia de comanda? */
  if (argc != 3)
    {
      printf ("[client] Sintaxa: %s <adresa_server> <port>\n", argv[0]);
      return -1;
    }

  /* stabilim portul */
  port = atoi (argv[2]);

  /* cream socketul */
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("[client] Eroare la socket().\n");
      return errno;
    }
  

  /* umplem structura folosita pentru realizarea conexiunii cu serverul */
  /* familia socket-ului */
  server.sin_family = AF_INET;
  /* adresa IP a serverului */
  server.sin_addr.s_addr = inet_addr(argv[1]);
  /* portul de conectare */
  server.sin_port = htons (port);
  
  /* ne conectam la server */
  if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
      perror ("[client]Eroare la connect().\n");
      return errno;
    }

  /* citirea mesajului */
  bzero (msg, 100);
  printf ("[client]Introduceti un nume: ");
  fflush (stdout);
  read (0, msg, 100);
  
  /* trimiterea mesajului la server */
  if (write (sd, msg, 100) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }

  /* citirea raspunsului dat de server 
     (apel blocant pina cind serverul raspunde) */
  if (read (sd, msg, 100) < 0)
    {
      perror ("[client]Eroare la read() de la server.\n");
      return errno;
    }
  /* afisam mesajul primit */
  printf ("[client]Mesajul primit este: %s\n", msg);

  /* inchidem conexiunea, am terminat */
  close (sd);
}
