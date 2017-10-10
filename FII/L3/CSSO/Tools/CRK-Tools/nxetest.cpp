// nxetest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>

typedef int (*PPUTS)( const char *string );
typedef void (/*__stdcall */ *PMEMORYEXECUTE)( PPUTS pPuts, char *string ) ;

void MemoryExecute( PPUTS pPuts, char *string )
{
	pPuts( string );
}	

int main(int argc, char* argv[])
{
	PMEMORYEXECUTE	pMemoryExecute;

	printf("\nNo-Execute Protection Test Applet\n");
	printf("By Mark Russinovich\n\n");

	pMemoryExecute = (PMEMORYEXECUTE) new char[1024];
	memcpy( pMemoryExecute, MemoryExecute, 1024);

	pMemoryExecute( puts, "Hello from the heap!\n");
	return 0;
}

