#include "stdafx.h"


#define COMN 22
#define PARN 512
#define BUFL 1024
#define KEY_MAXL 128
#define VAL_MAXL 256

// necessary when using RegCopy/DeleteTree
#define WIN32_WINNT 0x0600 


char * coms[COMN] = {"dir", "cd", "mkdir", "rmdir", "touch", "del",
                     "copy", "move", "read", "write", "enum", "run",
                     "hup", "kill", "pread", "pwrite", "kenum", "kshow",
                     "kvadd", "kadd", "kcopy", "kremove"};


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

    if (!strcmp(com, "enum"))
        if (!argc || argc < 3) {
            puts("enum proc|thrd PID|modl PID");
            return -1;
        } else {
            strcpy(param1, argv[2]);
            if (!strcmp(param1, "proc"))
                return 10;
            else if (!strcmp(param1, "thrd"))
                if (argc != 4) {
                    puts("enum thrd PID");
                    return -1;
                } else {
                    strcpy(param2, argv[3]);
                    return 11;
                }
            else if (!strcmp(param1, "modl"))
                if (argc != 4) {
                    puts("enum modl PID");
                    return -1;
                } else {
                    strcpy(param2, argv[3]);
                    return 12;
                }
        }

    if (!strcmp(com, "run"))
        if (!argc || argc < 3) {
            puts("run EXE [PARAMS]");
            return -1;
        } else {
            strcpy(param1, argv[2]);
            if (argc == 4)
                strcpy(param2, argv[3]);
            else
                param2[0] = '\0';
            return 13;
        }

    if (!strcmp(com, "hup"))
        if (!argc || argc != 3) {
            puts("hup PID");
            return -1;
        } else {
            strcpy(param1, argv[2]);
            return 14;
        }

    if (!strcmp(com, "kill"))
        if (!argc || argc != 3) {
            puts("kill PID");
            return -1;
        } else {
            strcpy(param1, argv[2]);
            return 15;
        }

    if (!strcmp(com, "pread"))
        if (!argc || argc != 3) {
            puts("pread PID");
            return -1;
        } else {
            strcpy(param1, argv[2]);
            return 16;
        }

    if (!strcmp(com, "pwrite"))
        if (!argc || argc != 4) {
            puts("pwrite PID STR");
            return -1;
        } else {
            strcpy(param1, argv[2]);
            strcpy(param2, argv[3]);
            return 17;
        }

    if (!strcmp(com, "kenum"))
        if (!argc || argc != 3) {
            puts("kenum KPATH");
            return -1;
        } else {
            strcpy(param1, argv[2]);
            return 18;
        }

    if (!strcmp(com, "kshow"))
        if (!argc || argc != 4) {
            puts("kshow KPATH NAME");
            return -1;
        } else {
            strcpy(param1, argv[2]);
            strcpy(param2, argv[3]);
            return 19;
        }

    if (!strcmp(com, "kvadd"))
        if (!argc || argc != 4) {
            puts("kvadd KPATH NAME:TYPE:VALUE");
            puts("        TYPE can be 0-BINARY 1-DWORD 2-QWORD 3-SZ 4-EXPAND_SZ 5-MULTI_SZ");
            return -1;
        } else {
            strcpy(param1, argv[2]);
            strcpy(param2, argv[3]);
            return 20;
        }

    if (!strcmp(com, "kadd"))
        if (!argc || argc != 3) {
            puts("kadd KPATH");
            return -1;
        } else {
            strcpy(param1, argv[2]);
            return 21;
        }

    if (!strcmp(com, "kcopy"))
        if (!argc || argc != 4) {
            puts("kcopy KSRC KDEST");
            return -1;
        } else {
            strcpy(param1, argv[2]);
            strcpy(param2, argv[3]);
            return 22;
        }

    if (!strcmp(com, "kremove"))
        if (!argc || argc != 3) {
            puts("kcopy KPATH");
            return -1;
        } else {
            strcpy(param1, argv[2]);
            return 23;
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
        printf("Error %d: invalid directory\n",
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
        printf("Error %d: invalid directory\n",
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
        printf("Error %d: couldn't delete\n");
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
        printf("Error %d: couldn't open\n", GetLastError());
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
        printf("Error %d: couldn't open file\n", GetLastError());
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


void _enum(char * param)
{
    PROCESSENTRY32 data;
    HANDLE hSnap;
    data.dwSize = sizeof(PROCESSENTRY32);

    hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    Process32First(hSnap, &data);

    do {
        printf("%s %d\n", data.szExeFile, data.th32ProcessID);
    } while (Process32Next(hSnap, &data));
    CloseHandle(hSnap);
}


void _enum_thrd(char * param1, char * param2,
                int ** vec, int * len)
{
    if (vec) {
        *vec = NULL;
        *len = 0;
    }

    int pid;
    sscanf(param2, "%d", &pid);
    //printf("pid: %d\n", pid);

    THREADENTRY32 data;
    HANDLE hSnap;
    data.dwSize = sizeof(THREADENTRY32);

    hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    Thread32First(hSnap, &data);

    do {
        if (data.th32OwnerProcessID != pid)
            continue;
        if (vec) {
            (*vec) = (int *)realloc(*vec, sizeof(int) * ++(*len));
            (*vec)[*len - 1] = data.th32ThreadID;
        } else
            printf("%d\n", data.th32ThreadID);
    } while (Thread32Next(hSnap, &data));
    CloseHandle(hSnap);
}


void _enum_modl(char * param1, char * param2)
{
    int pid;
    sscanf(param2, "%d", &pid);

    MODULEENTRY32 data;
    HANDLE hSnap;
    data.dwSize = sizeof(MODULEENTRY32);

    hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    Module32First(hSnap, &data);

    do {
        if (data.th32ProcessID != pid)
            continue;
        printf("%s\n", data.szModule);
    } while (Module32Next(hSnap, &data));

    CloseHandle(hSnap);
}


void _run(char * param1, char * param2)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);

    char paramCat[2 * PARN];
    strcpy(paramCat, param1);
    strcat(paramCat, " ");
    strcat(paramCat, param2);
    //printf("CAT: %s\n", paramCat);
    //return;

    BOOL rc = CreateProcess(NULL, paramCat, NULL, NULL, FALSE, 0,
                            NULL, NULL, &si, &pi);
    if (!rc) {
        printf("Error %d: create process failed\n",
               GetLastError());
        return;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}


void _hup(char * param)
{
    int * tids, len;
    _enum_thrd(NULL, param, &tids, &len);

    for (int i = 0; i < len; ++i) {
        HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE,
                                    tids[i]);
        SuspendThread(hThread);
        CloseHandle(hThread);
    }

    free(tids);
}


void _kill(char * param)
{
    int * tids, len;
    _enum_thrd(NULL, param, &tids, &len);

    for (int i = 0; i < len; ++i) {
        HANDLE hThread = OpenThread(THREAD_TERMINATE, FALSE,
                                    tids[i]);
        TerminateThread(hThread, 0);
        CloseHandle(hThread);
    }

    free(tids);
}


void _pread(char * param)
{
    int pid;
    sscanf(param, "%d", &pid);

    HANDLE hProc = OpenProcess(PROCESS_VM_READ, FALSE, pid);

    if (hProc == INVALID_HANDLE_VALUE) {
        printf("Error %d: couldn't open process\n", GetLastError());
        return;
    }

    MODULEENTRY32 data;
    HANDLE hSnap;
    data.dwSize = sizeof(MODULEENTRY32);

    hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    Module32First(hSnap, &data);

    char buffer[BUFL];
    int toRead = BUFL;
    int readed;
    ReadProcessMemory(hProc, data.modBaseAddr, buffer, toRead, (SIZE_T *)&readed);
    
    for (int i = 0; i < readed; ++i)
        printf("%c", buffer[i]);
    putchar('\n');

    CloseHandle(hSnap);
    CloseHandle(hProc);
}


void _pwrite(char * param1, char * param2)
{
    int pid;
    sscanf(param1, "%d", &pid);

    HANDLE hProc = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pid);

    if (hProc == INVALID_HANDLE_VALUE) {
        printf("Error %d: couldn't open process\n", GetLastError());
        return;
    }

    MODULEENTRY32 data;
    HANDLE hSnap;
    data.dwSize = sizeof(MODULEENTRY32);

    hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    Module32First(hSnap, &data);

    char * buffer = param2;
    int toWrite = strlen(param2);
    int written;
    BOOL rc;
    DWORD oldAcc;
    rc = VirtualProtectEx(hProc, data.modBaseAddr, toWrite, PAGE_READWRITE, &oldAcc);
    if (!rc) {
        printf("Error %d: VirtualProtectEx fail\n", GetLastError());
        return;
    }
    rc = WriteProcessMemory(hProc, data.modBaseAddr, buffer, toWrite, (SIZE_T *)&written);
    if (rc)
        puts("Written");
    else
        puts("Couldn't write");

    CloseHandle(hSnap);
    CloseHandle(hProc);
}


HKEY str2key(char * src)
{  
    if (!strcmp(src, "HKEY_CLASSES"))
        return HKEY_CLASSES_ROOT;
    if (!strcmp(src, "HKEY_CURRENT_CONFIG"))
        return HKEY_CURRENT_CONFIG;
    if (!strcmp(src, "HKEY_CURRENT_USER"))
        return HKEY_CURRENT_USER;
    if (!strcmp(src, "HKEY_LOCAL_MACHINE"))
        return HKEY_LOCAL_MACHINE;
    if (!strcmp(src, "HKEY_PERFORMANCE_DATA"))
        return HKEY_PERFORMANCE_DATA;
    if (!strcmp(src, "HKEY_USERS"))
        return HKEY_USERS;
    return NULL;
}


void param_parse(char * param, char * root,
                 char * rest)
{
    root[0] = rest[0] = '\0';
    char * pch = strchr(param, '\\');
    if (!pch)
        pch = param + strlen(param);
    strncpy(root, param, pch - param);
    root[pch - param] = '\0';
    if (*pch)
        strcpy(rest, pch + 1);
}


void _kenum(char * param)
{
    // parse param
    char root[KEY_MAXL], rest[KEY_MAXL];
    param_parse(param, root, rest);
    //printf("%s - %s\n", root, rest);

    HKEY hkroot = str2key(root);
    HKEY hKey;
    int rc;

    // try to open the key
    rc = RegOpenKeyEx(hkroot, rest, 0, KEY_READ, &hKey);
    if (rc != ERROR_SUCCESS) {
        printf("Error %d: couldn't open key\n", rc);
        return;
    }

    char buffer[KEY_MAXL];
    int ind = 0;
    int toRead;

    puts("Keys...");
    while (1) {
        toRead = KEY_MAXL;
        rc = RegEnumKeyEx(hKey, ind, buffer, (LPDWORD)&toRead, NULL,
                          NULL, NULL, NULL);
        if (rc != ERROR_SUCCESS)
            break;
        ind += 1;
        printf("%s\n", buffer);
    }
    //RegCloseKey(hKey);

    // do the same for values
    //RegOpenKeyEx(hkroot, rest, 0, KEY_READ, &hKey);
    puts("Values...");
    ind = 0;
    while (1) {
        toRead = KEY_MAXL;
        rc = RegEnumValue(hKey, ind, buffer, (LPDWORD)&toRead, NULL,
                          NULL, NULL, NULL);
        if (rc == ERROR_NO_MORE_ITEMS)
            break;
        ind += 1;
        printf("%s\n", buffer);
    }
    RegCloseKey(hKey);
}


void _show_value(char * param1, char * param2)
{
    char root[KEY_MAXL], rest[KEY_MAXL];
    param_parse(param1, root, rest);

    // get value type and data
    unsigned char valBuffer[VAL_MAXL];
    memset(valBuffer, 0, sizeof(valBuffer));
    int valLen, valType;
    int rc = RegGetValue(str2key(root), rest, param2, RRF_RT_ANY,
                         (LPDWORD)&valType, valBuffer, (LPDWORD)&valLen);
    if (rc != ERROR_SUCCESS) {
        printf("Error %d: couldn't retrieve value\n", rc);
        return;
    }
    if (valType == REG_DWORD) {
        unsigned int tmp;
        __asm {
            xor eax, eax
            lea ebx, valBuffer
            mov eax, dword ptr [ebx]
            mov tmp, eax
        }
        printf("%u\n", tmp);
    } else if (valType == REG_QWORD) {
        unsigned long long tmp = 0;
        __asm {
            lea ebx, valBuffer
            lea edx, tmp

            mov eax, dword ptr [ebx]
            mov dword ptr [edx], eax

            mov eax, dword ptr [ebx+4]
            mov dword ptr [edx+4], eax
        }
        printf("%I64u\n", tmp);
    } else if (valType == REG_BINARY || valType == REG_SZ ||
               valType == REG_EXPAND_SZ) {
        printf("%s\n", valBuffer);
    } else if (valType == REG_MULTI_SZ) {
        /*printf("%u %u %u %u %u\n", valBuffer[0], valBuffer[1], valBuffer[2],
                                   valBuffer[3], valBuffer[4]);*/
        // we must print each NULL terminated string
        char * pch = (char *)valBuffer - 1;
        //printf("valBuffer: %x\n", (unsigned int)valBuffer);
        //printf("valLen: %u\n", valLen);
        do {
            ++pch;

            // check if we are outside the buffer
            if (pch - (char *)valBuffer >= valLen || *pch == '\0')
                break;

            //printf("pch: %x\n", (unsigned int)pch);
            printf("%s\n", pch);
        } while ((pch = strchr(pch, '\0')));
    } else {
        puts("Unsupported type");
    }
}


void parse_value(char * param, char * name, unsigned int * type,
                 unsigned char * value, unsigned int * valueSize)
{
    // fill value buffer with zeros
    memset(value, 0, *valueSize);

    // get positions of separators
    char * lo, * hi;
    lo = strchr(param, ':');
    hi = strchr(lo + 1, ':');

    // retrieve value name
    strncpy(name, param, lo - param);
    name[lo - param] = '\0';

    // now interpret the value type
    char typeStr[2];
    strncpy(typeStr, lo + 1, hi - lo - 1);
    typeStr[hi - lo - 1] = '\0';
    unsigned short typeInt;
    //fprintf(stderr, "%x %x\n", typeStr[0], typeStr[1]);
    sscanf(typeStr, "%hu", &typeInt);
    switch (typeInt) {
    case 0:
        *type = REG_BINARY;
        break;
    case 1:
        *type = REG_DWORD;
        break;
    case 2:
        *type = REG_QWORD;
        break;
    case 3:
        *type = REG_SZ;
        break;
    case 4:
        *type = REG_EXPAND_SZ;
        break;
    case 5:
        *type = REG_MULTI_SZ;
        break;
    default:
        printf("Error: invalid value type\n");
        return;
    }

    // finally get the raw data
    char tmp[VAL_MAXL];
    strcpy(tmp, hi + 1);
    unsigned int tmpLen = strlen(tmp);

    switch (*type) {
    case REG_DWORD:
        unsigned int valueInt;
        sscanf(tmp, "%u", &valueInt);
        __asm {
            mov ebx, value
            mov eax, valueInt
            mov dword ptr [ebx], eax
        }
        *valueSize = 4;
        break;
    case REG_QWORD:
        unsigned long long valueLong;
        sscanf(tmp, "%I64u", &valueLong);
        __asm {
            mov ebx, value
            lea edx, valueLong

            mov eax, dword ptr [edx]
            mov dword ptr [ebx], eax

            mov eax, dword ptr [edx+4]
            mov dword ptr [ebx+4], eax
        }
        *valueSize = 8;
        break;
    case REG_BINARY:
    case REG_SZ:
    case REG_EXPAND_SZ:
        strncpy((char *)value, tmp, *valueSize);
        if (tmpLen < *valueSize)
            *valueSize = tmpLen + 1;
        break;
    case REG_MULTI_SZ:
        strncpy((char *)value, tmp, *valueSize);
        // replace spaces with nulls
        char * pch = strchr((char *)value, ' ');
        while (pch) {
            *pch = '\0';
            pch = strchr(pch + 1, ' ');
        }
        if (tmpLen < *valueSize)
            *valueSize = tmpLen + 2;    /* must end in two nulls,
                                           one for the last string and one for
                                           marking the end of the list */
        break;
    }
}


void _add_value(char * param1, char * param2)
{
    char valueName[32];
    unsigned int valueType = -1;
    unsigned char valueBuffer[VAL_MAXL];
    unsigned int valueSize = VAL_MAXL;
    // fill the data above
    parse_value(param2, valueName, &valueType, valueBuffer, &valueSize);
    
    // now write processed data to the registries
    char root[KEY_MAXL], rest[KEY_MAXL];
    param_parse(param1, root, rest);

    HKEY hkroot = str2key(root);
    HKEY hKey;
    int rc;

    // try to open the key
    rc = RegOpenKeyEx(hkroot, rest, 0, KEY_SET_VALUE, &hKey);
    if (rc != ERROR_SUCCESS) {
        printf("Error %d: couldn't open key for setting values\n", rc);
        return;
    }

    rc = RegSetValueEx(hKey, valueName, 0, valueType, valueBuffer, valueSize);
    if (rc != ERROR_SUCCESS) {
        printf("Error %d: couldn't set value\n", rc);
        return;
    }

    // al fine :]
    RegCloseKey(hKey);
}


void _add_key(char * param)
{
    char root[KEY_MAXL], rest[KEY_MAXL];
    param_parse(param, root, rest);
    HKEY hKey;

    int rc = RegCreateKeyEx(str2key(root), rest, 0, NULL, REG_OPTION_NON_VOLATILE,
                        KEY_ALL_ACCESS, NULL, &hKey, NULL);
    if (rc != ERROR_SUCCESS) {
        printf("Error %d: couldn't create key\n", rc);
        return;
    }

    RegCloseKey(hKey);
}


void _copy_key(char * param1, char * param2)
{
    char root[KEY_MAXL], rest[KEY_MAXL];
    HKEY hKeySrc, hKeyDest;
    int rc;

    param_parse(param1, root, rest);
    rc = RegOpenKeyEx(str2key(root), rest, 0, KEY_READ, &hKeySrc);
    if (rc != ERROR_SUCCESS) {
        printf("Error %d: couldn't open source key for reading\n", rc);
        return;
    }

    param_parse(param2, root, rest);
    rc = RegOpenKeyEx(str2key(root), rest, 0, KEY_ALL_ACCESS, &hKeyDest);
    if (rc != ERROR_SUCCESS) {
        printf("Error %d: couldn't open destination key for writting\n", rc);
        return;
    }

    // now that all the keys are openned, try to copy recursively
    rc = RegCopyTree(hKeySrc, NULL, hKeyDest);
    if (rc != ERROR_SUCCESS) {
        printf("Error %d: couldn't copy key tree\n");
        return;
    }
    
    RegCloseKey(hKeySrc);
    RegCloseKey(hKeyDest);
}


void parse_rest(char * rest, char * baseRest, char * subkey)
{
    char * pch, * last;
    pch = strchr(rest, '\\');

    if (!pch) {
        baseRest[0] = '\0';
        strcpy(subkey, rest);
        return;
    }

    while (pch) {
        last = pch;
        pch = strchr(pch + 1, '\\');
    }

    strncpy(baseRest, rest, last - rest);
    baseRest[last - rest] = '\0';
    strcpy(subkey, last + 1);
}


void _remove_key(char * param)
{
    char root[KEY_MAXL], rest[KEY_MAXL];
    HKEY hKey;
    int rc;

    param_parse(param, root, rest);
    rc = RegOpenKeyEx(str2key(root), rest, 0, KEY_ALL_ACCESS, &hKey);
    if (rc != ERROR_SUCCESS) {
        printf("Error %d: couldn't open key for deleting\n", rc);
        return;
    }

    rc = RegDeleteTree(hKey, NULL);
    if (rc != ERROR_SUCCESS) {
        printf("Error %d: couldn't delete key and its contents", rc);
        return;
    }

    RegCloseKey(hKey);

    // and now open the parent key and delete this subkey
    // remove last level of the tree
    char baseRest[KEY_MAXL], subkey[KEY_MAXL];
    parse_rest(rest, baseRest, subkey);
    //fprintf(stderr, "%s - %s", baseRest, subkey);
    char * _baseRest;
    if (strlen(baseRest))
        _baseRest = baseRest;
    else
        _baseRest = NULL;
    rc = RegOpenKeyEx(str2key(root), _baseRest, 0, KEY_ALL_ACCESS, &hKey);
    if (rc != ERROR_SUCCESS) {
        printf("Error %d: couldn't open base tree to delete subkey\n");
        return;
    }

    // delete specified subkey
    rc = RegDeleteKeyEx(hKey, subkey, KEY_WOW64_32KEY, 0);
    if (rc != ERROR_SUCCESS) {
        printf("Error %: couldn't delete subkey of opened basekey\n");
        return;
    }

    RegCloseKey(hKey);
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
    else if (rc == 10)
        _enum(param1);
    else if (rc == 11)
        _enum_thrd(param1, param2, NULL, NULL);
    else if (rc == 12)
        _enum_modl(param1, param2);
    else if (rc == 13)
        _run(param1, param2);
    else if (rc == 14)
        _hup(param1);
    else if (rc == 15)
        _kill(param1);
    else if (rc == 16)
        _pread(param1);
    else if (rc == 17)
        _pwrite(param1, param2);
    else if (rc == 18)
        _kenum(param1);
    else if (rc == 19)
        _show_value(param1, param2);
    else if (rc == 20)
        _add_value(param1, param2);
    else if (rc == 21)
        _add_key(param1);
    else if (rc == 22)
        _copy_key(param1, param2);
    else if (rc == 23)
        _remove_key(param1);
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
