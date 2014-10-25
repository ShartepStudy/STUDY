
#include "header.h"

class CMyDialog
{
public:
	CMyDialog(void);
public:
	~CMyDialog(void);
	static BOOL CALLBACK DlgProc(HWND hWnd,UINT mes,WPARAM wp,LPARAM lp);
	static CMyDialog*ptr;
	void OnInitDialog(HWND h);
	void OnFont();
	void SetTimeDate();
	HWND hDialog,hEdit;
	LOGFONT lf;
	HFONT hFont;
	COLORREF color;
};
