
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
	/*                     DDE MODULE                      */
	/*******************************************************/

/**************************************************************/
/* Purpose: For Starting, Maintaining and Stopping a Dymanic  */
/*    Data Exchange (DDE) conversation with a CLIPS Server.   */
/*                                                            */
/* Principal Programmer(s):                                   */
/*      Christopher J. Ortiz                                  */
/*                                                            */
/* Contributing Programmer(s):                                */
/*                                                            */
/* Revision History:                                          */
/*                                                            */
/**************************************************************/

/*-------------------------------+
| Windows & System Include Files |
+-------------------------------*/

#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*---------------------+
| Editor Include Files |
+---------------------*/

#include "setup.h"
#include "ide_ids.h"
#include "ide_main.h" // GDR
#include "ide_dde.h"

/*----------------------+
| DDE Prep for a Client |
+---------------------*/

FARPROC lpDDEProc  = NULL;
DWORD   idInst     = 0;
HCONV   hConv      = NULL;
HSZ     hSZService = NULL;
HSZ     hSZItem    = NULL;

/*************************************************************
* DDECallBack : This function is an application-defined dynamic
*    data exchange (DDE) callback function that processes DDE
*    transactions sent to the function as a result of DDE
*    Management Library (DDEML) calls by other applications.
*************************************************************/

#if IBM_TBC
#pragma argsused
#endif
HDDEDATA EXPENTRY DDECallBack (
	WORD wType,
	WORD wFmt,
	HCONV hConvX,
	HSZ hsz1,
	HSZ hsz2,
	HDDEDATA hData,
	DWORD dwData1,
	DWORD dwData2 )
  {
	switch ( wType )
	  {
		/*----------------------------------------------+
		| Enable DDE Menu Items when CLIPS is available |
		+----------------------------------------------*/

		case XTYP_REGISTER:
		  {
			extern HWND hwnd;
			HMENU hMenu = GetMenu (hwnd);

			EnableMenuItem(hMenu, IDM_EDIT_COMPLETE, MF_BYCOMMAND|MF_ENABLED);
			EnableMenuItem(hMenu, IDM_HELP_COMPLETE, MF_BYCOMMAND|MF_ENABLED);
			EnableMenuItem(hMenu, IDM_BUFFER_LOAD,   MF_BYCOMMAND|MF_ENABLED);
			EnableMenuItem(hMenu, IDM_BUFFER_LBUF,   MF_BYCOMMAND|MF_ENABLED);
			EnableMenuItem(hMenu, IDM_BUFFER_BATCH,  MF_BYCOMMAND|MF_ENABLED);
			break;
		  }

		/*-------------------------------------------------+
		| Disable DDE Menu Items when CLIPS is unavailable |
		+-------------------------------------------------*/

		case XTYP_UNREGISTER:
		  {
			extern HWND hwnd;
			HMENU hMenu = GetMenu (hwnd);

			EnableMenuItem(hMenu, IDM_HELP_COMPLETE, MF_BYCOMMAND|MF_GRAYED);
			EnableMenuItem(hMenu, IDM_EDIT_COMPLETE, MF_BYCOMMAND|MF_GRAYED);
			EnableMenuItem(hMenu, IDM_BUFFER_LOAD,   MF_BYCOMMAND|MF_GRAYED);
			EnableMenuItem(hMenu, IDM_BUFFER_LBUF,   MF_BYCOMMAND|MF_GRAYED);
			EnableMenuItem(hMenu, IDM_BUFFER_BATCH,  MF_BYCOMMAND|MF_GRAYED);
			break;
		  }

		case XTYP_DISCONNECT:
		  {
			extern HCONV hConv;
			hConv = NULL;
			break;
		  }
	  }

	return ((HDDEDATA) NULL);
  }

/*******************************************************************
* StartUpDDE: The function registers an application with the DDEML,
*   creates all strings, registers the service names that a DDE
*   server supports.
******************************************************************/

BOOL StartUpDDE ( HWND hWnd )
  {
	extern FARPROC lpDDEProc;
	extern HSZ hSZService;
	extern HSZ hSZItem;
	extern DWORD idInst;
	extern HCONV hConv;

	HMENU hMenu = GetMenu ( hWnd );
	BOOL RtnValue = TRUE;
	UINT Flags = ( MF_BYCOMMAND | MF_ENABLED );

	/*--------------------------------+
	| Setup Client Editor Application |
	+--------------------------------*/

	lpDDEProc = (FARPROC) DDECallBack;

	if ( DdeInitialize ((LPDWORD) &idInst,
							  (PFNCALLBACK)lpDDEProc,
							  APPCMD_CLIENTONLY,0L) )
	  {
		Flags = ( MF_BYCOMMAND | MF_GRAYED);
		RtnValue = FALSE;
		MessageBeep ( 0 );
		MessageBox (NULL,"Can not Initialize DDEML",
		"DDEML ERROR", MB_ICONSTOP | MB_TASKMODAL );
	  }

	else
	  {
		/*----------------------------+
		| Check if CLIPS is available |
		+----------------------------*/

		HSZ hSZTopic = DdeCreateStringHandle ( idInst, "LOAD",    CP_WINANSI );
		hSZItem      = DdeCreateStringHandle ( idInst, "DDEData", CP_WINANSI );
		hSZService   = DdeCreateStringHandle ( idInst, "CLIPS",   CP_WINANSI );

		hConv = DdeConnect ( idInst, hSZService, hSZTopic, (PCONVCONTEXT)NULL);
		if ( hConv == NULL )
		  {
			Flags = ( MF_BYCOMMAND | MF_GRAYED);
			RtnValue = FALSE;
		  }
		else
		  { DdeDisconnect ( hConv ); }
		DdeFreeStringHandle ( idInst, hSZTopic );
	  }

	EnableMenuItem( hMenu, IDM_EDIT_COMPLETE, Flags);
	EnableMenuItem( hMenu, IDM_HELP_COMPLETE, Flags);
	EnableMenuItem( hMenu, IDM_BUFFER_LOAD,   Flags);
	EnableMenuItem( hMenu, IDM_BUFFER_LBUF,   Flags);
	EnableMenuItem( hMenu, IDM_BUFFER_BATCH,  Flags);

	return ( RtnValue );
  }

/************************************************************
* ShutDownDDE: This function terminates a conversation,
*    invalidates the given conversation handle, and frees
*    string handles in the calling application.
*************************************************************/

BOOL ShutDownDDE ( void )
  {
	extern DWORD idInst;
	if ( hConv != NULL)
	  {
		DdeDisconnect ( hConv );
		hConv = NULL;
	  }

	DdeFreeStringHandle ( idInst, hSZService );
	DdeFreeStringHandle ( idInst, hSZItem );
	return (TRUE);
  }

/***************************************************************
* FreeDDE: This function frees all DDEML resources associated
*   with the calling application and frees the specified function
*   from the data segment bound to it by the StartUpDDE function.
***************************************************************/

void FreeDDE ( void )
  {
	extern FARPROC lpDDEProc;
	extern HCONV hConv;
	extern HSZ hSZService;
	extern HSZ hSZItem;
	extern DWORD idInst;

	if ( hConv != NULL)
	  {
		DdeDisconnect ( hConv );
		hConv = NULL;
	  }

	DdeUninitialize ( idInst );
  }

/***************************************************************
* MessageDDE: Support for the four DDEML Conversations.
*    Load Entire Buffer, Load Only Selection, Batch Only
*    Selection, and Get Completed Command.
***************************************************************/

BOOL MessageDDE ( WPARAM wParam )
  {
	switch ( wParam )
	  {
		case IDM_BUFFER_BATCH:
		case IDM_BUFFER_LOAD:
		case IDM_BUFFER_LBUF:
		  {
			extern HSZ hSZService, hSZItem;
			extern HCONV hConv;
			extern DWORD idInst;
			extern HWND hEditWnd;
			HANDLE hTemp;
			HSZ hSZTopic;
			DWORD dwResult;
			HDDEDATA hData;
			DWORD sel;
			int len;
			WORD start;
			char *Data;
			int text_length; // GDR

			/*--------------------------+
			| Create conversation Topic |
			+--------------------------*/

			if ( wParam == IDM_BUFFER_BATCH )
			  hSZTopic = DdeCreateStringHandle( idInst, "BATCH", CP_WINANSI);
			else
			  hSZTopic = DdeCreateStringHandle( idInst, "LOAD", CP_WINANSI);

			/*---------------------+
			| Selected entire File |
			+---------------------*/

			if ( wParam == IDM_BUFFER_LBUF )
			  SendMessage ( hEditWnd, EM_SETSEL, 0, -1);

			/*----------------------------------------+
			| Find the area of text that was selected |
			+----------------------------------------*/

			sel = SendMessage(hEditWnd,EM_GETSEL,0,0L);
			len = HIWORD(sel)- LOWORD(sel);
			start = LOWORD (sel);

			/*-------------------------------+
			| Start conversation with server |
			+-------------------------------*/

			if ( hConv != NULL ) DdeDisconnect ( hConv );
			hConv = DdeConnect ( idInst, hSZService, hSZTopic, (PCONVCONTEXT)NULL);
			if ( hConv == NULL )
			  {
				DdeFreeStringHandle ( idInst, hSZTopic );
				return ( FALSE );
			  }

			/*----------------------------+
			| Find Data that was Selected |
			+----------------------------*/

			// Begin GDR
			// hEditHandle = (HLOCAL) SendMessage ( hEditWnd, EM_GETHANDLE, 0, 0);
			// Data = (char *) LocalLock ( hEditHandle );
			text_length = SendMessage(hEditWnd,WM_GETTEXTLENGTH,0,0);
			Data = (char *) malloc(text_length+1);
			if (Data == NULL )
			  {
				MessageBeep ( 0 );
				MessageBox (NULL,"Can not complete operation",
					"Memory Low", MB_ICONSTOP | MB_TASKMODAL );
				DdeDisconnect( hConv );
				DdeFreeStringHandle ( idInst, hSZTopic );
				return(FALSE);
			  }

			SendMessage(hEditWnd,WM_GETTEXT,text_length+1,
							(LPARAM) Data);
			// End GDR

			/*------------------------------------------+
			| Create Packet Data and Copy Selected Data |
			+------------------------------------------*/

			hTemp = GlobalAlloc (GMEM_MOVEABLE | GMEM_ZEROINIT, len + 1 );
			if ( hTemp == NULL )
			  {
				MessageBeep ( 0 );
				MessageBox (NULL,"Can not complete operation",
								"Memory Low", MB_ICONSTOP | MB_TASKMODAL );
				free(Data); // GDR
				DdeDisconnect( hConv );
				DdeFreeStringHandle ( idInst, hSZTopic );
				return(FALSE);
			  }
			{
			BYTE *Temp;
			int x;

			Temp = (BYTE *) GlobalLock ( hTemp );

			strncpy ( (char *) Temp, Data+start, len );

			for (x=0; x< len; x++ )
			  if ( Temp[x] == '\r' )
				 Temp[x] = ' ';
			Temp[len] = '\0';

			hData = DdeCreateDataHandle ( idInst, Temp, len+1 ,
						0L, hSZItem, CF_TEXT, 0 );
			if ( hData == NULL )
			  {
				free(Data); // GDR
				DdeDisconnect( hConv );
				DdeFreeStringHandle ( idInst, hSZTopic );
				GlobalUnlock ( hTemp );
				GlobalFree   ( hTemp );
				return ( FALSE );
			  }

			/*-------------------------------------------------+
			| Pass DDE Data Via XTYP_POKE DdeClientTransaction |
			+-------------------------------------------------*/

			DdeClientTransaction ((LPBYTE)hData, -1, hConv, hSZItem, CF_TEXT,
							 XTYP_POKE, 1000, &dwResult );

			if ( DdeGetLastError ( idInst ) == DMLERR_BUSY )
			  {
				MessageBeep ( 0 );
				MessageBox (NULL,"Can not complete operation",
						  "CLIPS Running.", MB_ICONSTOP | MB_TASKMODAL );
				free(Data); // GDR
				DdeDisconnect( hConv );
				DdeFreeStringHandle ( idInst, hSZTopic );
				GlobalUnlock ( hTemp );
				GlobalFree   ( hTemp );
				return(FALSE);
			  }

			GlobalUnlock ( hTemp );
			GlobalFree   ( hTemp );
			}

			// LocalUnlock ( hEditHandle);
			free(Data); // GDR
			DdeDisconnect( hConv );
			DdeFreeStringHandle ( idInst, hSZTopic );
			break;
		  }

		case IDM_HELP_COMPLETE:
		case IDM_EDIT_COMPLETE:
		  {
			extern DWORD idInst;
			extern HCONV hConv;
			extern HSZ hSZService, hSZItem;
			extern HWND hEditWnd;
			HSZ hSZTopic;
			DWORD dwResult;
			HDDEDATA hData;

			/*-------------------------------+
			| Start conversation with server |
			+-------------------------------*/

			hSZTopic = DdeCreateStringHandle ( idInst, "COMPLETE", CP_WINANSI );
			if ( hConv != NULL ) DdeDisconnect ( hConv );
			hConv = DdeConnect ( idInst, hSZService, hSZTopic, (PCONVCONTEXT)NULL);
			if ( hConv == NULL )
			  {
				DdeFreeStringHandle ( idInst, hSZTopic );
				return ( FALSE );
			  }

			/*--------------------+
			| Find and Send Token |
			+--------------------*/

			{
			// HANDLE hEditHandle;
			int text_length; // GDR
			DWORD sel = SendMessage(hEditWnd,EM_GETSEL,0,0L);
			WORD start = LOWORD (sel);
			WORD end;
			int len;
			BYTE *buffer;
			char *EditData;

			/*-------------------------+
			| Find Token to be matched |
			+-------------------------*/

			text_length = SendMessage(hEditWnd,WM_GETTEXTLENGTH,0,0);
			EditData = (char *) malloc(text_length+1);
			if ( EditData == NULL )
			  {
				DdeDisconnect(hConv);
				DdeFreeStringHandle ( idInst, hSZTopic );
				return ( FALSE );
			  }

			SendMessage(hEditWnd,WM_GETTEXT,text_length+1,(LPARAM) EditData);
			// hEditHandle = (HLOCAL) SendMessage ( hEditWnd, EM_GETHANDLE, 0, 0);
			// EditData = (char *) LocalLock ( hEditHandle );

			while (start > 0 && !(isspace(EditData[start-1])))
			  {start --;}
			end = start;

			while (!(isspace(EditData[end])))
			  { end ++; }

			len = (end - start)+1;
			buffer = (BYTE *) malloc ( len + 1);
			if (buffer == NULL )
			  {
				MessageBeep ( 0 );
				MessageBox (NULL,"Can not complete operation",
						 "Memory Low", MB_ICONSTOP | MB_TASKMODAL );
				free(EditData);
				DdeDisconnect(hConv);
				DdeFreeStringHandle ( idInst, hSZTopic );
				return(FALSE);
			  }
			strncpy ( (char *) buffer, EditData+start, len );

			/*--------------------------+
			| Create Data Packet & Send |
			+--------------------------*/

			hData = DdeCreateDataHandle ( idInst, buffer,
			  (DWORD) (len)+1, 0, hSZItem, CF_TEXT, 0 );
			if ( hData == NULL )
			  {
				DdeDisconnect(hConv);
				DdeFreeStringHandle ( idInst, hSZTopic );
				free(buffer);
				free(EditData);
				return ( FALSE );
			  }

			DdeClientTransaction ((LPBYTE)hData, -1, hConv, hSZItem, CF_TEXT, XTYP_POKE, 1000, &dwResult);
			free ( buffer );
			// LocalUnlock ( hEditHandle );
			free(EditData);
			// Begin GDR
			SendMessage ( hEditWnd, EM_SETSEL, start, end);
			// End GDR
			}

			/*---------------------------+
			| Retrieve and replace token |
			+---------------------------*/
			{
			char *buffer;

			/*----------------+
			| Wait for Result |
			+----------------*/

			hData = NULL;
			while ( hData == FALSE )
			  {
				hData = DdeClientTransaction ( NULL, 90, hConv,
					 hSZItem, CF_TEXT, XTYP_REQUEST, 100, &dwResult );
			  }

			/*------------+
			| Copy Result |
			+------------*/

			SetFocus ( hEditWnd );
			buffer = (char*)DdeAccessData (hData, NULL);
			if ( strcmp ( buffer, "\0" ) != 0 )
			  SendMessage ( hEditWnd, EM_REPLACESEL, 0,
					 (LPARAM)((LPSTR) buffer));
			DdeUnaccessData (hData);
			}

			/*----------------------+
			| ShutDown Conversation |
			+----------------------*/

			DdeDisconnect(hConv);
			DdeFreeStringHandle ( idInst, hSZTopic );
			break;
		  }
	  }
	return ( TRUE );
  }
