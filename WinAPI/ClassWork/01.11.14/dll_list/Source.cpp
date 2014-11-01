#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <psapi.h>
#include <iostream>
using namespace std;

int PrintModules(DWORD processID) {
  HANDLE h = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                         FALSE,
                         processID);

  char exe_path[2048] = {};

  if (GetModuleFileNameExA(h, 0, exe_path, sizeof(exe_path)-1)) {
    //cout << exe_path << "\n";
  }

  CloseHandle(h);


  HMODULE hMods[1024];
  HANDLE hProcess;
  DWORD cbNeeded;
  unsigned int i;

  // Print the process identifier.

  //printf("\nProcess ID: %u\n", processID);

  // Get a handle to the process.

  hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
                         PROCESS_VM_READ,
                         FALSE, processID);
  if (NULL == hProcess)
    return 1;

  // Get a list of all the modules in this process.

  if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
    if (strstr(exe_path, "devenv.exe")) {
      for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
        TCHAR szModName[MAX_PATH];

        // Get the full path to the module's file.

        if (GetModuleFileNameEx(hProcess, hMods[i], szModName,
          sizeof(szModName) / sizeof(TCHAR))) {
          // Print the module name and handle value.

          _tprintf(TEXT("%s\n\n"), szModName);

        }
      }
      return 0;
    }
  }

  // Release the handle to the process.

  CloseHandle(hProcess);

  return 0;
}

void main() {
  DWORD aProcesses[1024];
  DWORD cbNeeded;
  DWORD cProcesses;
  unsigned int i;

  // Get the list of process identifiers.

  if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
    return;

  // Calculate how many process identifiers were returned.

  cProcesses = cbNeeded / sizeof(DWORD);

  // Print the names of the modules for each process.

  for (i = 0; i < cProcesses; i++) {
    PrintModules(aProcesses[i]);
  }

}