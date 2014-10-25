
#include "header.h"

class CStatusBarDlg
{
public:
	CStatusBarDlg(void);
public:
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CStatusBarDlg* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	void Cls_OnVScroll(HWND hwnd, HWND hwndCtl, UINT code, int pos);
	void Cls_OnSize(HWND hwnd, UINT state, int cx, int cy);
	HWND hDialog, hSpin, hCheck1, hCheck2, hStatus, hEdit;
	HICON hIcon;
};