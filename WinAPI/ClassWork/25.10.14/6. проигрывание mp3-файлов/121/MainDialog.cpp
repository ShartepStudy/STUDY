#include <windows.h>
#include <tchar.h>

#include "bass.h"
#pragma comment (lib, "bass.lib")

// �������� ������� ���������, ������� ���������� ���������� ���������
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

// �������� ������ ����
TCHAR szClassWindow[] = TEXT("��������������� MP3");

////////////////////// ���������� ������
HSTREAM stream;
////////////////////////////////////////

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASSEX wcl;

	wcl.cbSize = sizeof(wcl);	// ������ ��������� WNDCLASSEX
	wcl.style = CS_HREDRAW | CS_VREDRAW;	// CS (Class Style) - ����� ������ ����
	wcl.lpfnWndProc = WindowProc;	// ����� ������� ���������
	wcl.cbClsExtra = 0;		// ������������ Windows 
	wcl.cbWndExtra  = 0; 	// ������������ Windows 
	wcl.hInstance = hInst;	// ���������� ������� ����������
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// �������� ����������� ������
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);	// �������� ������������ �������	
	wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);	// ���������� ���� ����� ������
	wcl.lpszMenuName = NULL;	// ���������� �� �������� ����
	wcl.lpszClassName = szClassWindow;	// ��� ������ ����
	wcl.hIconSm = NULL;	// ���������� ��������� ������ ��� ����� � ������� ����

	if (!RegisterClassEx(&wcl))
		return 0; // ��� ��������� ����������� - �����

	HWND hWnd = CreateWindowEx(
		0,		// ����������� ����� ����
		szClassWindow,	//��� ������ ����
		szClassWindow, // ��������� ����
		WS_OVERLAPPEDWINDOW,				// ����� ����
		// ���������, �����, ����������� ������ �������, ��������� ����, ������ ������������ � ���������� ����
		40,	// �-���������� ������ �������� ���� ����
		40,	// y-���������� ������ �������� ���� ����
		400,	// ������ ����
		200,	// ������ ����
		NULL,			// ���������� ������������� ����
		NULL,			// ���������� ���� ����
		hInst,		// ������������� ����������, ���������� ����
		NULL);		// ��������� �� ������� ������ ����������

	// 4. ����������� ����
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd); // ����������� ����

	/////////////////////////////////////////////////////////

	if (HIWORD(BASS_GetVersion())!=BASSVERSION) {
		MessageBox (NULL, "������ ������ BASS.", NULL, 0);
		return 1;
	}
	if (!BASS_Init (-1, 22050, BASS_DEVICE_3D , 0, NULL)) {
		MessageBox (NULL, "�� ������� ���������������� BASS.", NULL, 0);
		return 1;
	}

	/////////////////////////////////////////////////////////

	char filename[] = "1.mp3";
	/* ������� ��������� ����, ��������� � ������ */
	stream = BASS_StreamCreateFile(FALSE, filename, 0, 0, 0); 
	if (!stream) {
		/* ...��������� ������... */
		return 1;
	}

	/* ������������� ���� */
	BASS_ChannelPlay(stream,TRUE);

	/////////////////////////////////////////////////////////

	// 5. ������ ����� ��������� ���������
	MSG lpMsg;
	while(GetMessage(&lpMsg, NULL, 0, 0)) // ��������� ���������� ��������� �� ������� ���������
	{
		TranslateMessage(&lpMsg);	// ���������� ���������
		DispatchMessage(&lpMsg);	// ��������������� ���������
	}
	return lpMsg.wParam;
}	

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch(uMessage)
	{
	case WM_DESTROY: // ��������� � ���������� ���������
		PostQuitMessage(0);
		break;
		/////////////////////////////////
	case WM_KEYDOWN:
		BASS_ChannelStop(stream);
		BASS_StreamFree(stream); 
		BASS_Free();
		break;
		/////////////////////////////////
	default:
		// ��� ���������, ������� �� �������������� � ������ ������� ������� 
		// ������������ ������� Windows �� ��������� �� ���������
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}