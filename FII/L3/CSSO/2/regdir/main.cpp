#include <iostream>
#include <cstring>
#include <string>
#include <windows.h>

#define MAX_SIZE 128
#define DIR_SEP "\\"
#define KEY_ROOT "Software\\CSSO"


using namespace std;


void path2key(const char * path, char * key)
{
    // Transforma o cale de director intr-o cheie de registri.
    static char root[MAX_SIZE] = "";
    const char *src;
    if (strlen(root)) {
        src = strstr(path, root);
    } else {
        // Setam pentru prima oara radacina.
        string path_str(path);
        size_t pos = path_str.rfind(DIR_SEP) + 1;
        src = path + pos;
        strcpy(root, src);
    }
    strcpy(key, KEY_ROOT);
    strcat(strcat(key, DIR_SEP), src);
}


HKEY create_key(char * path)
{
    char key[MAX_SIZE];
    path2key(path, key);
    cout << "Creating key: " << key << endl;
    HKEY key_handle;
    LONG key_ret = RegCreateKeyEx(
        HKEY_CURRENT_USER, key, 0, NULL,
        REG_OPTION_VOLATILE, KEY_WRITE | KEY_READ,
        NULL, &key_handle, NULL
    );

    if (key_ret != ERROR_SUCCESS) {
        cerr << "Couldn't create key because of: " << key_ret << endl;
        return NULL;
    }
    return key_handle;
}


void create_value(HKEY key_handle, char * name, long long dim)
{
    cout << "Creating value under " << key_handle << ": " << name << " (" << dim << ")" << endl;
    unsigned int norm_dim = (unsigned int)dim;
    LONG value_ret = RegSetValueEx(
        key_handle, name, 0,
        REG_DWORD, (const BYTE *)&norm_dim, sizeof(norm_dim)
    );
    if (value_ret != ERROR_SUCCESS) {
        cerr << "Couldn't create value because of: " << value_ret << endl;
    }
}


unsigned long long get_file_dim(const WIN32_FIND_DATA &data)
{
    unsigned long long dim = 0;
    memcpy((void *)&dim, (void *)&data.nFileSizeLow, 4);
    memcpy((void *)(&dim) + 4, (void *)&data.nFileSizeHigh, 4);
    return dim;
}


void path_join(const char * path, const char * name, char * new_path)
{
    strcpy(new_path, path);
    strcat(strcat(new_path, DIR_SEP), name);
}


void explore(char* path)
{
    /* Exploram recursiv directorul dat si cream intrarile necesare
       pentru continutul fiecarui nivel.
     */
    char new_path[MAX_SIZE];
    WIN32_FIND_DATA data;
    path_join(path, "*", new_path);
    HANDLE find_handle = FindFirstFile((LPCTSTR)new_path, &data);
    if (find_handle == INVALID_HANDLE_VALUE) {
        cerr << "Couldn't open path: " << path << " due to: " << GetLastError() << endl;
        return;
    }

    // S-a putut deschide respectiva cale, cream cheia aferenta.
    HKEY key_handle = create_key(path);
    if (!key_handle) {
        return;
    }
    // Acum se itereaza toate entitatile si se exploreaza recursiv mai departe.
    do {
        char *name = data.cFileName;
        if (!strcmp(name, ".") || !strcmp(name, "..")) continue;
        if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            // Am gasit un director, cream subcheie si-l parcurgem mai departe.
            path_join(path, name, new_path);
            explore(new_path);
        } else {
            // Este fisier, cream valoare cu dimensiunea acestuia.
            unsigned long long dim = get_file_dim(data);
            create_value(key_handle, name, dim);
        }
    } while(FindNextFile(find_handle, &data));

    RegCloseKey(key_handle);
    FindClose(find_handle);
}


int main(int argc, char* argv[])
{
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " DIR" << endl;
        return 1;
    }

    explore(argv[1]);
    return 0;
}
