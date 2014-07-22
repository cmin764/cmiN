#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <string.h>

#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <string>

using namespace std;


const int PIDL = 16;
const int EXEL = 256;
const char * ROOT = "C:\\Users\\cmiN\\Desktop\\procese";
const int DELAY = 1000;


typedef unsigned int ui_t;

typedef pair<string, ui_t> psu_t;    // (dllName, addr)
typedef vector<psu_t> vp_t;         // ((dllName, addr), ...)
typedef pair<string, vp_t> psv_t;    // (exeName, ((dllName, addr), ...))
typedef map<int, psv_t> mip_t;        // ((pid, (exeName, ((dllName, addr), ...))), ...)


void fill(mip_t & procs)
{
    // fill procs with details of all processes
    HANDLE hSnap;
    PROCESSENTRY32 data;

    data.dwSize = sizeof(PROCESSENTRY32);
    hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap == INVALID_HANDLE_VALUE) {
        printf("Error %d: couldn't create snaphot\n", GetLastError());
        return;
    }

    if (!Process32First(hSnap, &data)) {
        printf("Error %d: couldn't find first process\n", GetLastError());
        return;
    }

    // ok
    do {
        int pid = data.th32ProcessID;
        if (pid == 0)
            continue;
        string name(data.szExeFile);
        vp_t modules;

        // load kernel modules
        HANDLE _hSnap;
        MODULEENTRY32 _data;
        _data.dwSize = sizeof(MODULEENTRY32);
        _hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
        if (!Module32First(_hSnap, &_data)) {
            //printf("Error %d: couldn't find module\n", GetLastError());
            continue;
        }
        // first module found
        Module32Next(_hSnap, &_data);
        do {
            psu_t pair;
            pair.first = _data.szModule;
            pair.second = (ui_t)_data.modBaseAddr;
            modules.push_back(pair);
        } while(Module32Next(_hSnap, &_data));
        CloseHandle(_hSnap);

        psv_t pair;
        pair.first = name;
        pair.second.assign(modules.begin(), modules.end());
        procs[pid] = pair;
    } while (Process32Next(hSnap, &data));

    CloseHandle(hSnap);
}


inline void create_folder(string dir)
{
    string absPath(ROOT);
    absPath.append("\\" + dir);
    CreateDirectory(absPath.c_str(), NULL);
}


inline void create_file(string dirName, string fname, int addr)
{
    string absPath(ROOT);
    absPath.append("\\" + dirName + "\\" + fname);
    HANDLE hFile = CreateFile(absPath.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL, NULL);
    int written;
    char addrStr[32];
    sprintf(addrStr, "%d", addr);
    WriteFile(hFile, addrStr, strlen(addrStr), (LPDWORD)&written, NULL);
    CloseHandle(hFile);
}


void build(const mip_t & procs)
{
    for (mip_t::const_iterator it = procs.begin(); it != procs.end(); ++it) {
        char tmp[PIDL];
        sprintf(tmp, "%d", it->first);
        string dirName(tmp);
        dirName.append("_" + (it->second).first);
        create_folder(dirName);

        for (vp_t::const_iterator vit = (it->second).second.begin();
             vit != (it->second).second.end(); ++vit) {
                string fname = vit->first;
                int addr = vit->second;
                create_file(dirName, fname, addr);
        }
    }
}


void remove(const mip_t& procs)
{
    for (mip_t::const_iterator it = procs.begin();
         it != procs.end(); ++it) {
        string path(ROOT);
        char pid[PIDL];
        sprintf(pid, "%d", it->first);
        path.append("\\" + string(pid) + "_" + (it->second).first);

        WIN32_FIND_DATA findData;
        HANDLE findHandle;

        findHandle = FindFirstFile((path + "\\*").c_str(), &findData);
        if (findHandle != INVALID_HANDLE_VALUE) {
            // there are files to delete
            do {
                DeleteFile((path + "\\" + string(findData.cFileName)).c_str());
            } while (FindNextFile(findHandle, &findData));
        }
        FindClose(findHandle);

        RemoveDirectory(path.c_str());
    }
}


void diff_make(const mip_t & procs, const mip_t & _procs,
               mip_t & toMake)
{
    for (mip_t::const_iterator it = _procs.begin();
         it != _procs.end(); ++it)
        if (procs.count(it->first) == 0)
            toMake.insert(*it);
}


void diff_del(const mip_t & procs, const mip_t & _procs,
               mip_t & toDel)
{
    for (mip_t::const_iterator it = procs.begin();
         it != procs.end(); ++it)
        if (_procs.count(it->first) == 0)
            toDel.insert(*it);
}


void show(const mip_t & dict)
{
    /// For testing purposes.
    for (mip_t::const_iterator it = dict.begin();
         it != dict.end(); ++it)
        cout << it->first << endl;
}


int get_pid(string path)
{
    HANDLE fin = CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ,
                            NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
                            NULL);
    if (fin == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error %d: couldn't open start file", GetLastError());
        return -1;
    }

    char buffer[PIDL];
    int read = -1, pid = -1;
    if (ReadFile(fin, buffer, PIDL - 1, (LPDWORD)&read, NULL)) {
        buffer[read] = '\0';
        sscanf(buffer, "%d", &pid);
    } else
        fprintf(stderr, "Error %d: couldn't read start file", GetLastError());
    CloseHandle(fin);
    return pid;
}


string get_ename(string path)
{
    HANDLE fin = CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ,
                            NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
                            NULL);
    if (fin == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error %d: couldn't open kill file", GetLastError());
        return "";
    }

    char buffer[EXEL];
    int read = -1;
    string exeName;
    if (ReadFile(fin, buffer, EXEL - 1, (LPDWORD)&read, NULL)) {
        buffer[read] = '\0';
        sscanf(buffer, "%s", &buffer);
        exeName.assign(buffer);
    } else
        fprintf(stderr, "Error %d: couldn't read kill file", GetLastError());
    CloseHandle(fin);
    return exeName;
}


void start(string path)
{
    STARTUPINFO sInfo;
    PROCESS_INFORMATION pInfo;

    ZeroMemory(&sInfo, sizeof(sInfo));
    ZeroMemory(&pInfo, sizeof(pInfo));
    sInfo.cb = sizeof(sInfo);

    if (!CreateProcess(NULL, (LPSTR)path.c_str(), NULL, NULL, FALSE, 0,
                      NULL, NULL, &sInfo, &pInfo)) {
       fprintf(stderr, "Error %d: create process failed", GetLastError());
       return;
    }

    CloseHandle(pInfo.hProcess);
    CloseHandle(pInfo.hThread);
}


void kill(int pid)
{
    THREADENTRY32 threadData;
    HANDLE snapHandle;

    threadData.dwSize = sizeof(THREADENTRY32);
    snapHandle = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    Thread32First(snapHandle, &threadData);

    do {
        if (threadData.th32OwnerProcessID != pid)
            continue;
        // thread from process, kill it
        HANDLE threadHandle = OpenThread(THREAD_TERMINATE, FALSE,
                                         threadData.th32ThreadID);
        TerminateThread(threadHandle, 0);
        CloseHandle(threadHandle);
    } while (Thread32Next(snapHandle, &threadData));
    CloseHandle(snapHandle);
}


void check_sk()
{
    string path(ROOT);

    WIN32_FIND_DATA findData;
    HANDLE findHandle;
    bool sFound = false, kFound = false;

    findHandle = FindFirstFile((path + "\\*").c_str(), &findData);
    do {
        if (!strcmp(findData.cFileName, "start")) {
            sFound = true;
            string exeName = get_ename(path + "\\" + "start");
            if (exeName.size())
                start(exeName);
        }
        if (!strcmp(findData.cFileName, "kill")) {
            kFound = true;
            int pid = get_pid(path + "\\" + "kill");
            if (pid != -1)
                kill(pid);
        }
        if (sFound && kFound)
            break;    // nothing to search for
    } while (FindNextFile(findHandle, &findData));

    if (sFound)
        DeleteFile((path + "\\start").c_str());
    if (kFound)
        DeleteFile((path + "\\kill").c_str());
}


void watcher()
{
    // initial snapshot
    mip_t procs;
    fill(procs);
    build(procs);

    while (1) {
        // check for start and kill file
        check_sk();

        // view differences
        mip_t _procs, toMake, toDel;
        fill(_procs);
        diff_make(procs, _procs, toMake);
        diff_del(procs, _procs, toDel);

        /*cout << "Create..." << endl;
        show(toMake);
        cout << "Delete..." << endl;
        show(toDel);*/
        build(toMake);
        remove(toDel);

        // update old procs
        procs.swap(_procs);

        //cout << "Dorm..." << endl;
        Sleep(DELAY);
    }
}


int main(int argc, char * argv[])
{
    watcher();
	return 0;
}
