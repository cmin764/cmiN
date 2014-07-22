/* servTCPIt.c - Exemplu de server UDP
   Asteapta un nume de la clienti; intoarce clientului sirul
   "Hello nume".
   
   Autor: Lenuta Alboaie  <adria@infoiasi.ro> (c)2009
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* portul folosit */
#define PORT 2728

/* codul de eroare returnat de anumite apeluri */
extern int errno;

int main ()
{
  struct sockaddr_in server;	// structura folosita de server
  struct sockaddr_in client;	
  char msg[100];		//mesajul primit de la client 
  char msgrasp[100]=" ";        //mesaj de raspuns pentru client
  int sd;			//descriptorul de socket 

  /* crearea unui socket */
  if ((sd = socket (AF_INET, SOCK_DGRAM, 0)) == -1)
    {
      perror ("[server]Eroare la socket().\n");
      return errno;
    }

  /* pregatirea structurilor de date */
  bzero (&server, sizeof (server));
  bzero (&client, sizeof (client));
  
  /* umplem structura folosita de server */
  /* stabilirea familiei de socket-uri */
    server.sin_family = AF_INET;	
  /* acceptam orice adresa */
    server.sin_addr.s_addr = htonl (INADDR_ANY);
  /* utilizam un port utilizator */
    server.sin_port = htons (PORT);
  
  /* atasam socketul */
  if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
    {
      perror ("[server]Eroare la bind().\n");
      return errno;
    }

  
  /* servim in mod iterativ clientii... */
  while (1)
    {
      int msglen;
      int length = sizeof (client);

      printf ("[server]Astept la portul %d...\n",PORT);
      fflush (stdout);

      bzero (msg, 100);
      
      /* citirea mesajului primit de la client */
      if ((msglen = recvfrom(sd, msg, 100, 0,(struct sockaddr*) &client, &length)) <= 0)
	{
	  perror ("[server]Eroare la recvfrom() de la client.\n");
	  return errno;
	}
	
      printf ("[server]Mesajul a fost receptionat...%s\n", msg);
      
      /*pregatim mesajul de raspuns */
      bzero(msgrasp, 100);
      strcat(msgrasp, "Hello ");
      strcat(msgrasp, msg);
      
      printf("[server]Trimitem mesajul inapoi...%s\n",msgrasp);
      
      
      /* returnam mesajul clientului */
      if (sendto(sd, msgrasp, 100, 0, (struct sockaddr*) &client, length) <= 0)
	{
	  perror ("[server]Eroare la sendto() catre client.\n");
	  continue;		/* continuam sa ascultam */
	}
      else
	printf ("[server]Mesajul a fost trasmis cu succes.\n");

    }				/* while */
}				/* main */
