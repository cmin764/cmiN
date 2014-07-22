/* sig.c

   Afiseaza continutul fisierului "/etc/services" la aparitia 
   semnalului SIGUSR2
   
   Autor: Sabin-Corneliu Buraga <busaco@infoiasi.ro> (c)1998-2001
   Ultima actualizare: 10 iulie 2001
*/
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>

void
sighandler (int sig)		/* functia de tratare a semnalului */
{
  pid_t pid;

  if ((pid = fork ()) < 0)	/* executam 'less' ca proces copil */
    {
      perror ("fork()");
      exit (1);
    }
  if (!pid)			/* copil */
    {
      execl ("/usr/bin/less", "less", "/etc/services", NULL);
      perror ("exec()");
      exit (1);
    }
  else				/* parinte */
    {
      if (wait (NULL) < 0)
	perror ("wait()");
    }
}

int
main ()				/* programul principal */
{
  /* atasam functia de tratare la semnalul SIGUSR2 */
  if (signal (SIGUSR2, sighandler) == SIG_ERR)
    {
      perror ("signal()");
      return 1;
    }
  /* asteptam aparitia unui semnal */
  pause ();
  return 0;
}
