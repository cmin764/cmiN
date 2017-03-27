
int PASCAL WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
long FAR PASCAL MainWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL FAR PASCAL About(HWND, unsigned, WPARAM, LPARAM);
BOOL SaveFile(HWND);
BOOL QuerySaveFile(HWND,short *);
void SetNewBuffer(HWND, // HANDLE,
                  char *);
HDC GetPrinterDC();
int FAR PASCAL AbortProc(HDC, int);
int FAR PASCAL AbortDlg(HWND, unsigned, WPARAM, LPARAM);
HDC GetPrinterDC(void);
long FAR PASCAL MainWndProc( HWND, UINT, WPARAM, LPARAM);
BOOL PrintFile ( HWND );