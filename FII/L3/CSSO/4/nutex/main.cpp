#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <windows.h>


#define MAX_SIZE 1 << 13
#define FNAME "nutex.txt"

#define MOD 128
#define CHECKS 256
#define SENTINEL 1

#define E_READY "ready"
#define E_GEN "generate"
#define E_VER "verify"
#define M_LOCK "lock"

// Setari.
#define DEBUG true    // afiseaza mesaje de depanare
#define USE_EVENT    // foloseste evenimente (sau mutex in caz contrar)


using namespace std;


char *put_nr(char *buffer, unsigned int nr)
{
    // Copiaza bytes numarului in buffer raw.
    memcpy((void *)buffer, (void *)&nr, sizeof(nr));
    buffer = (char *)((void *)buffer + sizeof(nr));
    // Si marcheaza cu NULL terminarea noii zone de memorie in buffer.
    *buffer = '\0';
    // Returneaza noua adresa.
    return buffer;
}


char *get_nr(char *buffer, unsigned int &nr)
{
    // Copiaza bytes bufferului in numar.
    memcpy((void *)&nr, (void *)buffer, sizeof(nr));
    buffer = (char *)((void *)buffer + sizeof(nr));
    // Returneaza noua adresa.
    return buffer;
}


int exec_generate()
{
    /** Genereaza numere aleatoare si le trimite ca expresie celuilalt proces. */

    // Initializam un seed nou in functie de timp pt. a avea numere diferite.
    srand(time(NULL));
    // Deschidem fisierul mapat in memorie.
    HANDLE hfile = CreateFileMapping(NULL, NULL, PAGE_READWRITE,
                                     0, MAX_SIZE, FNAME);
    // Si un pointer la view-ul lui pt. a scrie/citi continut din el.
    char *file_addr = (char *)MapViewOfFile(hfile, FILE_MAP_WRITE, 0, 0, 0);
    if (!file_addr) {
        cerr << "Couldn't map file: " << GetLastError() << endl;
        CloseHandle(hfile);
        return 3;
    }
    file_addr[0] = '\0';

    // Eveniment initial ce sincronizeaza numai pornirile celor doua procese.
    HANDLE ready_event = CreateEvent(
        NULL,
        TRUE,
        FALSE,
        E_READY
    );
    if (ready_event == INVALID_HANDLE_VALUE) {
        cerr << "Couldn't create ready event: " << GetLastError();
        UnmapViewOfFile(file_addr);
        CloseHandle(hfile);
        return 4;
    }
    // Suntem pregatiti sa lasam procesul de verificare sa citeasca fisierul
    // mapat in memorie.
    SetEvent(ready_event);

    unsigned int a, b;
    char *buffer = file_addr;

    // Initializam partea de sincronizare intre procese.
    #ifdef USE_EVENT
    HANDLE gen_event = CreateEvent(
        NULL,
        FALSE,
        FALSE,
        E_GEN
    );
    HANDLE ver_event = CreateEvent(
        NULL,
        FALSE,
        /* Ca sa nu fim in deadlock, marcam procesul de verificare ca fiind
        deja pregatit. */
        TRUE,
        E_VER
    );
    if (gen_event == INVALID_HANDLE_VALUE || ver_event == INVALID_HANDLE_VALUE) {
        cerr << "Couldn't create sync event(s): " << GetLastError();
        if (gen_event)
            CloseHandle(gen_event);
        if (ver_event)
            CloseHandle(ver_event);
        CloseHandle(ready_event);
        UnmapViewOfFile(file_addr);
        CloseHandle(hfile);
        return 4;
    }
    #else
    HANDLE lock_mutex = CreateMutex(
        NULL,
        FALSE,
        M_LOCK
    );
    if (lock_mutex == INVALID_HANDLE_VALUE) {
        cerr << "Couldn't create sync mutex: " << GetLastError();
        CloseHandle(ready_event);
        UnmapViewOfFile(file_addr);
        CloseHandle(hfile);
        return 4;
    }
    #endif

    for (int cnt = 0; cnt < CHECKS; ++cnt) {
        // Folosim partea de sincronizare pt. a genera si scrie in fisier date complete.
        // Asteptam ca fisierul de verificare sa termine citirea si afisajul.
        #ifdef USE_EVENT
        WaitForSingleObject(ver_event, INFINITE);
        #else
        WaitForSingleObject(lock_mutex, INFINITE);
        #endif
        // Intram in sectiunea critica.

        a = rand() % MOD + 1;
        b = 2 * a;
        if (DEBUG) {
            cout << "Generate: " << a << " " << b
                 << " (" << clock() << ")"
                 << endl;
        }
        // Scriem bytes lui `a` si `b` in ordine in fisierul mapat in memorie.
        buffer = put_nr(put_nr(buffer, a), b);
        // Pentru a fi lasat catre citire de procesul ce verifica numerele.

        // Acum parasim sectiunea critica.
        #ifdef USE_EVENT
        // Marcam evenimentul de generare ca fiind pregatit de o noua citire.
        SetEvent(gen_event);
        #else
        ReleaseMutex(lock_mutex);
        #endif
    }

    // Trimitem si santinela pt. a marca sfarsitul generarii.
    #ifdef USE_EVENT
    WaitForSingleObject(ver_event, INFINITE);
    #else
    WaitForSingleObject(lock_mutex, INFINITE);
    #endif

    put_nr(put_nr(buffer, SENTINEL), SENTINEL);

    #ifdef USE_EVENT
    SetEvent(gen_event);
    #else
    ReleaseMutex(lock_mutex);
    #endif

    cout << "Press enter to end execution..." << endl;
    cin.get();

    #ifdef USE_EVENT
    CloseHandle(gen_event);
    CloseHandle(ver_event);
    #else
    CloseHandle(lock_mutex);
    #endif

    CloseHandle(ready_event);
    UnmapViewOfFile(file_addr);
    CloseHandle(hfile);

    return 0;
}


int exec_verify()
{
    /** Citeste si verifica numerele generate pana la termenul santinela. */

    // Deschidem fisierul mapat in memorie.
    HANDLE hfile = CreateFileMapping(NULL, NULL, PAGE_READWRITE,
                                     0, MAX_SIZE, FNAME);
    // Si un pointer la view-ul lui pt. a scrie/citi continut din el.
    char *file_addr = (char *)MapViewOfFile(hfile, FILE_MAP_READ, 0, 0, 0);
    if (!file_addr) {
        cerr << "Couldn't map file: " << GetLastError() << endl;
        CloseHandle(hfile);
        return 3;
    }

    // Eveniment initial ce sincronizeaza numai pornirile celor doua procese.
    HANDLE ready_event = CreateEvent(
        NULL,
        TRUE,
        FALSE,
        E_READY
    );
    if (ready_event == INVALID_HANDLE_VALUE) {
        cerr << "Couldn't create ready event: " << GetLastError();
        UnmapViewOfFile(file_addr);
        CloseHandle(hfile);
        return 4;
    }
    // Asteptam sa primim permisiunea sa citim fisierul.
    WaitForSingleObject(ready_event, INFINITE);

    unsigned int a, b;
    char *buffer = file_addr;

    // Initializam partea de sincronizare intre procese.
    #ifdef USE_EVENT
    HANDLE gen_event = CreateEvent(
        NULL,
        FALSE,
        FALSE,
        E_GEN
    );
    HANDLE ver_event = CreateEvent(
        NULL,
        FALSE,
        /* Ca sa nu fim in deadlock, marcam procesul de verificare ca fiind
        deja pregatit. */
        TRUE,
        E_VER
    );
    if (gen_event == INVALID_HANDLE_VALUE || ver_event == INVALID_HANDLE_VALUE) {
        cerr << "Couldn't create sync event(s): " << GetLastError();
        if (gen_event)
            CloseHandle(gen_event);
        if (ver_event)
            CloseHandle(ver_event);
        CloseHandle(ready_event);
        UnmapViewOfFile(file_addr);
        CloseHandle(hfile);
        return 4;
    }
    #else
    HANDLE lock_mutex = CreateMutex(
        NULL,
        FALSE,
        M_LOCK
    );
    if (lock_mutex == INVALID_HANDLE_VALUE) {
        cerr << "Couldn't create sync mutex: " << GetLastError();
        CloseHandle(ready_event);
        UnmapViewOfFile(file_addr);
        CloseHandle(hfile);
        return 4;
    }
    #endif

    // Citim numerele, cum am gasit ceva nou scris in fisier.
    unsigned int total = 0, ok = 0;
    bool stop = false;

    while (!stop) {
        // Folosim partea de sincronizare pt. a genera si scrie in fisier date complete.
        // Asteptam ca fisierul de generare sa termine generarea si scrierea.
        #ifdef USE_EVENT
        WaitForSingleObject(gen_event, INFINITE);
        #else
        WaitForSingleObject(lock_mutex, INFINITE);
        #endif
        // Intram in sectiunea critica.

        if (buffer[0]) {
            // Avem ceva nou, deci citim numerele din memorie.
            buffer = get_nr(get_nr(buffer, a), b);

            // Acum verificam santinela si daca n-am ajuns la final, atunci verificam
            // efectiv numere.
            if (a == SENTINEL && b == SENTINEL) {
                stop = true;
            } else {
                total += 1;
                if (b == 2 * a) {
                    ok += 1;
                    if (DEBUG) {
                        cout << b << " == " << "2 * " << a
                             << " (" << clock() << ")"
                             << endl;
                    }
                } else {
                    cerr << b << " != " << "2 * " << a << endl;
                }
            }
        }

        // Acum parasim sectiunea critica.
        #ifdef USE_EVENT
        // Marcam evenimentul de generare ca fiind pregatit de o noua citire.
        SetEvent(ver_event);
        #else
        ReleaseMutex(lock_mutex);
        #endif
    }
    cout << "OK: " << ok << "/" << total << endl;

    cout << "Press enter to end execution..." << endl;
    cin.get();

    #ifdef USE_EVENT
    CloseHandle(gen_event);
    CloseHandle(ver_event);
    #else
    CloseHandle(lock_mutex);
    #endif

    CloseHandle(ready_event);
    UnmapViewOfFile(file_addr);
    CloseHandle(hfile);

    return 0;
}


int execute(const char *cmd)
{
    int rcode = 1;
    if (!strcmp("generate", cmd)) {
        rcode = exec_generate();
    } else if (!strcmp("verify", cmd)) {
        rcode = exec_verify();
    } else {
        cerr << "Command not understood." << endl;
    }
    return rcode;
}



int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " COMMAND" << endl;
        return 1;
    }

    return execute(argv[1]);
}
