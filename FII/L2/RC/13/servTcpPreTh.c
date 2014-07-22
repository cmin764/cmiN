/* servTCPPreTh.c - Exemplu de server TCP concurent care deserveste clientii
   printr-un mecanism de prethread-ing; cu blocarea mutex de protectie a lui accept(); 
   Asteapta un numar de la clienti si intoarce clientilor numarul incrementat.
  
   
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
#include <signal.h>
#include <pthread.h>

/* portul folosit */
#define PORT 2909

/* codul de eroare returnat de anumite apeluri */
extern int errno;

static void *treat(void *); /* functia executata de fiecare thread ce realizeaza comunicarea cu clientii */
//void raspunde(void *);

typedef struct {
	pthread_t idThread; //id-ul thread-ului
	int thCount; //nr de conexiuni servite
}Thread;

Thread *threadsPool; //un array de structuri Thread

int sd; //descriptorul de socket de ascultare
int nthreads;//numarul de threaduri
pthread_mutex_t mlock=PTHREAD_MUTEX_INITIALIZER;              // variabila mutex ce va fi partajata de threaduri

void raspunde(int cl,int idThread);

int main (int argc, char *argv[])
{
  struct sockaddr_in server;	// structura folosita de server  	
  void threadCreate(int);

   if(argc<2)
   {
        fprintf(stderr,"Eroare: Primul argument este numarul de fire de executie...");
	exit(1);
   }
   nthreads=atoi(argv[1]);
   if(nthreads <=0)
	{
        fprintf(stderr,"Eroare: Numar de fire invalid...");
	exit(1);
	}
    threadsPool = calloc(sizeof(Thread),nthreads);

   /* crearea unui socket */
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("[server]Eroare la socket().\n");
      return errno;
    }
  /* utilizarea optiunii SO_REUSEADDR */
  int on=1;
  setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
  
  /* pregatirea structurilor de date */
  bzero (&server, sizeof (server));

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

  /* punem serverul sa asculte daca vin clienti sa se conecteze */
  if (listen (sd, 2) == -1)
    {
      perror ("[server]Eroare la listen().\n");
      return errno;
    }

   printf("Nr threaduri %d \n", nthreads); fflush(stdout);   int i;
   for(i=0; i<nthreads;i++) threadCreate(i);

	
  /* servim in mod concurent clientii...folosind thread-uri */
  for ( ; ; )
    {
	printf ("[server]Asteptam la portul %d...\n",PORT);
        pause();				
     }//while    
};				
void threadCreate(int i)
{
	void *treat(void *);
	
	pthread_create(&threadsPool[i].idThread,NULL,&treat,(void*)i);
	return; /* threadul principal returneaza */
}

void *treat(void * arg)
{		
		int client;
		        
		struct sockaddr_in from; 
		  bzero (&from, sizeof (from));
      				printf ("[thread]- %d - pornit...\n", (int) arg);fflush(stdout);

		for( ; ; )
		{
			int length = sizeof (from);
			pthread_mutex_lock(&mlock);
			//printf("Thread %d trezit\n",(int)arg);
			if ( (client = accept (sd, (struct sockaddr *) &from, &length)) < 0)
				{
	 			 perror ("[thread]Eroare la accept().\n");	  			
				}
			pthread_mutex_unlock(&mlock);
			threadsPool[(int)arg].thCount++;

			raspunde(client,(int)arg); //procesarea cererii
			/* am terminat cu acest client, inchidem conexiunea */
			close (client);			
		}	
};


void raspunde(int cl,int idThread)
{
        int nr;		//mesajul primit de trimis la client  
	
	if (read (cl, &nr,sizeof(int)) <= 0)
			{
			  printf("[Thread %d]\n",idThread);
			  perror ("Eroare la read() de la client.\n");
			
			}
	
	printf ("[Thread %d]Mesajul a fost receptionat...%d\n",idThread, nr);
		      
		      /*pregatim mesajul de raspuns */
		      nr++;      
	printf("[Thread %d]Trimitem mesajul inapoi...%d\n",idThread, nr);
		      
		      
		      /* returnam mesajul clientului */	 if (write (cl, &nr, sizeof(int)) <= 0)
		{
		 printf("[Thread %d] ",idThread);
		 perror ("[Thread]Eroare la write() catre client.\n");
		}
	else
		printf ("[Thread %d]Mesajul a fost trasmis cu succes.\n",idThread);	

}
