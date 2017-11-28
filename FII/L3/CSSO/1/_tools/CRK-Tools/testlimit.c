#include <windows.h>


//----------------------------------------------------------------------
//
// EnablePrivilege
//
// Enables the specified privilege.
//
//----------------------------------------------------------------------
BOOL EnablePrivilege( PTCHAR Privilege )
{
    LUID luid;
	HANDLE	hToken;
	BOOL	result;
    TOKEN_PRIVILEGES tpPrevious;

	if(!OpenProcessToken( GetCurrentProcess(),
				TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
				&hToken )) {
	
		return FALSE;
	}
	
    if(!LookupPrivilegeValue( NULL, Privilege, &luid )) return FALSE;

    tpPrevious.PrivilegeCount       = 1;
    tpPrevious.Privileges[0].Luid   = luid;
    tpPrevious.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    result = AdjustTokenPrivileges(
            hToken,
            FALSE,
            &tpPrevious,
            sizeof(TOKEN_PRIVILEGES),
            NULL,
            NULL
            );
	if( result && GetLastError() != ERROR_SUCCESS ) {

		result = FALSE;
	}
	CloseHandle( hToken );
	return result;
}

void Usage()
{
    printf("usage: testlimit [-p [-n]] | [-t] | [-h] | [-u] | [-g [object size]] | [-m [MB]]\n");
    printf("  -g       Create GDI handles of specified size (default 1 byte)\n");
    printf("  -h       Create handles\n");
    printf("  -m       Leak memory in specified MBs (default is 1)\n");
    printf("  -n       Set min working set of processes to smallest\n");
    printf("  -p       Create processes.\n");
    printf("  -t       Create threads\n");
    printf("  -u       Create USER handles\n");
}

void Banner()
{
	printf("\nTestlimit - tests Windows limits\n");
	printf("By Mark Russinovich\n\n");
}

DWORD WINAPI ThreadProc(
  LPVOID lpParameter
)
{
    Sleep( INFINITE );
    return 0;
}

void PrintError( DWORD ErrorCode )
{
    HMODULE hModule = NULL; // default to system source
    LPSTR MessageBuffer;
    DWORD dwBufferLength;

    DWORD dwFormatFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_IGNORE_INSERTS |
        FORMAT_MESSAGE_FROM_SYSTEM ;


    //
    // Call FormatMessage() to allow for message 
    //  text to be acquired from the system 
    //  or from the supplied module handle.
    //

    if(dwBufferLength = FormatMessageA(
        dwFormatFlags,
        hModule, // module to get message from (NULL == system)
        ErrorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // default language
        (LPSTR) &MessageBuffer,  0, NULL )) {

        DWORD dwBytesWritten;

        //
        // Output message string on stderr.
        //
        WriteFile(
            GetStdHandle(STD_ERROR_HANDLE),
            MessageBuffer,
            dwBufferLength,
            &dwBytesWritten,
            NULL
            );

        //
        // Free the buffer allocated by the system.
        //
        LocalFree(MessageBuffer);
    }

    //
    // If we loaded a message source, unload it.
    //
    if(hModule != NULL) FreeLibrary(hModule);
}


void main( int argc, char *argv[])
{
	STARTUPINFO startup;
	PROCESS_INFORMATION procinfo;
	int	 i = 0, gdiSize = 1;

	if( argc < 2 ) {

        Usage();
		return;
	}

    if( argv[1][0] == 't' ) {

    } else if( argv[1][0] == 'n' ) {
    
        EnablePrivilege( SE_INC_BASE_PRIORITY_NAME );
        SetProcessWorkingSetSize( GetCurrentProcess(), 4096, 1024*1024 );

    } else if( !stricmp( argv[1], "-p" )) {

        BOOLEAN minws = FALSE;

        Banner();
        if( argc == 3 && !stricmp( argv[2], "-n" )) {

            printf("Creating processes with min working set...\n");
            minws = TRUE;
        } else {

            printf("Creating processes...\n");
        }
        startup.cb = sizeof(startup);
        memset( &startup, 0, sizeof(startup));
        while( CreateProcess( "testlimit.exe", 
                              minws ? "testlimit n" : "testlimit t", 
                              NULL, NULL, FALSE, 0,
                              NULL, NULL, &startup, &procinfo )) {

            i++;
            if( !( i % 100 )) printf("\r%d", i );
        }
        printf("\rCreated %d processes. Lasterror: %d\n", i, GetLastError() );
        PrintError( GetLastError());
    
    } else if( !stricmp( argv[1], "-t" )) {

        BOOLEAN minstack = FALSE;

        Banner();
        printf("Creating threads...\n");
        while( CreateThread( NULL, 0, ThreadProc, 0, CREATE_SUSPENDED, NULL )) {

            i++;
            if( !( i % 100 )) printf("\r%d", i );
        }
        printf("\rCreated %d threads. Lasterror: %d\n", i, GetLastError() );
        PrintError( GetLastError());

    } else if( !stricmp( argv[1], "-h")) {

        HANDLE hEvent;

        Banner();
        printf("Creating handles...\n");
        
        hEvent = CreateEvent( NULL, FALSE, FALSE, "TestLimit" );
        while( OpenEvent( EVENT_ALL_ACCESS, FALSE, "TestLimit" )) {

            i++;
            if( !( i % 100 )) printf("\r%d", i );
        }
        printf("\rCreated %d handles. Lasterror: %d\n", i, GetLastError() );
        PrintError( GetLastError());

    } else if( !stricmp( argv[1], "-g")) {

        Banner();
        if( argc > 2 ) {

             sscanf( argv[2], "%d", &gdiSize );
            printf("Creating GDI %d byte objects...\n", gdiSize );

        } else 
            printf("Creating GDI objects...\n");
        
        while( CreateBitmap( 1, gdiSize, 1, 1, NULL )) {

            i++;
            if( !( i % 100 )) printf("\r%d", i );
        } 
        printf("\rCreated %d GDI objects. Lasterror: %d\n", i, GetLastError() );
        PrintError( GetLastError() );

    } else if( !stricmp( argv[1], "-u")) {

        Banner();
        printf("Creating USER objects (menus)...\n");
        
        while( CreateMenu()) {

            i++;
            if( !( i % 100 )) printf("\r%d", i );
        } 
        printf("\rCreated %d USER objects. Lasterror: %d\n", i, GetLastError() );
        PrintError( GetLastError() );

    } else if( !stricmp( argv[1], "-m")) {

        Banner();
        if( argc > 2 ) {

             sscanf( argv[2], "%d", &gdiSize );
            printf("Leaking private bytes %d MB at a time...\n", gdiSize );

        } else 
            printf("Leaking private bytes...\n");
        
        while( VirtualAlloc( NULL, gdiSize * 1024*1024, MEM_COMMIT, PAGE_READWRITE )) {

            i++;
            if( !( i % 100 )) printf("\r%d", i );
        } 
        printf("\rLeaked %d MB of private memory. Lasterror: %d\n", i * gdiSize, GetLastError() );
        PrintError( GetLastError() );

    } else {

        Usage();
        return;
    }

    Sleep( INFINITE );
}
