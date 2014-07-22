#include "stdafx.h"


#define COMN 10
#define PARN 128
#define BUFL 1024


char * coms[COMN] = {"dir", "cd", "mkdir", "rmdir", "touch", "del",
                     "copy", "move", "read", "write"};


char * _read(LPCSTR);
void _write(LPCSTR, char *);


int help(char * com, int argc, char ** argv,
         char * param1, char * param2)
{
    if (!strcmp(com, "dir"))
        if (!argc || argc > 3) {
            puts("dir [DIR]");
            return -1;
        } else {
            if (argc == 3) {
                strcpy(param1, argv[2]);
                strcat(param1, "\\*");
            } else
                strcpy(param1, "*");
            return 0;
        }

    if (!strcmp(com, "cd"))
        if (!argc || argc != 3) {
            puts("cd DIR");
            return -1;
        } else {
            strcpy(param1, argv[2]);
            return 1;
        }
    
    if (!strcmp(com, "mkdir"))
        if (!argc || argc != 3) {
            puts("mkdir DIR");
            return -1;
        } else {
            strcpy(param1, argv[2]);
            return 2;
        }

    if (!strcmp(com, "rmdir"))
        if (!argc || argc != 3) {
            puts("rmdir DIR");
            return -1;
        } else {
            strcpy(param1, argv[2]);
            return 3;
        }

    if (!strcmp(com, "touch"))
        if (!argc || argc != 3) {
            puts("touch FILE");
            return -1;
        } else {
            strcpy(param1, argv[2]);
            return 4;
        }

    if (!strcmp(com, "del"))
        if (!argc || argc != 3) {
            puts("del FILE");
            return -1;
        } else {
            strcpy(param1, argv[2]);
            return 5;
        }

    if (!strcmp(com, "copy"))
        if (!argc || argc != 4) {
            puts("copy SRC DEST");
            return -1;
        } else {
            strcpy(param1, argv[2]);
            strcpy(param2, argv[3]);
            return 6;
        }

    if (!strcmp(com, "move"))
        if (!argc || argc != 4) {
            puts("move SRC DEST");
            return -1;
        } else {
            strcpy(param1, argv[2]);
            strcpy(param2, argv[3]);
            return 7;
        }

    if (!strcmp(com, "read"))
        if (!argc || argc != 3) {
            puts("read FILE");
            return -1;
        } else {
            strcpy(param1, argv[2]);
            return 8;
        }

    if (!strcmp(com, "write"))
        if (!argc || argc != 4) {
            puts("write FILE STR");
            return -1;
        } else {
            strcpy(param1, argv[2]);
            strcpy(param2, argv[3]);
            return 9;
        }

    puts("Invalid command");
    return -1;
}


void _dir(LPCSTR param)
{
    WIN32_FIND_DATA fileData;
    HANDLE lastFile;

    lastFile = FindFirstFile(param, &fileData);
    if (lastFile == INVALID_HANDLE_VALUE ||
        !(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
        printf("Error %d: invalid directory",
                GetLastError());
        return;
    }
    
    do {
        printf("%s\n", fileData.cFileName);
    } while (FindNextFile(lastFile, &fileData));
    FindClose(lastFile);
}


void _cd(LPCSTR param)
{
    if (!SetCurrentDirectory(param))
        printf("Failed %d", GetLastError());
}


void _mkdir(LPCSTR param)
{
    BOOL ret = CreateDirectory(param, NULL);
    if (!ret)
        printf("Error %d: couldn't create directory\n",
                GetLastError());
}



void _rmdir(LPCSTR param)
{
    WIN32_FIND_DATA fileData;
    HANDLE lastFile;

    char * _param = (char *)malloc(sizeof(char) * (strlen(param) + 3));
    strcpy(_param, param);
    strcat(_param, "\\*");
    lastFile = FindFirstFile(_param, &fileData);
    free(_param);

    if (lastFile == INVALID_HANDLE_VALUE ||
        !(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
        printf("Error %d: invalid directory",
                GetLastError());
        return;
    }
    
    do {
        char start[2];
        strncpy(start, fileData.cFileName, 2);
        if (start[0] == '.')
            continue;    // 
        if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            int length = strlen(param) + strlen(fileData.cFileName) + 2;
            char * newPath = (char *)malloc(sizeof(char) * length);
            strcpy(newPath, param);
            strcat(newPath, "\\");
            strcat(newPath, fileData.cFileName);
            _rmdir(newPath);
            free(newPath);
        } else
            DeleteFile(param);
    } while (FindNextFile(lastFile, &fileData));

    FindClose(lastFile);
    RemoveDirectory(param);
}


void _touch(LPCSTR param)
{
    HANDLE fileHandle;
    fileHandle = CreateFile(param, GENERIC_WRITE, 0,
        NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        printf("Error %d: couldn't oepn file\n");
        return;
    }
    CloseHandle(fileHandle);
}



void _del(LPCSTR param)
{
    if (!DeleteFile(param))
        printf("Error %d: couldn't delete");
}


void _copy(LPCSTR param1, LPCSTR param2)
{
    char * ret = _read(param1);
    _write(param2, ret);
    free(ret);
}


void _move(LPCSTR param1, LPCSTR param2)
{
    _copy(param1, param2);
    _del(param1);
}


char * _read(LPCSTR param)
{
    char buffer[BUFL];
    int readSize = BUFL;
    char * total = NULL;
    int totalSize = 0;

    HANDLE fileHandle;
    fileHandle = CreateFile(param, GENERIC_READ, FILE_SHARE_READ,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (fileHandle == INVALID_HANDLE_VALUE) {
        printf("Error %d: couldn't open", GetLastError());
        return NULL;
    }

    while (1) {
        BOOL rc = ReadFile(fileHandle, &buffer, readSize,
            (LPDWORD)&readSize, NULL);

        total = (char *)realloc(total, sizeof(char) *\
            (totalSize + readSize));
        for (int i = totalSize; i < totalSize + readSize; ++i)
            total[i] = buffer[i - totalSize];
        totalSize += readSize;

        if (rc && !readSize)
            break;
    }

    total = (char *)realloc(total, sizeof(char) * (totalSize + 1));
    total[totalSize] = '\0';
    CloseHandle(fileHandle);
    return total;
}


int _min(int a, int b)
{
    if (b < a)
        return b;
    return a;
}


void _write(LPCSTR param, char * toWrite)
{
    HANDLE fileHandle;
    fileHandle = CreateFile(param, GENERIC_WRITE, 0, NULL,
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        printf("Error %d: couldn't open file", GetLastError());
        return;
    }

    int total = strlen(toWrite);
    int start = 0;

    BOOL rc;
    do {
        int written;
        rc = WriteFile(fileHandle, toWrite + start, _min(total - start, BUFL),
                       (LPDWORD)&written, NULL);
        if (written < BUFL)
            break;
    } while (rc);

    CloseHandle(fileHandle);
}


void process(char * com, int argc, char ** argv)
{
    char param1[PARN], param2[PARN];
    int rc = help(com, argc, argv, param1, param2);
    if (rc == -1)
        return;

    if (rc == 0)
        _dir(param1);
    else if (rc == 1)
        _cd(param1);
    else if (rc == 2)
        _mkdir(param1);
    else if (rc == 3)
        _rmdir(param1);
    else if (rc == 4)
        _touch(param1);
    else if (rc == 5)
        _del(param1);
    else if (rc == 6)
        _copy(param1, param2);
    else if (rc == 7)
        _move(param1, param2);
    else if (rc == 8) {
        char * ret = _read(param1);
        if (ret) {
            printf("%s\n", ret);
            free(ret);
        }
    } else if (rc == 9)
        _write(param1, param2);
}


int main(int argc, char * argv[])
{
    if (argc < 2) {
        printf("Usage: %s COMMAND [PARAM]...\n\n", argv[0]);
        puts("Commands:");
        for (int i = 0; i < COMN; ++i) {
            fputs("    ", stdout);
            help(coms[i], 0, NULL, NULL, NULL);
        }
        return 0;
    }

    process(argv[1], argc, argv);
	return 0;
}
