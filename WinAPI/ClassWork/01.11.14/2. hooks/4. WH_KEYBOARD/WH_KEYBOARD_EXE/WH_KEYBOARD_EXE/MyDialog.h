
#include "header.h"

class CMyDialog
{
public:
	CMyDialog();
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CMyDialog* ptr;
	void OnInitDialog(HWND h);
	void OnCommand(WPARAM wp, LPARAM lp);
	HWND hDialog, hButton1, hButton2;
	void OnKeyStroke(WPARAM wp, LPARAM lp);
};
