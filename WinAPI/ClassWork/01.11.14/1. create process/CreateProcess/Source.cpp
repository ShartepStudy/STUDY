#include <windows.h>
#include "resource.h"

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

// о процессах и потоках:
// http://msdn.microsoft.com/ru-ru/library/windows/desktop/ms684841(v=vs.85).aspx

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

TCHAR *path_to_exe; // путь к исполняемому файлу http://stackoverflow.com/questions/11339186/createprocess-fails-with-an-access-violation
TCHAR *arguments; // строка с аргументами
TCHAR *error_description; // строка с описанием ошибки 

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

STARTUPINFO si; // http://msdn.microsoft.com/en-us/library/windows/desktop/ms686331(v=vs.85).aspx
// Specifies the window station, desktop, standard handles, and appearance of the main window for a process at creation time.

PROCESS_INFORMATION pi; // http://msdn.microsoft.com/en-us/library/windows/desktop/ms684873(v=vs.85).aspx
// Contains information about a newly created process and its primary thread.

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{

	switch (uMessage)
	{
	case WM_INITDIALOG:

		// STARTUPINFO fields

		/* typedef struct _STARTUPINFO {
		DWORD  cb; // the size of the structure, in bytes.
		LPTSTR lpReserved; // reserved; must be NULL.
		LPTSTR lpDesktop; // the name of the desktop.
		LPTSTR lpTitle; // for console processes, this is the title displayed in the title bar. This parameter must be NULL for GUI.
		DWORD  dwX; // it works great only for console apps :)
		DWORD  dwY; 
		DWORD  dwXSize; 
		DWORD  dwYSize;
		DWORD  dwXCountChars;
		DWORD  dwYCountChars;
		DWORD  dwFillAttribute;
		DWORD  dwFlags; // A bitfield that determines whether certain STARTUPINFO members are used when the process creates a window.
		WORD   wShowWindow; // if dwFlags specifies STARTF_USESHOWWINDOW, this member can be any of the values that can be specified in the nCmdShow parameter for the ShowWindow function.
		WORD   cbReserved2;
		LPBYTE lpReserved2;
		HANDLE hStdInput;
		HANDLE hStdOutput;
		HANDLE hStdError;
		} STARTUPINFO, *LPSTARTUPINFO; */

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		si.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE | STARTF_USESHOWWINDOW;
		si.dwX = 10;
		si.dwY = 10;
		si.dwXSize = 500;
		si.dwYSize = 250;
		// si.dwXCountChars = 80;
		// si.dwYCountChars = 25;
		si.wShowWindow = SW_SHOW; // SW_MINIMIZE, SW_HIDE

		////////////////////////////////////////////////////////////////

		// PROCESS_INFORMATION fields

		/* typedef struct _PROCESS_INFORMATION {
			HANDLE hProcess; // A handle to the newly created process. The handle is used to specify the process in all functions that perform operations on the process object.
			HANDLE hThread; // A handle to the primary thread of the newly created process. The handle is used to specify the thread in all functions that perform operations on the thread object.
			DWORD  dwProcessId; // A value that can be used to identify a process. The value is valid from the time the process is created until all handles to the process are closed and the process object is freed; at this point, the identifier may be reused.
			DWORD  dwThreadId; // A value that can be used to identify a thread. The value is valid from the time the thread is created until all handles to the thread are closed and the thread object is freed; at this point, the identifier may be reused.
		} PROCESS_INFORMATION, *LPPROCESS_INFORMATION; */

		ZeroMemory(&pi, sizeof(pi));

		return TRUE;

	case WM_COMMAND: // нажатие на кнопку
		path_to_exe = new TCHAR[256]; // The Unicode version of this function, CreateProcessW, can modify the contents of this string. Therefore, this parameter cannot be a pointer to read-only memory (such as a const variable or a literal string). If this parameter is a constant string, the function may cause an access violation.
		arguments = new TCHAR[256];
		error_description = new TCHAR[256];

		lstrcpy(path_to_exe, L"C:\\Windows\\System32\\cmd.exe"); // also try notepad.exe or calc.exe
		lstrcpy(arguments, L"some arguments for console command window");

		// http://msdn.microsoft.com/en-us/library/windows/desktop/ms682512(v=vs.85).aspx

		/* BOOL WINAPI CreateProcess( // If the function succeeds, the return value is nonzero.
			_In_opt_     LPCTSTR lpApplicationName, // The string can specify the full path and file name of the module to execute or it can specify a partial name. In the case of a partial name, the function uses the current drive and current directory to complete the specification. The function will not use the search path. This parameter must include the file name extension; no default extension is assumed. It means, you must use L"C:\\Windows\\System32\\cmd.exe" instead L"cmd.exe" or even L"cmd"
			_Inout_opt_  LPTSTR lpCommandLine, // The lpCommandLine parameter can be NULL. In that case, the function uses the string pointed to by lpApplicationName as the command line. If both lpApplicationName and lpCommandLine are non-NULL, the null-terminated string pointed to by lpApplicationName specifies the module to execute, and the null-terminated string pointed to by lpCommandLine specifies the command line.
			_In_opt_     LPSECURITY_ATTRIBUTES lpProcessAttributes, // http://stackoverflow.com/questions/3332584/how-do-you-use-security-attributes-with-createprocess
			_In_opt_     LPSECURITY_ATTRIBUTES lpThreadAttributes,
			_In_         BOOL bInheritHandles, // http://msdn.microsoft.com/en-us/library/windows/desktop/ms724466(v=vs.85).aspx
			_In_         DWORD dwCreationFlags, // http://msdn.microsoft.com/en-us/library/windows/desktop/ms684863.aspx This parameter also controls the new process's priority class, which is used to determine the scheduling priorities of the process's threads
			_In_opt_     LPVOID lpEnvironment, // http://stackoverflow.com/questions/4206190/win32-createprocess-when-is-create-unicode-environment-really-needed
			_In_opt_     LPCTSTR lpCurrentDirectory, // If this parameter is NULL, the new process will have the same current drive and directory as the calling process
			_In_         LPSTARTUPINFO lpStartupInfo,
			_Out_        LPPROCESS_INFORMATION lpProcessInformation
			); */

		
		if (!CreateProcess(path_to_exe, arguments, 0, 0, false, 0, 0, 0, &si, &pi))
		{
			wsprintf(error_description, L"CreateProcess failed! :(\nError number: %d (use error lookup)", GetLastError());
			MessageBox(hWnd, error_description, L"Error!", MB_OK);
		}
		
		delete[]path_to_exe;
		delete[]arguments;

		return TRUE;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}

	return FALSE;
}