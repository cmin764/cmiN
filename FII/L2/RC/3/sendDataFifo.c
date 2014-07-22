/* sendDataFifo.c   
  Exemplu de comunicare intre procese aflate pe aceeasi masina folosind FIFO-uri. Programul curent trimite date intr-un FIFO.
        
  Autor: Lenuta Alboaie <adria@infoiasi.ro> (c)2009  
*/ 


#include <stdio.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <string.h>
    #include <fcntl.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>

    #define FIFO_NAME "MyTest_FIFO"

    main()
    {
        char s[300];
        int num, fd;

      

        printf("Astept cititori...\n");
        fd = open(FIFO_NAME, O_WRONLY);
        printf("Am un cititor....introduceti ceva..\n");

        while (gets(s), !feof(stdin)) {
            if ((num = write(fd, s, strlen(s))) == -1)
                perror("Problema la scriere in FIFO!");
            else
                printf("S-au scris in FIFO %d bytes\n", num);
        }
    }

