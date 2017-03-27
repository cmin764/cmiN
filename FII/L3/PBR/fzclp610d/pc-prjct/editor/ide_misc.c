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
   /*                     PRINT MODULE                    */
	/*******************************************************/

/**************************************************************/
/* Purpose: Handle Dialogs, File I/O, and Printing.           */
/*                                                            */
/* Principal Programmer(s):                                   */
/*      Christopher J. Ortiz                                  */
/*                                                            */
/* Contributing Programmer(s):                                */
/*      Sample Code from Microsoft SDK                        */
/*      Sample Code from Borland C++                          */
/*                                                            */
/* Revision History:                                          */
/*                                                            */
/**************************************************************/

#include <windows.h>
#include <commdlg.h>

#include <io.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // GDR

#include "setup.h"
#include "ide_ids.h"
#include "ide_main.h"
#include "ide_misc.h"

PRINTDLG pd;
BOOL     bAbort = FALSE;
HWND     hAbortDlgWnd = NULL;

/******************************************************************
* SaveFile: This saves the current contents of the Edit buffer
*******************************************************************/

BOOL SaveFile(
	HWND hWnd)

{  extern HWND hEditWnd;
	HICON hSaveCursor;
	// extern HANDLE hEditBuffer;
	int text_length; // GDR
	char *pEditBuffer;
	BOOL bSuccess;
	int IOStatus;
	extern HFILE hFile; // GDR
	extern OFSTRUCT OfStruct;
	extern char szFileName[];

	if ((hFile = OpenFile(szFileName, &OfStruct, OF_CANCEL | OF_CREATE)) < 0)
	{  extern char szTemp[];
		/*---------------------------+
		| If the file can't be saved |
		+---------------------------*/
		sprintf(szTemp, "Cannot write to %s.", szFileName);
		MessageBox(hWnd, szTemp, NULL, MB_OK | MB_ICONHAND);
		return (FALSE);
	}

	text_length = SendMessage(hEditWnd,WM_GETTEXTLENGTH,0,0);
	pEditBuffer = (char *) malloc(text_length+1);

	if (pEditBuffer == NULL)
	  {
		extern char szTemp[];

		sprintf(szTemp, "Not enough memory to save %s.", szFileName);
		MessageBox(hWnd, szTemp, NULL, MB_OK | MB_ICONHAND);
		_lclose(hFile);
		return (FALSE);
	  }

	SendMessage(hEditWnd,WM_GETTEXT,text_length+1,
					(LPARAM) pEditBuffer);

	/*--------------------------------------------------------+
	| Set the cursor to an hourglass during the file transfer |
	+--------------------------------------------------------*/
	hSaveCursor = SetCursor(hHourGlass);

	IOStatus = _lwrite(hFile, pEditBuffer, strlen(pEditBuffer));

	_lclose(hFile);

	SetCursor(hSaveCursor);

	if (IOStatus != (int) strlen(pEditBuffer))
	{  extern char szTemp[];
		sprintf(szTemp, "Error writing to %s.", szFileName);
		MessageBox(hWnd, szTemp, NULL, MB_OK | MB_ICONHAND);
		bSuccess = FALSE;
	}
	else
	{  extern BOOL bChanges;
		bSuccess = TRUE;                /* Indicates the file was saved      */
		bChanges = FALSE;               /* Indicates changes have been saved */

      SendMessage(hEditWnd,EM_SETMODIFY,
                  (WPARAM) (UINT) FALSE, (LPARAM) 0);
 	}

	free(pEditBuffer);
	return (bSuccess);
}

/******************************************************************
* QuerySaveFile: Called when some action might lose current contents
*******************************************************************/

BOOL QuerySaveFile(
  HWND hWnd,
  short *cancel)
  {
   int Response;
   extern BOOL bChanges;

   *cancel = FALSE;

   if (bChanges)
	  {
      extern char szTemp[];
      extern char szFileName[];

		sprintf(szTemp, "Save current changes: %s", szFileName);
      Response = MessageBox(hWnd, szTemp, "EditFile",  MB_YESNOCANCEL | MB_ICONEXCLAMATION);


      if (Response == IDYES)
        {
         /*-----------------------------------------+
	      | Make sure there is a filename to save to |
	      +-----------------------------------------*/

	      while (!szFileName[0])
	        {
            extern OPENFILENAME ofn;
	         if (! GetSaveFileName ((LPOPENFILENAME)&ofn))
			     { return FALSE; }
           }
			SaveFile(hWnd);
        }
      else if (Response == IDCANCEL)
        {
         *cancel = TRUE;
         return (FALSE);
        }
     }

   return ( TRUE );
  }

/******************************************************************
* SetNewBuffer: Set new buffer for edit window
*******************************************************************/

void SetNewBuffer(
	HWND hWnd,
	char *Title)

{  extern HWND hEditWnd;
	extern BOOL bChanges;
	// HANDLE hOldBuffer;

	// hOldBuffer = (HANDLE)SendMessage(hEditWnd, EM_GETHANDLE, 0, 0L);
	// LocalFree(hOldBuffer);

	/*----------------------------------+
	| Allocates a buffer if none exists |
	+----------------------------------*/
	// if (!hNewBuffer)
	//	hNewBuffer = LocalAlloc(LMEM_MOVEABLE | LMEM_ZEROINIT, 1);

	/*-------------------------------------------+
	| Updates the buffer and displays new buffer |
	+-------------------------------------------*/
	// SendMessage(hEditWnd, EM_SETHANDLE, hNewBuffer, 0L);
	//SendMessage(hEditWnd, EM_SETHANDLE,
	//				(WPARAM) hNewBuffer, 0L); // GDR
	SetWindowText(hWnd, Title);
	SetFocus(hEditWnd);
	bChanges = FALSE;
}

/******************************************************************
* GetPrinterDC: Get hDc for current device on current output port
*   according to info in WIN.INI.
*******************************************************************/

HDC GetPrinterDC(void)

{  HDC         hDC;
	LPDEVMODE   lpDevMode = NULL;
	LPDEVNAMES  lpDevNames;
   LPSTR       lpszDriverName;
   LPSTR       lpszDeviceName;
   LPSTR       lpszPortName;

   if (!PrintDlg((LPPRINTDLG)&pd))
      return(NULL);

   if (pd.hDC)
   {  hDC = pd.hDC;
	}
	else
   {  if (!pd.hDevNames)
         return(NULL);

      lpDevNames = (LPDEVNAMES)GlobalLock(pd.hDevNames);
      lpszDriverName = (LPSTR)lpDevNames + lpDevNames->wDriverOffset;
      lpszDeviceName = (LPSTR)lpDevNames + lpDevNames->wDeviceOffset;
      lpszPortName   = (LPSTR)lpDevNames + lpDevNames->wOutputOffset;
      GlobalUnlock(pd.hDevNames);

		if (pd.hDevMode)
        lpDevMode = (LPDEVMODE)GlobalLock(pd.hDevMode);

		hDC = CreateDC(lpszDriverName, lpszDeviceName,
		               lpszPortName, lpDevMode);

      if (pd.hDevMode && lpDevMode)
        GlobalUnlock(pd.hDevMode);
   }

   if (pd.hDevNames)
   {  GlobalFree(pd.hDevNames);
		pd.hDevNames=NULL;
   }

   if (pd.hDevMode)
   {  GlobalFree(pd.hDevMode);
      pd.hDevMode=NULL;
   }
   return(hDC);
}

/******************************************************************
* AbortProc: Processes messages for the Abort Dialog box
*******************************************************************/

#if IBM_TBC
#pragma argsused
#endif
int FAR PASCAL AbortProc(
	HDC hPr,
	int Code)

{  MSG msg;

    /*---------------------------------+
    | If the abort dialog isn't up yet |
    +---------------------------------*/
   if (!hAbortDlgWnd)             
		return(TRUE);

   /*---------------------------------------------------+
   | Process messages intended for the abort dialog box |
   +---------------------------------------------------*/

	while (!bAbort && PeekMessage(&msg, NULL, 0, 0, TRUE))
   {  if (!IsDialogMessage(hAbortDlgWnd, &msg))
      {   TranslateMessage(&msg);
          DispatchMessage(&msg);
      }
	}
   return (!bAbort);
}

/******************************************************************
* AbortDlg: Processes messages for printer abort dialog box
*******************************************************************/

#if IBM_TBC
#pragma argsused
#endif
int FAR PASCAL AbortDlg(
	HWND hDlg,
	UINT msg,
	WPARAM wParam,
    LPARAM lParam)

{  switch(msg)
   {  /*-------------------------------------+
      | Watch for Cancel button, RETURN key, |
      | ESCAPE key, or SPACE BAR             |
		+-------------------------------------*/

      case WM_COMMAND:
         return (bAbort = TRUE);

      case WM_INITDIALOG:
      {  /*----------------------------------------------+
	 | Set the focus to the Cancel box of the dialog |
	 +----------------------------------------------*/
         extern char szFileName[];

			SetFocus(GetDlgItem(hDlg, IDCANCEL));
         SetDlgItemText(hDlg, IDC_FILENAME, szFileName);
	 return (TRUE);
      }
   }
   return (FALSE);
}

/******************************************************************
* About: Processes messages for "About" dialog box
*******************************************************************/

#if IBM_TBC
#pragma argsused
#endif
BOOL FAR PASCAL About(
   HWND hDlg,
   unsigned message,
	WPARAM wParam,
   LPARAM lParam)

{  switch (message)
   {  case WM_INITDIALOG:
         return (TRUE);

		case WM_COMMAND:
      { if (wParam == IDOK || wParam == IDCANCEL)
	 {  EndDialog(hDlg, TRUE);
            return (TRUE);
			}
	 return (TRUE);
      }
   }
   return (FALSE);
}

/******************************************************************
* PrintFile: Procedure to send editor buffer out to a printer.
*******************************************************************/

BOOL PrintFile ( 
   HWND hWnd)

{  extern BOOL bAbort;
   extern HWND hAbortDlgWnd;
   extern HWND hEditWnd;
   extern char szTemp[];

   int nPageSize;	   /* vert. resolution of printer device */
	int LineSpace;          /* spacing between lines          */
   int LinesPerPage;       /* lines per page                 */
   int CurrentLine;        /* current line                   */
   int LineLength;         /* line length                    */
   WORD wLines;            /* number of lines to print       */
   WORD wIndex;            /* index into lines to print      */
   char szLine[128];       /* buffer to store lines before printing */
   TEXTMETRIC TextMetric;  /* information about character size      */
   /* FARPROC lpAbortDlg; */
	//int FAR PASCAL (*lpAbortDlg)(HWND,UINT,WPARAM,LPARAM);
   
   FARPROC lpAbortProc;
   HICON hSaveCursor;
	HDC hPr;
   int Status;

   hSaveCursor = SetCursor(hHourGlass);
   hPr = GetPrinterDC();
   if (!hPr)
   {  extern char szFileName[];
      sprintf(szTemp, "Cannot print %s", szFileName);
      MessageBox(hWnd, szTemp, NULL, MB_OK | MB_ICONHAND);
      return (FALSE);
	}

	//lpAbortDlg = AbortDlg;
	lpAbortProc = (FARPROC) AbortProc;

	/*--------------------------+
	| Define the abort function |
	+--------------------------*/

	Escape(hPr, SETABORTPROC, 0, (LPSTR)  lpAbortProc, (LPSTR) NULL);

	if (Escape(hPr, STARTDOC, 14, "PrntFile text", (LPSTR) NULL) < 0)
	{  MessageBox(hWnd, "Unable to start print job", NULL, MB_OK | MB_ICONHAND);

		DeleteDC(hPr);
	}

   /*---------------------+
   | Clear the abort flag |
   +---------------------*/
   bAbort = FALSE;

	/*---------------------------------------+
   | Create the Abort dialog box (modeless) |
   +---------------------------------------*/
	DLGPROC lpAbortDlg = (DLGPROC) MakeProcInstance(About, hInst) ;

   hAbortDlgWnd = CreateDialog((HINSTANCE) hInst, "AbortDlg", hWnd, 
										 lpAbortDlg);

	FreeProcInstance ((FARPROC) lpAbortDlg);


	if (!hAbortDlgWnd)
   {  SetCursor(hSaveCursor);
      MessageBox(hWnd, "NULL Abort window handle", NULL, MB_OK | MB_ICONHAND);
      return (FALSE);
   }

   /*----------------------+
   | Now show Abort dialog |
   +----------------------*/
   ShowWindow (hAbortDlgWnd, SW_NORMAL);

   /*---------------------------+
   | Disable the main window to |
   | avoid reentrancy problems  |
   +---------------------------*/

	EnableWindow(hWnd, FALSE);
   SetCursor(hSaveCursor);

   /*---------------------------------------------------------+                                                          
   | Since you may have more than one line, you need to       |
   | compute the spacing between lines.  You can do that by   |
   | retrieving the height of the characters you are printing |
   | and advancing their height plus the recommended external |
   | leading height.                                          |
   +---------------------------------------------------------*/

	GetTextMetrics(hPr, &TextMetric);
   LineSpace = TextMetric.tmHeight + TextMetric.tmExternalLeading;

   /*------------------------------------------------------+
   | Since you may have more lines than can fit on one     |
   | page, you need to compute the number of lines you can |
   | print per page.  You can do that by retrieving the    |
   | dimensions of the page and dividing the height        |
   | by the line spacing.                                  |
   +------------------------------------------------------*/

	nPageSize = GetDeviceCaps (hPr, VERTRES);
   LinesPerPage = nPageSize / LineSpace - 1;

   /*----------------------------------------------------------+
   | You can output only one line at a time, so you need a     |
   | count of the number of lines to print.  You can retrieve  |
   | the count sending the EM_GETLINECOUNT message to the edit |
   | control.                                                  |
   +----------------------------------------------------------*/

   wLines = (WORD)SendMessage(hEditWnd, EM_GETLINECOUNT, 0, 0L);

   /*---------------------------------------------------+
   | Keep track of the current line on the current page |
   +---------------------------------------------------*/

   CurrentLine = 1;

   /*-------------------------------------------------------+
   | One way to output one line at a time is to retrieve    |
   | one line at a time from the edit control and write it  |
   | using the TextOut function.  For each line you need to |
	| advance one line space.  Also, you need to check for   |
   | the end of the page and start a new page if necessary. |    
   +-------------------------------------------------------*/

   Status = 0;
   for (wIndex = 0; wIndex < wLines; wIndex++)
   {  szLine[0] = 127;	 
      szLine[1] = 0;
      LineLength = (int)SendMessage(hEditWnd, EM_GETLINE, wIndex, (DWORD)(LPSTR)szLine);
      TextOut(hPr, 0, CurrentLine*LineSpace, (LPSTR)szLine, LineLength);
      if (++CurrentLine > LinesPerPage )
		{  CurrentLine = 1;
			Status = Escape(hPr, NEWFRAME, 0, 0L, 0L);
	 if (Status < 0 || bAbort) break;
		}
	}

	if (Status >= 0 && !bAbort)
	{  Escape(hPr, NEWFRAME, 0, 0L, 0L);
		Escape(hPr, ENDDOC, 0, 0L, 0L);
	}
	EnableWindow(hWnd, TRUE);

	/*-----------------------------+
	| Destroy the Abort dialog box |
	+-----------------------------*/

	DestroyWindow(hAbortDlgWnd);

	DeleteDC(hPr);
   return ( TRUE );
}
