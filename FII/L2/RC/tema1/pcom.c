/*
 * pcom: inter-process minimal basic protocol
 * Copyright (C) 2013  cmiN
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


// pipe I/O
#define SV 0
#define CL 1

// maximum allowed lengths for
#define ULEN 64      // user
#define CLEN 128     // command
#define RLEN 1024    // response


void test_users(char ** users, int ulen)
{
    for (int i = 0; i < ulen; ++i)
        puts(users[i]);
}



int listener(int pio[][2], char fname[])
{
    /// Function handled by the child process waiting for commands.

    char tmp[ULEN];           // temporary line buffer
    int ulen = 0;             // number of users 
    char **users = NULL;      // user list

    // open and load data from input file
    FILE *fin = fopen(fname, "r");
    while (fgets(tmp, ULEN, fin)) {
        // discard EOL
        int len = strlen(tmp);
        if (tmp[len - 1] == '\n')
            --len;
        tmp[len] = '\0';
        // add a new user to the list
        users = realloc(users, sizeof(char*) * ++ulen);
        users[ulen - 1] = malloc(sizeof(char) * (len + 1));
        strcpy(users[ulen - 1], tmp);
    }
    fclose(fin);
    //test_users(users, ulen);

    int quit = 0;
    int found = 0;    // logged in or not

    while (!quit) {    // receive and execute commands until quit
        char com[CLEN];
        int clen = 0;
        // read a command char by char until EOL is reached
        while (1) {
            // read one char from the pipe
            char chr;
            if (read(pio[SV][0], &chr, 1) == -1) {
                perror("Receive command");
                return 32;
            }
            // write and check it
            com[clen++] = chr;
            if (chr == '\n') {
                com[clen - 1] = '\0';
                break;    // end of command
            }
        }

        // response
        char resp[RLEN];
        memset(resp, 0, RLEN);
        int rlen = 0;

        // execute it
        if (!strcmp(com, "quit")) {
            strcpy(resp, "Exited");
            quit = 1;
        } else if (!strncmp(com, "login", strlen("login"))) {
            // extract user name
            char uname[ULEN];
            memset(uname, 0, ULEN);
            sscanf(com, "%*s %s", uname);
            //fprintf(stderr, "Debug uname: %s\n", uname);
            // search for it
            found = 0;
            for (int i = 0; i < ulen && !found; ++i)
                if (!strcmp(uname, users[i]))
                    found = 1;
            if (found)
                strcpy(resp, "Login succeeded");
            else
                strcpy(resp, "Login failed");
        } else if (!strcmp(com, "help")) {
            char * help = "Available commands:\n\
    help          print this message\n\
    quit          quit the program\n\
    login USER    user name authentication\n\
    wc FILE       word(s) count\n\
    find FILE     find a file and show some info about it";
            strcpy(resp, help);
        } else if (!strncmp(com, "wc", strlen("wc")) ||
                   !strncmp(com, "find", strlen("find"))) {
            if (found) {
                char bin[CLEN], param[CLEN];
                memset(bin, 0, CLEN);
                memset(param, 0, CLEN);
                sscanf(com, "%s %s", bin, param);
                // temporary pipe
                int tfd[2];
                pipe(tfd);
                if (fork() == 0) {
                    // redirect stdout to the write end
                    dup2(tfd[1], STDOUT_FILENO);
                    dup2(tfd[1], STDERR_FILENO);
                    close(tfd[1]);
                    close(tfd[0]);
                    if (!strcmp(bin, "wc"))
                        execlp(bin, bin, param, NULL);
                    else
                        execlp(bin, bin, "-type", "f", "-name", param,
                               "-exec", "stat", "{}", ";", NULL);
                    exit(0);    // just to be sure
                } else {
                    wait(NULL);
                    fcntl(tfd[0], F_SETFL, O_NONBLOCK);
                    while(read(tfd[0], &resp[rlen++], 1) != -1);
                    rlen -= 2;
                    resp[rlen] = '\0';
                    //printf("Debug resp[-1]: %d\n", (int)resp[rlen - 1]);
                }
            } else
                strcpy(resp, "Not authenticated");
        } else
            strcpy(resp, "Invalid command");

        // write the response
        rlen = strlen(resp);
        if (write(pio[CL][1], &rlen, sizeof(int)) == -1) {
            perror("Send response size");
            return 16;
        }
        if (write(pio[CL][1], resp, rlen) == -1) {
            perror("Send response text");
            return 16;
        }
    }

    for (int i = 0; i < ulen; ++i)
        free(users[i]);
    free(users);

    // all fine
    return 0;
}


int commander(int pio[][2])
{
    int quit = 0;
    while (!quit) {
        // wait for a command
        printf(">>> ");
        char com[CLEN];
        if (!fgets(com, CLEN, stdin)) {
            perror("Read command");
            return 8;
        }
        // check for quit
        if (!strncmp(com, "quit", strlen("quit")))
            quit = 1;
        // send it
        if (write(pio[SV][1], com, strlen(com)) == -1) {
            perror("Send command");
            return 16;
        }
        // receive response
        char resp[RLEN];
        int rlen;
        // read message length
        if (read(pio[CL][0], &rlen, sizeof(int)) == -1) {
            perror("Receive response size");
            return 32;
        }
        // read the whole message
        if (read(pio[CL][0], resp, rlen) == -1) {
            perror("Receive response text");
            return 32;
        }
        // print it
        resp[rlen] = '\0';
        puts(resp);
    }

    return 0;
}


int main(int argc, char *argv[])
{
    // check arguments
    if (argc != 2) {
        printf("Usage: %s CONFIG\n", argv[0]);
        return 1;
    }

    // create and init the pair of pipes
    int pio[2][2];
    if (pipe(pio[SV]) == -1 || pipe(pio[CL]) == -1) {
        perror("Pipes");
        return 2;
    }
    // create a child
    pid_t proc = fork();
    if (proc == -1) {
        perror("New process");
        return 4;
    }

    // bisect logic
    if (proc == 0)
        return listener(pio, argv[1]);
    int prcode = commander(pio);
    int crcode;
    wait(&crcode);
    return prcode + crcode;
}
