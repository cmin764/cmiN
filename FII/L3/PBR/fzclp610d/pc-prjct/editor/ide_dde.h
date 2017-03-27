#include <ddeml.h>
#include <dde.h>

BOOL StartUpDDE  ( HWND );
BOOL ShutDownDDE ( void );
void FreeDDE     ( void );
BOOL MessageDDE  ( WPARAM );
HDDEDATA EXPENTRY DDECallBack ( WORD, WORD, HCONV, HSZ, HSZ, HDDEDATA, DWORD, DWORD );
