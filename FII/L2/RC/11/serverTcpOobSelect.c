/*  Server TCP ce utilizeaza select() pentru detectarea aparitiei de date OOB
   
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
#include <fcntl.h>
#include <signal.h>


/* portul folosit */
#define PORT 3234

/* eroarea returnata de unele apeluri */
extern int errno;


int client;

/* programul */
int main ()
{
  /* structurile pentru server si client */
  struct sockaddr_in server;
  struct sockaddr_in from;
  /* descriptori de socket */
  int sd;
  /* lungimea structurii sockaddr_in */
  int len;
  /* optiunea de reutilizarea a adresei pentru socket */
  char opt;
  /* numarul octetilor cititi*/
  int n;
  /* mesajul citit*/
  char msg[100]; 
  int justReadOOBData=0;  
  fd_set rfds,efds;

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
  
  printf ("Asteptam la portul %d...\n", PORT);
  fflush (stdout);
  /* servim in mod iterativ clientii... */
  while (1)
    {

        len = sizeof (from);
	printf("Astept clienti:\n");
      /* acceptam conexiunea din partea unui client */
	client = accept (sd, (struct sockaddr *) &from, &len);
      
     /* eroare la acceptarea conexiunii de la un client */
      if (client < 0)
	{
	  perror ("accept()");
	  continue;
	}
	
 	FD_ZERO(&rfds);
  	FD_ZERO(&efds);
	
      printf ("S-a conectat un client.\n");
      fflush (stdout);
     	
     for(; ;)
     {
     	FD_SET(client, &rfds);

	/* select() indica aparitia exceptiei pina cand procesul citeste si datele OOB; odata citite datele OOB
	ele sunt eliminate din buffer; daca facem apelul recv() cu MSG_OOB a doua oara se va intorce EINVAL */ 
	if(justReadOOBData==0) FD_SET(client,&efds);
	
	select(client+1, &rfds,NULL,&efds,NULL);
	
	if(FD_ISSET(client,&efds))
		{
			n=recv(client,msg,sizeof(msg)-1,MSG_OOB);
			msg[n]=0;
			printf("S-au citit %d OOB byte: %s\n", n, msg);
			justReadOOBData=1;
			FD_CLR(client, &efds);
		}
	
	if(FD_ISSET(client,&rfds))
		{
			
		     	 if((n=read(client,msg,sizeof(msg)-1))==0)
				{
					printf("Am primit EOF\n");
		     		        break;
				}
			else
				{
					msg[n]=0;
					printf("Am citit %d bytes: %s\n",n, msg);
					justReadOOBData =0;
				}

		}
       }
     printf("Inchid conexiunea cu clientul\n----------------------\n");
     close(client);
   }
}

