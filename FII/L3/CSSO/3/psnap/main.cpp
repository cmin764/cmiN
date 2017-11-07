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
#define INDENT 4


using namespace std;


struct ProcNode {
    unsigned int pid, ppid;
    string name;
    bool exists;
    vector<ProcNode *> sons;

    ProcNode(unsigned int pid = -1, unsigned int ppid = -1, string name = "", bool exists = false) :
        pid(pid), ppid(ppid), name(name), exists(exists) {}
};

// pid -> ppid, name
typedef map<unsigned int, pair<unsigned int, string> > procs_t;
// pid -> ppid, address
typedef map<unsigned int, ProcNode *> link_t;
// lista de arbori (paduri)
typedef vector<pair<int, ProcNode *> > nodes_t;


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


nodes_t get_ptree()
{
    nodes_t roots;
    procs_t procs;

    HANDLE hfile = OpenFileMapping(FILE_MAP_WRITE, FALSE, FNAME);
    const char *file_addr = (const char *)MapViewOfFile(hfile, FILE_MAP_WRITE, 0, 0, 0);
    if (!file_addr) {
        cerr << "Couldn't map file: " << GetLastError() << endl;
        CloseHandle(hfile);
        return roots;
    }
    /* Citeste toate liniile din fisierul de comunicare si salveaza procesele
     intr-o structura. */
    //cout << file_addr << endl;
    istringstream sio(file_addr);
    unsigned int pid, ppid;
    string name;

    while (sio.good()) {
        char buffer[BUFF];
        sio.getline(buffer, BUFF);
        if (sio.eof() || sio.fail()) break;
        char name_str[BUFF];
        sscanf(buffer, "%u %u %[^\t\n]s", &pid, &ppid, name_str);
        name.assign(name_str);
        procs[pid] = make_pair(ppid, name);
    }
    UnmapViewOfFile(file_addr);
    CloseHandle(hfile);

    link_t links;
    link_t::iterator link_it;
    for (auto it = procs.cbegin(); it != procs.cend(); ++it) {
        pid = it->first;
        ppid = it->second.first;
        name = it->second.second;
        //cout << pid << " " << "(" << ppid << ", " << name << ") " << endl;

        // Cautam nodul aferent procesului curent, daca nu exista, il cream.
        link_it = links.find(pid);
        ProcNode *son, *parent;
        if (link_it == links.end()) {
            // Cream nod nou, inexistent momentan aferent procesului curent.
            son = new ProcNode(pid, ppid, name, true);
            links[pid] = son;
        } else son = link_it->second;
        // Marcam nodul ca existent (in caz de a fost adaugat in trecut pe post de tata)
        son->ppid = ppid;
        son->name = name;
        son->exists = true;    // procesul chiar exista

        // Acum cautam tatal si daca exista, incercam sa-i facem un nod virtual,
        // ce poate deveni real de-a lungul parcurgerii.
        link_it = links.find(ppid);
        if (link_it == links.end()) {
            // Cream nod parinte nou, ca nu exista, insa e marcat ca fiind virtual.
            parent = new ProcNode(ppid);
            // Nu stim ce parinte sau nume are si e non-existent (momentan).
            links[ppid] = parent;
        } else parent = link_it->second;
        // Acum ca avem tatal corespunzator, ii adaugam fiul `pid`.
        parent->sons.push_back(son);
    }

    /* Acum, alegem fiecare nod radacina ce este de asemenea si existent.
    Daca are parinte inexistent, il consideram radacina unui intreg arbore
    si nicidecum subarbore. */
    int index = 1;
    for (auto& elem : links) {
        ProcNode *node = elem.second;
        if (!node->exists) continue;
        link_it = links.find(node->ppid);
        if (link_it == links.end() || !link_it->second->exists) {
            roots.push_back(make_pair(index++, node));
        }
    }
    return roots;
}


void show_tree(ProcNode *node, int level)
{
    for (int cnt = level * INDENT; cnt > 0; --cnt)
        cout << " ";
    cout << node->name << " " << node->pid << endl;
    for (auto &son : node->sons)
        show_tree(son, level + 1);
}


void close_tree(ProcNode *node)
{
    // Inchidem nodul proces dupa ce ne asiguram ca am inchis toti copii.
    for (auto &son : node->sons)
        close_tree(son);

    // Inchidem efectiv procesul.
    unsigned int pid = node->pid;
    cout << "Inchidem: " << pid;

    HANDLE hproc = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (TerminateProcess(hproc, 0)) {
        cout << " OK";
    } else {
        cout << " FAIL";
    }
    cout << endl;
    CloseHandle(hproc);
}


int exec_tree()
{
    // Obtine arborele de procese.
    nodes_t roots = get_ptree();
    if (!roots.size()) {
        cerr << "Something went wrong while getting process tree." << endl;
        return 3;
    }

    // Afiseaza arborii de procese si intreaba utilizatorul ce vrea sa inchida.
    int ask = 0;
    do {
        for (auto &root : roots) {
            int level = 0;
            cout << "[" << root.first << "]" << endl;
            show_tree(root.second, level);
            cout << endl;
        }
        cout << "Close tree (0 - exit): ";
        cin >> ask;
        cin.get();
        if (ask < 0 || ask > roots.size()) {
            cerr << "Invalid option." << endl;
            continue;
        }
        if (ask) {
            close_tree(roots[ask - 1].second);
            cout << "Press enter to continue..." << endl;
            cin.get();
        }
    } while (ask);

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
