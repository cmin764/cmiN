/*  Client TCP ce trimite octeti normali dar si date OOB 
   
    Autor: Lenuta Alboaie  <adria@infoiasi.ro> (c)2009
*/

#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <strings.h>
#include <stdlib.h>


int sd;				/* descriptor de socket */

int main (int argc, char *argv[])
{
  int n;
  int sd;
  /* structuri ale serverului */
  struct sockaddr_in server;
  
 
  if (argc != 3)
    {
      printf ("Sintaxa: %s <server> <port>\n", argv[0]);
      return 1;
    }
 
  /* completare structuri pentru server si client */
  server.sin_family = AF_INET;
  server.sin_port = htons (atoi (argv[2]));
  server.sin_addr.s_addr= inet_addr(argv[1]);
 
  /* creare socket */
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("socket()");
      exit (1);
    }
 
  /* conectare la server */
  if (connect (sd, (struct sockaddr *) &server, sizeof (server)) == -1)
    {
      perror ("connect()");
      exit (1);
    }

  printf ("[client]Ne-am conectat la server ... trimitem informatii\n");
  
  write(sd,"123",3);
  printf("[client] Scriem 3 octeti de date normale\n");
  /*sleep() - asigura ca ceea ce este scris sa fie transmis ca un singur segment TCP*/
  sleep(1);
  
  send(sd,"4",1,MSG_OOB);
  printf("[client] Scriem 1 octet de date OOB\n");
  sleep(1);

  write(sd,"56",2);
  printf("[client] Scriem 2 octeti de date normale\n");
  sleep(1);  

  send(sd,"7",1,MSG_OOB);
  printf("[client] Scriem 1 octet de date OOB\n");
  sleep(1);
  
  write(sd,"89",2);
  printf("[client] Scriem 2 octeti de date normale\n");
  sleep(1);

  exit(0);
	
}				/* main */
