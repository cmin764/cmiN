#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/capability.h>
#include <sys/prctl.h>
#include <sys/types.h>

/*
1. Compilare cu make (makefile facut in prealabil)
2. sudo -H setcap cap_setuid,cap_setgid+ep cap (effective + permit)
3. ./cap (ruleaza si are acces de root)
4. e deja facut in folder fara noSUID si nu e nevoie sa fie mutat
5. filecap /mnt/C/Repos/cmiN/FII/L3/SI/5/lab/cap (listeaza capabilitati)
*/

int main(int argc, char **argv)
{
printf("cap_setuid and cap_setgid: %d\n", prctl(PR_CAPBSET_READ, CAP_SETUID|CAP_SETGID, 0, 0, 0));
printf("Capabilitati fisier: %s\n", cap_to_text(cap_get_file(argv[0]), NULL));
printf("Capabilitati proces: %s\n", cap_to_text(cap_get_proc(), NULL));
if (setresuid(0, 0, 0))
{
printf("setresuid(): %s\n", strerror(errno));
}
else
{
char *args[] = {NULL};
char *env[] = {NULL};
execve("/bin/sh", args, env);
}
}
