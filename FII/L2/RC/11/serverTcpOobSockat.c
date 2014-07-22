/* Server TCP interativ ce apeleaza sokatmark() pentru a determina aparitia
unui octet OOB
   
    Autor: Lenuta Alboaie  <adria@infoiasi.ro> (c)2009
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <strings.h>
#include <stdlib.h>


/* portul folosit */
#define PORT 3034

/* eroarea returnata de unele apeluri */
extern int errno;


/* programul */
int main ()
{
  /* structurile pentru server si client */
  struct sockaddr_in server;
  struct sockaddr_in from;
  /* descriptori de socket */
  int sd, client;
  /* lungimea structurii sockaddr_in */
  int len;
  /* optiunea de reutilizarea a adresei pentru socket */
  char opt;
  int on=1, n;
  char msg[100]; 

  /* creare socket */
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("socket()");
      exit (1);
    }
  /* pregatim structurile de date */
  bzero (&server, sizeof (server));
  /* umplem structura folosita de server */
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl (INADDR_ANY);
  server.sin_port = htons (PORT);

  opt = 1;
  /* setam optiunea de a reutiliza portul */
  setsockopt (sd, SOL_SOCKET, SO_REUSEADDR, (void *) &opt, sizeof (opt));

  /* atasam socketul */
  if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
    {
      perror ("bind()");
      exit (1);
    }

  /* punem serverul sa asculte daca vin clienti sa se conecteze */
  if (listen (sd, 5) == -1)
    {
      perror ("listen()");
      exit (1);
    }
  /*setam optiunea SO_OOBINLINE pentru sd*/
  setsockopt(sd, SOL_SOCKET, SO_OOBINLINE,&on,sizeof(on));
  printf ("Asteptam la portul %d...\n", PORT);
  fflush (stdout);
  /* servim in mod iterativ clientii... */
  while (1)
    {
      len = sizeof (from);
      /* acceptam conexiunea din partea unui client */
	printf("Astept clienti:\n");
      client = accept (sd, (struct sockaddr *) &from, &len);
      /*!!! client mosteneste optiunile de socket de la sd */
      /* eroare la acceptarea conexiunii de la un client */
      if (client < 0)
	{
	  perror ("accept()");
	  continue;
	}
      printf ("S-a conectat un client.\n");
      fflush (stdout);
   
      /*dam timp emitatorului sa trimita toate datele*/	
      sleep(3);
 
	
     for(; ;)
     {
     	 if(sockatmark(client)) 
		{	
			printf("OOB mark ...\n ");
			
		}

     	 if((n=read(client,msg,sizeof(msg)))==0)
		{
			printf("Am primit EOF\n");
     		        break;
		}
	else
		{
			msg[n]=0;
			printf("Am citit %d octeti: %s\n",n, msg);
		}
       }
     printf("Inchid conexiunea cu clientul\n----------------------\n");
     close(client);
   }
}

