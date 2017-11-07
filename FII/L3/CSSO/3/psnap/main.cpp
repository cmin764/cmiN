#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <windows.h>
#include <tlhelp32.h>

#define BUFF 64
#define MAX_SIZE 1 << 13
#define FNAME "psnap.txt"


using namespace std;


struct ProcMap {
    int pid;
    string name;
    vector<ProcMap> sons;

    ProcMap() : pid(-1), name("") {}
};

typedef map<unsigned int, pair<unsigned int, string> > procs_t;


int exec_snap()
{
    /* Enumeram toate procesele si salvam detalii despre ele intr-un
    fisier mapat in memorie.
    */
    // Facem snapshot.
    HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hsnap == INVALID_HANDLE_VALUE) {
        cerr << "Snapshot failed: " << GetLastError() << endl;
        return 2;
    }
    // Initializez dwSize cu dimensiunea structurii.
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    // Obtinem informatii despre primul proces listat.
    if(!Process32First(hsnap, &pe32)) {
        cerr << "Process first enum failed: " << GetLastError() << endl;
        CloseHandle(hsnap);
        return 2;
    }

    // Deschidem fisierul mapat in memorie.
    HANDLE hfile = CreateFileMapping(NULL, NULL, PAGE_READWRITE,
                                     0, MAX_SIZE, FNAME);
    char *file_addr = (char *)MapViewOfFile(hfile, FILE_MAP_WRITE, 0, 0, 0);
    if (!file_addr) {
        cerr << "Couldn't map file: " << GetLastError() << endl;
        CloseHandle(hfile);
        CloseHandle(hsnap);
        return 3;
    }

    // Afisam toate procesele enumerate.
    file_addr[0] = '\0';
    do {
        cout << pe32.th32ProcessID << " " << pe32.th32ParentProcessID << " "
             << pe32.szExeFile << endl;
        char buffer[BUFF];
        sprintf(buffer, "%u %u %s\n",
                (unsigned int)pe32.th32ProcessID,
                (unsigned int)pe32.th32ParentProcessID,
                (const char *)pe32.szExeFile);
        strcat(file_addr, buffer);
    } while(Process32Next(hsnap, &pe32));
    CloseHandle(hsnap);

    cout << "Press enter to end execution..." << endl;
    cin.get();
    UnmapViewOfFile(file_addr);
    CloseHandle(hfile);

    return 0;    // totul in regula
}


ProcMap get_ptree()
{
    ProcMap ptree;
    procs_t procs;

    HANDLE hfile = OpenFileMapping(FILE_MAP_WRITE, FALSE, FNAME);
    const char *file_addr = (const char *)MapViewOfFile(hfile, FILE_MAP_WRITE, 0, 0, 0);
    if (!file_addr) {
        cerr << "Couldn't map file: " << GetLastError() << endl;
        CloseHandle(hfile);
        return ptree;
    }
    /* Citeste toate liniile din fisierul de comunicare si salveaza procesele
     intr-o structura. */
    //cout << file_addr << endl;
    istringstream sio(file_addr);
    while (sio.good()) {
        unsigned int pid, ppid;
        string name;
        sio >> pid >> ppid >> name;
        if (sio.eof() || sio.fail()) break;
        procs[pid] = make_pair(ppid, name);
    }
    UnmapViewOfFile(file_addr);
    CloseHandle(hfile);

    for (auto it = procs.cbegin(); it != procs.cend(); ++it)
        cout << it->first << " " << "(" << it->second.first << ", "
             << it->second.second << ") " << endl;

    ptree.pid = 0;
    return ptree;
}


int exec_tree()
{
    ProcMap ptree = get_ptree();
    if (ptree.pid == -1) {
        cerr << "Something went wrong while getting process tree." << endl;
        return 3;
    }
    return 0;
}


int execute(const char *cmd)
{
    int rcode = 1;
    if (!strcmp("snap", cmd)) {
        rcode = exec_snap();
    } else if (!strcmp("tree", cmd)) {
        rcode = exec_tree();
    } else {
        cerr << "Command not understood." << endl;
    }
    return rcode;
}


int main(int argc, char* argv[])
{
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " COMMAND" << endl;
        return 1;
    }

    return execute(argv[1]);
}
