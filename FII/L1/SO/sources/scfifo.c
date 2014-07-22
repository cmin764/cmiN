#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>


#define SV 1
#define CL 2

#define BUFL 128

#define check(a, b) !strcmp(a, b)


static inline int str_comp(const void * first, const void * second)
{
    return strcmp(*((char * *)first), *((char * *)second));
}


void process_file(char * fname, char * lines)
{
    /* open the file, read and sort all lines,
       then write the first 3 of them to `lines` buffer */

    int linesLen = 0;
    char * * linesVec = NULL;

    FILE * file = fopen(fname, "r");
    while (1) {
        char line[BUFL];
        fgets(line, BUFL, file);
        if (feof(file))
            break;

        linesVec = realloc(linesVec, ++linesLen * sizeof(char *));
        linesVec[linesLen - 1] = malloc((strlen(line) + 1) * sizeof(char));
        strcpy(linesVec[linesLen - 1], line);
    }
    fclose(file);

    qsort(linesVec, linesLen, sizeof(char *), str_comp);
    
    strcpy(lines, linesVec[0]);
    strcat(lines, linesVec[1]);
    strcat(lines, linesVec[2]);

    for (int i = 0; i < linesLen; ++i)
        free(linesVec[i]);
    free(linesVec);
}


int main(int argc, char * argv[])
{
    if (argc < 3) {
        printf("Usage: %s OPTION (NAME...|NAME FILE)\n", argv[0]);
        puts("Open a server or client using named pipes communication for processing a file.\n\
\n\
Options:\n\
    -s, --server    open for serving\n\
    -c, --client    open for sending\n\
\n\
Parameters:\n\
    NAME            path name(s) for FIFO(s)\n\
    FILE            file path for lines reading");
        return 1;
    }

    int whoami = 0;
    if (check(argv[1], "-s") || check(argv[1], "--server"))
        whoami = SV;
    else if (check(argv[1], "-c") || check(argv[1], "--client"))
        whoami = CL;

    if (whoami == SV) {
        // make FIFOs
        int fifoLen = argc - 2;
        // for input/output
        char * * fifoIn = malloc(sizeof(char *) * fifoLen);
        char * * fifoOut = malloc(sizeof(char *) * fifoLen);

        for (int i = 2; i < 2 + fifoLen; ++i) {
            int ind = i - 2;
            int len = sizeof(char) * (strlen(argv[i]) + 2);
            fifoIn[ind] = malloc(len);
            fifoOut[ind] = malloc(len);
            
            strcpy(fifoIn[ind], argv[i]);
            strcpy(fifoOut[ind], argv[i]);
            strcat(fifoIn[ind], "i");
            strcat(fifoOut[ind], "o");

            // rw-rw-rw-
            mkfifo(fifoIn[ind], 0666);
            mkfifo(fifoOut[ind], 0666);

        }

        // wait for messages, process them, then send the response
        for (int i = 0; i < fifoLen; ++i) {
            pid_t pid = fork();
            if (pid == 0) {
                // the child

                // open the pipe for reading
                int fin = open(fifoIn[i], O_RDONLY);
                char fname[BUFL] = {0};
                read(fin, fname, BUFL);
                close(fin);

                // read the filename, open and process it
                printf("Process %s on channel %s\n", fname, argv[i + 2]);
                char lines[3 * BUFL] = {0};
                process_file(fname, lines);

                // send the lines back to client
                int fout = open(fifoOut[i], O_WRONLY);
                write(fout, lines, strlen(lines));
                close(fout);

                return 0;
            }
        }
        // wait processes to finish
        for (int i = 0; i < fifoLen; ++i)
            wait(NULL);

        // free resources
        for (int i = 0; i < fifoLen; ++i) {
            unlink(fifoIn[i]);
            unlink(fifoOut[i]);
            free(fifoIn[i]);
            free(fifoOut[i]);
        }
        free(fifoIn);
        free(fifoOut);
    } else if (whoami == CL) {
        // prepare pipe names for i/o
        int len = sizeof(char) * (strlen(argv[2]) + 2);
        char * fifoIn = malloc(len);
        char * fifoOut = malloc(len);
        strcpy(fifoIn, argv[2]);
        strcat(fifoIn, "i");
        strcpy(fifoOut, argv[2]);
        strcat(fifoOut, "o");

        // open server's input for writing
        int fout = open(fifoIn, O_WRONLY);
        write(fout, argv[3], strlen(argv[3]));
        close(fout);

        // now receive the response
        int fin = open(fifoOut, O_RDONLY);
        char lines[3 * BUFL] = {0};
        read(fin, lines, 3 * BUFL);
        close(fin);

        puts(lines);

        free(fifoIn);
        free(fifoOut);
    } else {
        fputs("Invalid or no option selected\n", stderr);
        return 2;
    }

    return 0;
}
