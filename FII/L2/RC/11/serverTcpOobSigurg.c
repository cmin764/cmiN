/*  Server TCP ce trateaza semnalul SIGURG  atunci cind apar date OOB
   
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

void urgHandler(int);
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

      signal(SIGURG,urgHandler);
	/*setarea proprietarului socketului conectat */
     fcntl(client, F_SETOWN, getpid());

      printf ("S-a conectat un client.\n");
      fflush (stdout);
     
    
	
     for(; ;)
     {
     
     	 if((n=read(client,msg,sizeof(msg)-1))==0)
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


void urgHandler(int signnr)
{
	int n;
	char buff[100];
	printf("SIGURG e primit\n");
	n=recv(client,buff, sizeof(buff)-1, MSG_OOB);
        buff[n]='\0';
        printf("Am citit %d octet OOB %s\n",n, buff);
}
