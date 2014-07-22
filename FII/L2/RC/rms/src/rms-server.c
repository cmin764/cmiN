/*
 * rms-server: Release Management System - server
 *
 * Author: cmin764@yahoo/gmail.com
 */


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <netinet/in.h>
#include <arpa/inet.h>


// default server settings
#define CPATH "res/rms.conf"    // config path
#define PEXT ".tar.gz"          // package extension

// other constants
#define BLEN 128    // default buffer length
#define OCOUNT 2    // number of options
#define DEBUG 1     // print debugging messages
#define ASYNC 1     // asynchronous processing


typedef struct {
    int port;            // custom server port
    char ppath[BLEN];    // extensions path
} options_t;


typedef enum {
    PORT,
    PPATH
} option_c;

typedef enum {
    SEARCH,
    DOWNLOAD
} task_c;


options_t options = {.port = 0, .ppath = ""};


static inline int str2const(const char *key)
{
    static const char *choices[OCOUNT] = {"port", "ppath"};
    for (int i = 0; i < OCOUNT; ++i)
        if (!strcmp(choices[i], key))
            return i;
    return -1;
}


void parse_option(const char *key, const char *value)
{
    /// Interpret custom options.
    int port;
    switch (str2const(key)) {
    case PORT:
        sscanf(value, "%d", &port);
        options.port = port;
        break;
    case PPATH:
        strcpy(options.ppath, value);
        break;
    default:
        fputs("Invalid option in config file\n", stderr);
        exit(EXIT_FAILURE);
    }
}


void load_config(const char *cpath)
{
    /// Load settings from the default or specifiend config file.

    // open the file
    FILE *fin = fopen(cpath, "r");
    if (!fin) {
        perror("Couldn't load config file");
        exit(EXIT_FAILURE);
    }

    // parse line by line
    while (!feof(fin)) {
        // prepare the items
        static char line[BLEN], key[BLEN], value[BLEN];
        // read the line
        void *ret = fgets(line, BLEN, fin);
        if (!ret)
            break;
        // skip comments and blank lines
        if (line[0] == '#' || isspace(line[0]))
            continue;
        // split into pairs and process them
        sscanf(line, "%s %s", key, value);
        parse_option(key, value);
    }

    // close it
    fclose(fin);
}


void get_packname(int clsfd, char **_packname)
{
    int packlen;
    read(clsfd, &packlen, sizeof(packlen));
    packlen = ntohl(packlen);
    char *packname = calloc(packlen + 1, sizeof(char));
    read(clsfd, packname, packlen);
    *_packname = packname;
}


void search_package(const char *packname,
                    char ***packvec, int *packcnt)
{
    /// Search for a pattern and return a list of packages.

    // package vector
    char **_packvec = *packvec = NULL;
    int _packcnt = *packcnt = 0;

    // list all files from packages path
    DIR *dirp = opendir(options.ppath);
    if (!dirp) {
        perror("Couldn't open package directory");
        return;
    }
    struct dirent *dirobj;

    while ((dirobj = readdir(dirp))) {
        char fname[BLEN];    // current file name
        strcpy(fname, dirobj->d_name);

        // some basic checks
        if (!strcmp(fname, ".") ||
            !strcmp(fname, ".."))
            continue;    // skip current and parent directory
        char *pchr = strstr(fname, PEXT);
        if (!pchr)
            continue;    // invalid package
        fname[pchr - fname] = '\0';    // strip extension
        if (!strstr(fname, packname))
            continue;    // nothing found

        // package name found, save it
        _packvec = realloc(_packvec, sizeof(char *) * ++_packcnt);
        _packvec[_packcnt - 1] = malloc(sizeof(char) *
                                        (strlen(fname) + 1));
        strcpy(_packvec[_packcnt - 1], fname);
    }

    *packvec = _packvec;
    *packcnt = _packcnt;
}


void download_package(int clsfd, const char *packname)
{
    /// Retrieve and upload a package to the client.

    // build path to file
    char fpath[BLEN];
    strcat(
        strcat(
            strcat(
                strcpy(
                    fpath,
                    options.ppath
                ),
                "/"
            ),
            packname
        ),
        PEXT
    );

    // get the size of that file
    FILE *fin = fopen(fpath, "r");
    if (!fin) {
        perror("Package doesn't exist");
        return;
    }
    fseek(fin, 0, SEEK_END);
    int fsize = ftell(fin);
    fclose(fin);

    #if DEBUG
    printf("Sending file %s (%d bytes)...\n", fpath, fsize);
    #endif

    // send the file
    int _fsize = htonl(fsize);
    write(clsfd, &_fsize, sizeof(_fsize));
    int ifd = open(fpath, O_RDONLY | O_SYNC);
    sendfile(clsfd, ifd, NULL, fsize);
    close(ifd);
}


void handle_client(int clsfd)
{
    /// Communicate with this client and process received tasks.

    // receive the task
    task_c task;
    read(clsfd, &task, sizeof(task));
    task = ntohl(task);
    // process it
    switch (task) {
    case SEARCH:
        {
            // receive package name
            char *packname;
            get_packname(clsfd, &packname);
            #if DEBUG
            printf("Searching for package %s...\n", packname);
            #endif
            // search for that package
            char **packvec;
            int packcnt;
            search_package(packname, &packvec, &packcnt);
            // send the packages (if any)
            #if DEBUG
            printf("Found %d packages\n", packcnt);
            #endif
            int _packcnt = htonl(packcnt);
            write(clsfd, &_packcnt, sizeof(_packcnt));
            for (int i = 0; i < packcnt; ++i) {
                int slen = strlen(packvec[i]);
                int _slen = htonl(slen);
                write(clsfd, &_slen, sizeof(_slen));
                write(clsfd, packvec[i], slen);
            }
            // free resources
            free(packname);
            for (int i = 0; i < packcnt; ++i)
                free(packvec[i]);
            free(packvec);
        }
        break;
    case DOWNLOAD:
        {
            char *packname;
            get_packname(clsfd, &packname);
            #if DEBUG
            printf("Uploading package %s...\n", packname);
            #endif
            download_package(clsfd, packname);
        }
        break;
    default:
        fputs("Received invalid task type\n", stderr);
    }

    close(clsfd);
}


void *threaded_handle_client(void *clsfd)
{
    handle_client((int)clsfd);
    pthread_exit(NULL);
}


void serve()
{
    /// Server core.

    // create the socket
    int svsfd = socket(AF_INET, SOCK_STREAM, 0);
    if (svsfd == -1) {
        perror("Couldn't create server socket");
        exit(EXIT_FAILURE);
    }
    // reuse address
    int op = 1;
    if (setsockopt(svsfd, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op))) {
        perror("Couldn't set socket option");
        exit(EXIT_FAILURE);
    }

    // configure it
    struct sockaddr_in svaddr;
    memset(&svaddr, 0, sizeof(svaddr));
    svaddr.sin_family = AF_INET;
    svaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    svaddr.sin_port = htons(options.port);

    // bind localhost with the desired port
    if (bind(svsfd, (struct sockaddr *) &svaddr, sizeof(svaddr)) == -1) {
        perror("Couldn't bind server socket address");
        exit(EXIT_FAILURE);
    }
    // listening queue
    if (listen(svsfd, 5) == -1) {
        perror("Couldn't listen for clients");
        exit(EXIT_FAILURE);
    }

    // client socket data
    struct sockaddr_in claddr;
    memset(&claddr, 0, sizeof(claddr));
    socklen_t clslen = sizeof(claddr);

    // accept clients, then process the work in a separate thread
    #if DEBUG
    puts("Waiting for clients...");
    #endif
    while (1) {
        int clsfd = accept(svsfd, (struct sockaddr *) &claddr, &clslen);
        if (clsfd == -1) {
            perror("Couldn't accept the client, skip");
            continue;
        }
        #if DEBUG
        printf("Accepted: %d.%d.%d.%d:%d\n",
               (int)(claddr.sin_addr.s_addr & 0xFF),
               (int)((claddr.sin_addr.s_addr & 0xFF00) >> 8),
               (int)((claddr.sin_addr.s_addr & 0xFF0000) >> 16),
               (int)((claddr.sin_addr.s_addr & 0xFF000000) >> 24),
               ntohs(claddr.sin_port));
        #endif
        #if ASYNC
        pthread_t thread;
        pthread_create(&thread, NULL,
                       threaded_handle_client, (void *)clsfd);
        #else
        handle_client(clsfd);
        #endif
    }
}


int main(int argc, const char *argv[])
{
    // parse optional positional arguments
    if (argc > 2) {
        puts("Release Management System - server");
        printf("Usage: %s [CONFIG]\n", argv[0]);
        return 1;
    }

    // load config file
    char cpath[BLEN];
    if (argc == 2)
        strcpy(cpath, argv[1]);
    else
        strcpy(cpath, CPATH);
    load_config(cpath);

    // start the server
    serve();

    return 0;
}
