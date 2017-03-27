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
   /*                   BALANCE MODULE                    */
   /*******************************************************/

/**************************************************************/
/* Purpose: Handle the Balance Command within an Edit Window  */
/*                                                            */
/* Principal Programmer(s):                                   */
/*      Christopher J. Ortiz                                  */
/*      Gary Riley                                            */
/*                                                            */
/* Contributing Programmer(s):                                */
/*                                                            */
/* Revision History:                                          */
/*                                                            */
/**************************************************************/

#include <windows.h>
#include <stdlib.h> // GDR

#include "ide_bal.h"
#include "ide_main.h" // GDR

static void BalanceIt ( int, int, int, int, char*, DWORD, HWND );

/*******************************************************
* Balance: Handle Balance Command
********************************************************/
void Balance (
   HWND hWindow)

{  DWORD sel;
	int left_middle, right_middle, text_length;
	// HLOCAL textHandle; // GDR
	char *text_ptr;

	/*-----------------------------------------------------------+
	| Get information about the current selection to be balanced |
	+-----------------------------------------------------------*/

	sel = SendMessage ( hWindow, EM_GETSEL, 0, 0 );
	left_middle = (int)LOWORD(sel);
	right_middle= (int)HIWORD(sel);
	// Begin GDR
	// textHandle  = (HLOCAL) SendMessage(hWindow, EM_GETHANDLE, 0, 0);
	// text_length = LocalSize ( textHandle );
	// text_ptr = LocalLock ( textHandle);
	text_length = SendMessage(hWindow,WM_GETTEXTLENGTH,
									  0,0);
	text_ptr = (char *) malloc(text_length+1);
	if (text_ptr == NULL )
	  {
		MessageBeep ( 0 );
		MessageBox (hWindow,"Can not complete operation",
					"Memory Low", MB_ICONSTOP | MB_TASKMODAL );
		return;
	  }

	SendMessage(hWindow,WM_GETTEXT,text_length+1,
					(LPARAM) text_ptr);
	// End GDR

	/*----------------------------------+
	| If the selection is empty then... |
   +----------------------------------*/

	if ( left_middle == right_middle )
	{  /*---------------------------------------------+
		| if the '(' is to the right of the cursor,    |
		| then all balancing should occur to the right.|
		+---------------------------------------------*/
		if ((text_ptr[left_middle] == '(') && (left_middle < text_length))
      {  BalanceIt ( left_middle-1, left_middle+1, 1, 0,
	 text_ptr, text_length, hWindow );
      }
      /*-------------------------------------------+
      |Else if ')' is to the left of the cursor,   |
		|then all balancing should occur to the left |
		+-------------------------------------------*/
		else if ((left_middle > 0) ? (text_ptr[left_middle-1] == ')'): 0)
		{  BalanceIt ( left_middle-2, right_middle, // GDR
							0, -1, text_ptr, text_length, hWindow );
      }
      /*------------------------------------------------------+
      |Else balancing occurs to the left and right of cursor |
      +------------------------------------------------------*/
      else
      {  BalanceIt (left_middle-1, right_middle, 0, 0,
	 text_ptr, text_length, hWindow );
      }
   }
	else
   {  /*----------------------------------------------+
      | Determine the number of right parentheses ')' |
      |  that need to be balanced from the left side. |
      +----------------------------------------------*/
      int count, i;
      int left_count, right_count;

      count = 0;
      left_count = 0;

		for ( i = left_middle; i < right_middle; i++ )
      {  if (text_ptr[i] == '(') count ++;
	 else if ( text_ptr[i] == ')') count --;
         if ( count < left_count) left_count = count;
      }

      /*----------------------------------------------+ 
      | Determine the number of right parentheses ')' |
      |  that need to be balanced from the left side. |
      +----------------------------------------------*/
      count = 0;
		right_count = 0;

      for ( i = right_middle-1; i >= left_middle; i--)
      {  if ( text_ptr[i] == '(') count++;
	 else if ( text_ptr[i] == ')') count--;
         if ( count > right_count) right_count = count;
      }

      /*--------------------------------------------+
      | Balance to the left and right of the cursor |
      +--------------------------------------------*/
		BalanceIt ( left_middle-1, right_middle, left_count, right_count,
	 text_ptr, text_length, hWindow );
	}
	// Begin GDR
	free(text_ptr);
	// LocalUnlock ( textHandle );
   // End GDR
}

/*******************************************************
* BalanceIt: Balances a selection of text by extending 
*    extending it to the left and right until the      
*    number of left and right parentheses is balanced. 
********************************************************/
static void BalanceIt ( 
   int left_middle, 
   int right_middle,
   int left_count, 
   int right_count,
   char *text_ptr,
   DWORD text_length,
   HWND hWindow)

{  /*-----------------------------+
   | Balance the left side of the |
   | text by moving left and up   |
   +-----------------------------*/
   while ( left_count <= 0 )
   {  if ( left_middle < 0 )
      {  MessageBeep(0);
         return;
      }

      if (text_ptr[left_middle] == '(') left_count++;
      else if (text_ptr[left_middle] == ')') left_count--;

      left_middle--;
   }

   /*-------------------------------+
   | Balance the right side of the  |
   | text by moving right and down. |
   +-------------------------------*/
   while ( right_count >= 0)
   {  if( right_middle > text_length )
      { MessageBeep(0);
        return;
      }

      if (text_ptr[right_middle] == '(') right_count ++;
      else if ( text_ptr[right_middle] == ')') right_count --;

      right_middle++;
   }

   /*-------------------------------------------+
	| Set the current selection to balanced text |
	+-------------------------------------------*/
	// Begin GDR
	SendMessage(hWindow,EM_SETSEL,
					left_middle+1,right_middle);
	// End GDR

	/*-----------------------------------+
	| Make sure the selection is visible |
	+-----------------------------------*/
	SendMessage (hWindow, EM_LINESCROLL, 0,
      MAKELPARAM (0, -(GetScrollPos ( hWindow, SB_HORZ))));
}