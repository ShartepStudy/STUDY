#include "header.h"

class CMyDialog
{
public:
	CMyDialog();
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CMyDialog* ptr;
	void OnInitDialog(HWND h);
	HWND hDialog;
	void OnCommand(WPARAM wp, LPARAM lp);
	void OnTimer();
	Clock clk;
};
