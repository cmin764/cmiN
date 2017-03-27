   /*******************************************************/
   /*      "C" Language Integrated Production System      */
   /*                                                     */
   /*                  A Product Of The                   */
   /*             Software Technology Branch              */
   /*             NASA - Johnson Space Center             */
   /*                                                     */
   /*               CLIPS Version 6.00  01/01/93          */
   /*              IDE Text Editor 1.00  01/01/93         */
	/*                                                     */
   /*                    SEARCH MODULE                    */
   /*******************************************************/

/**************************************************************/
/* Purpose: To preform all operations required by the         */
/*          Search and Replace Menu Items                     */
/*                                                            */
/* Principal Programmer(s):                                   */
/*      Christopher J. Ortiz                                  */
/*                                                            */
/* Contributing Programmer(s):                                */
/*      Search/Replace adapted from CView Search/Replace      */
/*      Algorithm. Eastern Language Systems, Provo, UT        */
/*                                                            */
/* Revision History:                                          */
/**************************************************************/

/*-------------------------------+
| Windows & System Include Files |
+-------------------------------*/
#include <windows.h>
#include <string.h>
#include <commdlg.h>
#include <stdio.h>
#include <stdlib.h>   // GDR

/*---------------------+
| Editor Include Files |
+---------------------*/

#include "setup.h"
#include "ide_srch.h"
#include "ide_main.h" // GDR
#include "ide_ids.h"

/*-----------------+
| Global Variables |
+-----------------*/
FINDREPLACE fr;
UINT uFindReplaceMsg;
BOOL FirstSearch = TRUE;
char SearchFor [255];
char ReplaceWith [255];
HWND SearchDlg = NULL;

/*----------------+
| Local Functions |
+----------------*/
void DoSearch ( HWND, int, int, int);
char *stristr ( char*, char* );

/********************************************************************
* SetUpSearch: Will display the common dialog for search & replace
*   as well as preventing the dialogs from being called twice.
****************************************************************/

void SetUpSearch ( HWND hWnd, int Replace )

{  extern FINDREPLACE fr;
   extern BOOL StartUp;
   extern HWND SearchDlg;

   /*-----------------------+
   | Call the common dialog |
   | for Search or Replace  |
   +-----------------------*/
   fr.Flags = FR_HIDEUPDOWN | FR_HIDEWHOLEWORD ;
   if (Replace)
		SearchDlg = ReplaceText(&fr);
   else
      SearchDlg = FindText(&fr);

	/*-------------------+
   | Disable Menu Items |
   +-------------------*/
   if ( SearchDlg )
   {  HMENU hMenu = GetMenu ( hWnd );
      EnableMenuItem(hMenu, IDM_BUFFER_FIND,    MF_BYCOMMAND | MF_GRAYED);
      EnableMenuItem(hMenu, IDM_BUFFER_REPLACE ,MF_BYCOMMAND | MF_GRAYED);
		FirstSearch = TRUE;
   }
}

/**************************************************************
* StartSearch: Call back procedure for the common Dialog Box
*    to do the shut down, search or replace.
***************************************************************/

#if IBM_TBC
#pragma argsused
#endif
int StartSearch (HWND hWnd, WPARAM wParam, LONG lParam )

{  FINDREPLACE FAR* lpfr;
	extern HWND SearchDlg;

   lpfr = ( FINDREPLACE FAR*) lParam;

   /*-----------------------+
   | Terminate Find/Replace |
   |    Dialog if needed    |
	+-----------------------*/
   if (lpfr->Flags & FR_DIALOGTERM)
	{  HMENU hMenu = GetMenu ( hWnd );

      EnableMenuItem(hMenu, IDM_BUFFER_FIND,    MF_BYCOMMAND | MF_ENABLED);
      EnableMenuItem(hMenu, IDM_BUFFER_REPLACE ,MF_BYCOMMAND | MF_ENABLED);
      return 0;
	}

   /*-----------------------------------------+
   | Preform the actual search and/or Replace |
	+-----------------------------------------*/
   ShowWindow ( SearchDlg, SW_HIDE );
   DoSearch ( hWnd,
		((lpfr->Flags & FR_REPLACE) || (lpfr->Flags & FR_REPLACEALL)),
      (lpfr->Flags & FR_REPLACEALL),
      (lpfr->Flags & FR_MATCHCASE) );
   ShowWindow ( SearchDlg, SW_SHOW );
	SetFocus (hWnd );
	return 0;
}

/***************************************************************
* DoSearch: Scans the edit buffer for mach items and can replace
*   items if needed.
****************************************************************/

#if IBM_TBC
#pragma argsused
#endif
void DoSearch(
	HWND hWnd,
	int Replace,
	int ReplaceAll,
	int MatchCase )

{  extern char SearchFor [255];
   extern char ReplaceWith [255];
   extern HWND hEditWnd;
	extern BOOL FirstSearch;
	static char * pBase = NULL;
	static char * pFound = NULL;
	int searchLen, loc, ReplaceLen;
	int text_length;
	char * pEditBuffer;
	int Count = 0;

	if (FirstSearch)
	  pFound = NULL;
	FirstSearch = FALSE;

	searchLen = strlen(SearchFor);
	if (!searchLen)
	{  MessageBeep(0);
		return;
	}

	do
	{
		// Begin GDR
		// hEditBuffer = (HANDLE)SendMessage(hEditWnd, EM_GETHANDLE, 0, 0L);
		// pEditBuffer = LocalLock( hEditBuffer );
		text_length = SendMessage(hEditWnd,WM_GETTEXTLENGTH,0,0);
		pEditBuffer = (char *) malloc(text_length+1);
		if (pEditBuffer == NULL)
		  {
			MessageBeep ( 0 );
			MessageBox (hEditWnd,"Can not complete operation",
					"Memory Low", MB_ICONSTOP | MB_TASKMODAL );
			return;
		  }

		SendMessage(hEditWnd,WM_GETTEXT,text_length+1,
						(LPARAM) pEditBuffer);
		// End GDR

		/*-----------------+
		| Text replacement |
		+-----------------*/
		if (!pFound)
      {  pBase = NULL;
      }
      else
      {  ReplaceLen = strlen(ReplaceWith);
	 if ((ReplaceAll || Replace) && ReplaceLen )
	 {  
	    SendMessage(hEditWnd, EM_REPLACESEL, 0, (DWORD)(LPSTR)ReplaceWith);
            Count ++;
	 }
      }

      /*----------------------+
      | Search for next match |
      +----------------------*/
		{ WORD Temp;
        Temp = HIWORD(SendMessage(hEditWnd, EM_GETSEL, 0, 0L));
        pBase = pEditBuffer + Temp;
      }
      if ( MatchCase )
	 pFound = strstr ( pBase, SearchFor );
      else
			pFound = stristr( pBase, SearchFor );

		loc = pFound - pEditBuffer;

		// Begin GDR
		SendMessage(hEditWnd, EM_SETSEL, loc, loc + searchLen);



		// LocalUnlock( hEditBuffer );
		free(pEditBuffer);
		// End GDR

	} while ( pFound && ReplaceAll);

	if (ReplaceAll)
	{  char Buffer[20];
		sprintf ( (char *)&Buffer,"%d Items Replaced", Count );
		MessageBox ( hEditWnd, Buffer,"",MB_ICONINFORMATION | MB_OK);
	}

	SetFocus(hEditWnd);
}

/******************************************************************
* stristr: Finds the first occurrence of one substring in another
*   without case sensitivity.
********************************************************************/

char *stristr(	char *Source, char *Target )

{  int TargetSize = strlen(Target);
   int SourceSize = strlen(Source);
   char *pStr;
   int notfound = 1;

   for (pStr = Source;
      (pStr <= (Source + SourceSize - TargetSize)) && notfound;
      pStr++)
#if IBM_TBC
         notfound = strnicmp(pStr, Target, TargetSize);
#endif
#if IBM_MCW
         notfound = _strnicmp(pStr, Target, TargetSize);
#endif
#if (! IBM_TBC) && (! IBM_MCW)
         notfound = strnicmp(pStr, Target, TargetSize);
#endif

   if (notfound)
      return (NULL);
   else
      return (pStr-1);
}






