#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <wininet.h>

#pragma comment(lib, "Wininet")

#define MAX_SIZE 10 * (1 << 20)
#define NAME "ftpexec"
#define DEST "download"


using namespace std;


HINTERNET net_handle;
char dl_buffer[MAX_SIZE];


string download_file(const string &url)
{
    cout << "Downloading: " << url << endl;
    HINTERNET url_handle = InternetOpenUrl(
        net_handle,
        url.c_str(),
        NULL,
        NULL,
        INTERNET_FLAG_PASSIVE,
        NULL
    );
    if (!url_handle) {
        cerr << "Can't open url handle: " << GetLastError() << endl;
        return "";
    }

    unsigned int length = 0;
    BOOL status = InternetReadFile(
        url_handle,
        dl_buffer,
        MAX_SIZE,
        (LPDWORD)&length
    );
    if (!status) {
        cerr << "Can't download file from url: " << GetLastError() << endl;
        return "";
    }

    //cout << dl_buffer << endl;
    int idx = url.rfind("/");
    string fname = url.substr(idx + 1, url.length() - idx);
    string fpath(DEST);
    fpath.append("\\");
    fpath.append(fname);

    cout << "Writing into '" << fpath << "' " << length << " bytes of data." << endl;
    ofstream stream(fpath, ios::out | ios::binary);
    stream.write(dl_buffer, length);
    stream.close();

    InternetCloseHandle(url_handle);
    return fpath;
}


int exec_file(const string &dl_path)
{
    cout << "Executing: " << dl_path << endl;

    STARTUPINFO info={sizeof(info)};
    PROCESS_INFORMATION processInfo;
    int idx = dl_path.rfind("/");
    int len = dl_path.length();
    string path = dl_path.substr(0, idx);
    string cmd = dl_path.substr(idx + 1, len - idx);

    BOOL status = CreateProcess(
        path.c_str(),
        (LPSTR)cmd.c_str(),
        NULL,
        NULL,
        TRUE,
        0,
        NULL,
        NULL,
        &info,
        &processInfo
    );

    if (status) {
        WaitForSingleObject(processInfo.hProcess, INFINITE);
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
    } else {
        cerr << "Couldn't run process '" << dl_path << "': " << GetLastError() << endl;
        return 3;
    }
    return 0;
}


int parse_exec(const string &path)
{
    cout << "Parsing: " << path << endl;
    // Citeste continutul fisierului.
    ifstream stream(path);
    string line;
    int rcode = 0, last;
    while (stream >> line) {
        //cout << line << endl;
        int s_start = line.compare(0, 4, "http");
        int s_end = line.compare(line.length() - 4, 4, ".exe");
        if (s_start || s_end)
            continue;
        string dl_path = download_file(line);
        if (!dl_path.length())
            rcode = 2;
        else {
            last = exec_file(dl_path);
            if (last)
                rcode = last;
        }
    }
    stream.close();
    return rcode;
}


int process(char *host, char *usr, char *pwd)
{
    // Deschidem handle de internet.
    net_handle = InternetOpen(
        NAME,
        INTERNET_OPEN_TYPE_PRECONFIG,
        NULL,
        NULL,
        NULL
    );
    if (!net_handle) {
        cerr << "Can't open internet handle: " << GetLastError() << endl;
        return 1;
    }

    // Ne conectam la serverul ftp.
    HINTERNET ftp_handle = InternetConnect(
        net_handle,
        host,
        INTERNET_DEFAULT_FTP_PORT,
        usr,
        pwd,
        INTERNET_SERVICE_FTP,
        INTERNET_FLAG_PASSIVE,
        NULL
    );
    if (!ftp_handle) {
        cerr << "Can't open ftp handle: " << GetLastError() << endl;
        InternetCloseHandle(net_handle);
        return 1;
    }

    // Listam toate fisierele.
    WIN32_FIND_DATA data;
    HINTERNET find_handle = FtpFindFirstFile(
        ftp_handle,
        "*",
        &data,
        INTERNET_FLAG_RELOAD,
        NULL
    );
    if (!find_handle) {
        cerr << "Can't search ftp files: " << GetLastError() << endl;
        InternetCloseHandle(ftp_handle);
        InternetCloseHandle(net_handle);
        return 1;
    }
    int rcode = 0, last;
    do {
        //cout << data.cFileName << endl;
        string name(data.cFileName);
        if (name.compare(name.length() - 4, 4, ".txt"))
            continue;
        //cout << name << endl;
        // Acum descarcam fisierele text.
        string dest(DEST);
        dest.append("\\");
        dest.append(name);
        BOOL status = FtpGetFile(
            ftp_handle,
            name.c_str(),
            dest.c_str(),
            FALSE,
            FILE_ATTRIBUTE_NORMAL,
            FTP_TRANSFER_TYPE_ASCII,
            NULL
        );
        if (!status)
            cerr << "Couldn't download file '" << name << "': " << GetLastError() << endl;
        else {
            cout << name << " -> " << dest << endl;
            last = parse_exec(dest);
            if (last)
                rcode = last;
        }
    } while (InternetFindNextFile(find_handle, &data));

    // Inchidem toate hadle-urile deschise.
    FindClose(find_handle);
    InternetCloseHandle(ftp_handle);
    InternetCloseHandle(net_handle);
    return rcode;
}


int main(int argc, char *argv[])
{
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " HOST USR PWD" << endl;
        return 1;
    }

    return process(argv[1], argv[2], argv[3]);
}
