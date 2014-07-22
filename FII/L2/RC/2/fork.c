/* fork.c   
  Exemplu de executie concurenta a doua procese parinte si copil, folosind primitiva 
  fork.      
  Autor: Lenuta Alboaie <adria@infoiasi.ro> (c)2009  
*/  
    #include <stdio.h> 
    #include <stdlib.h>
    #include <errno.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>

    main()
    {
        pid_t pid;
        int rv;

        switch(pid=fork()) {
            case -1:
                perror("fork");  
                exit(1);        

            case 0:
                printf(" PC: Proces Copil!\n");
                printf(" PC: Am PID-ul %d\n", getpid());
                printf(" PC: PID-ul parintelui este %d\n", getppid());
                printf(" PC: Da-mi un status de iesire: ");
                scanf(" %d", &rv);
                printf(" PC: Am plecat!\n");
                exit(rv);

            default:
                printf("PP: Proces Parinte!\n");
                printf("PP: Am PID-ul %d\n", getpid());
                printf("PP: Am copil cu pidul %d\n", pid);
                printf("PP: Astept ca PC sa apeleze exit()...\n");
                wait(&rv);
                printf("PP: Statusul de iesire al PC este: %d\n", WEXITSTATUS(rv));
                printf("PP: Am plecat!\n");
        }
    }

