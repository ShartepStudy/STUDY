#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
using namespace std;

#define MAX_LOADSTRING 256
#define ID_BUTTON 1001

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
                         50, 50, 400, 400, NULL, NULL, hInstance, NULL);

  if (!hParent) return FALSE;

  CreateWindow(L"Button", L"Создать дочернее окно!", WS_CHILD | WS_VISIBLE, 20, 20, 345, 325, hParent, (HMENU)ID_BUTTON, hInstance, NULL);

  ShowWindow(hParent, nCmdShow);
  UpdateWindow(hParent);

  return TRUE;
}

BOOL ChildInitInstance(HINSTANCE hInstance, int nCmdShow) {
  hChildInst = hInstance;

  hChild = CreateWindow(szChildWindowClass, szChildTitle, WS_OVERLAPPEDWINDOW,
                        500, 50, 200, 200, NULL, NULL, hInstance, NULL);

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
      if (LOWORD(wParam) == ID_BUTTON) {
        //if (hChild != 0) return FALSE;
        if (!ChildInitInstance(hParentInst, SW_SHOW)) return FALSE;

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
      //hChild = 0;
      break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}