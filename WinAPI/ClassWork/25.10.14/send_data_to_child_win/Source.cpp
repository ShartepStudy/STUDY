#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
using namespace std;

#define MAX_LOADSTRING 256

#define ID_PARENT_EDIT 1001
#define ID_SHOW_CHILD 1002
#define ID_SEND_MESSAGE_TO_CHILD 1003
#define ID_CHILD_EDIT 1004

HINSTANCE hParentInst, hChildInst;
HWND hParent, hChild;

TCHAR szParentTitle[MAX_LOADSTRING] = L"Parent Window Caption";
TCHAR szChildTitle[MAX_LOADSTRING] = L"Child Window Caption";
TCHAR szParentWindowClass[MAX_LOADSTRING] = L"ParentWindowClass";
TCHAR szChildWindowClass[MAX_LOADSTRING] = L"ChildWindowClass";

ATOM				ParentRegisterClass(HINSTANCE hInstance);
BOOL				ParentInitInstance(HINSTANCE, int);
LRESULT CALLBACK	ParentWndProc(HWND, UINT, WPARAM, LPARAM);

ATOM				ChildRegisterClass(HINSTANCE hInstance);
BOOL				ChildInitInstance(HINSTANCE, int);
LRESULT CALLBACK	ChildWndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow) {
  MSG msg;

  ParentRegisterClass(hInstance);
  ChildRegisterClass(hInstance);

  // Perform application initialization:
  if (!ParentInitInstance(hInstance, nCmdShow)) return FALSE;

  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return (int)msg.wParam;
}

ATOM ParentRegisterClass(HINSTANCE hInstance) {
  WNDCLASSEX wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = ParentWndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(hInstance, 0);
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = CreateSolidBrush(RGB(255, 0, 0));
  wcex.lpszMenuName = NULL;
  wcex.lpszClassName = szParentWindowClass;
  wcex.hIconSm = NULL;

  return RegisterClassEx(&wcex);
}

ATOM ChildRegisterClass(HINSTANCE hInstance) {
  WNDCLASSEX wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = ChildWndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(hInstance, 0);
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = CreateSolidBrush(RGB(0, 255, 0));
  wcex.lpszMenuName = NULL;
  wcex.lpszClassName = szChildWindowClass;
  wcex.hIconSm = NULL;

  return RegisterClassEx(&wcex);
}

BOOL ParentInitInstance(HINSTANCE hInstance, int nCmdShow) {

  hParentInst = hInstance;

  hParent = CreateWindow(szParentWindowClass, szParentTitle, WS_OVERLAPPEDWINDOW,
                         50, 50, 400, 180, NULL, NULL, hInstance, NULL);

  if (!hParent) return FALSE;

  CreateWindow(L"Edit", L"Напишите здесь что-нибудь", WS_CHILD | WS_VISIBLE, 20, 20, 345, 18, hParent, (HMENU)ID_PARENT_EDIT, hInstance, NULL);
  CreateWindow(L"Button", L"Создать дочернее окно", WS_CHILD | WS_VISIBLE, 20, 50, 345, 30, hParent, (HMENU)ID_SHOW_CHILD, hInstance, NULL);
  CreateWindow(L"Button", L"Отправить сообщение", WS_CHILD | WS_VISIBLE, 20, 90, 345, 30, hParent, (HMENU)ID_SEND_MESSAGE_TO_CHILD, hInstance, NULL);


  ShowWindow(hParent, nCmdShow);
  UpdateWindow(hParent);

  return TRUE;
}

BOOL ChildInitInstance(HINSTANCE hInstance, int nCmdShow) {
  hChildInst = hInstance;

  hChild = CreateWindow(szChildWindowClass, szChildTitle, WS_OVERLAPPEDWINDOW,
                        500, 50, 400, 100, NULL, NULL, hInstance, NULL);

  CreateWindow(L"Edit", L"", WS_CHILD | WS_VISIBLE, 20, 20, 345, 18, hChild, (HMENU)ID_CHILD_EDIT, hInstance, NULL);


  if (!hChild) return FALSE;

  ShowWindow(hChild, nCmdShow);
  UpdateWindow(hChild);

  return TRUE;
}

LRESULT CALLBACK ParentWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
    case WM_CREATE:

      break;
    case WM_COMMAND:
      if (LOWORD(wParam) == ID_SHOW_CHILD) {
        if (hChild != 0) return FALSE;
        if (!ChildInitInstance(hParentInst, SW_SHOW)) return FALSE;
        EnableWindow(GetDlgItem(hParent, ID_SHOW_CHILD), 0);
      } else if (LOWORD(wParam) == ID_SEND_MESSAGE_TO_CHILD && hChild != 0) {
        TCHAR str[256];
        GetWindowText(GetDlgItem(hParent, ID_PARENT_EDIT), str, 256);
        SetWindowText(GetDlgItem(hChild, ID_CHILD_EDIT), str);
      }
      break;
    case WM_DESTROY:
      PostQuitMessage(0);
      break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}

LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
    case WM_CREATE:

      break;
    case WM_COMMAND:

      break;
    case WM_DESTROY:
      hChild = 0;
      EnableWindow(GetDlgItem(hParent, ID_SHOW_CHILD), 1);
      break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}