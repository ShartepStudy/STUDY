
#pragma warning (disable:4996)

//  Bounce - Creates a new thread each time the letter 'a' is typed.
//  Each thread bounces a happy face of a different color around
//  the screen. All threads are terminated when the letter 'Q' is
//  entered.

#include <windows.h>
#include <conio.h>
#include <time.h>
#include <process.h>
#include <iostream>
using namespace std;

#define MAX_THREADS 200

// The function getrandom returns a random number between 
// min and max, which must be in integer range.

#define getrandom( min, max ) \
(SHORT)((rand() % (int)(((max) + 1) - (min))) + (min))

int main();		                     // Thread 1: main 
void KbdFunc();					     // Keyboard input, thread dispatch
void BounceProc(void * MyID);        // Threads 2 to n: display 
void ClearScreen();                  // Screen clear 
void ShutDown();                     // Program shutdown 
void WriteTitle(int ThreadNum);      // Display title bar information 

HANDLE  hConsoleOut;                 // Handle to the console 
HANDLE  hRunMutex;                   // "Keep Running" mutex 
HANDLE  hScreenMutex;                // "Screen update" mutex
int     ThreadNr;                    // Number of threads started 
CONSOLE_SCREEN_BUFFER_INFO csbiInfo; // Console information 

int main() // Prime Thread 
{
	system("mode con cols=130 lines=50");
	MoveWindow(GetConsoleWindow(), 50, 50, 3000, 3000, false);

	// Get display screen information & clear the screen.
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	ClearScreen();
	WriteTitle(0);

	// Create the mutexes and reset thread count.
	hScreenMutex = CreateMutex(NULL, FALSE, NULL);  // Cleared 
	hRunMutex = CreateMutex(NULL, TRUE, NULL);      // Set 
	ThreadNr = 0;

	setlocale(0, "");
	cout << "Нажмите пробел для создания нового потока!\n";

	// Start waiting for keyboard input to dispatch threads or exit.
	KbdFunc();

	// All threads done. Clean up handles.
	CloseHandle(hScreenMutex);
	CloseHandle(hRunMutex);
	CloseHandle(hConsoleOut);
}

void ShutDown() // Shut down threads 
{
	while (ThreadNr > 0)
	{
		// Tell thread to die and record its death.
		ReleaseMutex(hRunMutex);
		ThreadNr--;
	}

	// Clean up display when done
	WaitForSingleObject(hScreenMutex, INFINITE);
	ClearScreen();
}

void KbdFunc(void) // Dispatch and count threads.
{
	int KeyInfo;

	do
	{
		KeyInfo = _getch();
		if (tolower(KeyInfo) == ' ' &&
			ThreadNr < MAX_THREADS)
		{
			ThreadNr++;
			_beginthread(BounceProc, 0, &ThreadNr);
			WriteTitle(ThreadNr);
		}
	} while (tolower(KeyInfo) != 'q');

	ShutDown();
}

void BounceProc(void *pMyID)
{
	wchar_t    MyCell, OldCell;
	WORD	   MyAttrib, OldAttrib;
	wchar_t    BlankCell = ' ';
	COORD      Coords, Delta;
	COORD      Old = { 0, 0 };
	DWORD      Dummy;
	wchar_t    *MyID = (wchar_t*)pMyID;

	// Generate update increments and initial 
	// display coordinates.

	srand(time(0) + (int)* MyID);

	Coords.X = getrandom(0, csbiInfo.dwSize.X - 1);
	Coords.Y = getrandom(0, csbiInfo.dwSize.Y - 1);
	Delta.X = getrandom(-3, 3);
	Delta.Y = getrandom(-3, 3);

	if (Delta.X == 0 && Delta.Y == 0) Delta.X = Delta.Y = 1;

	// Set up "happy face" & generate color 
	// attribute from thread number.

	MyCell = *MyID % 2 + 1;         // outline face 

	//	MyAttrib =  *MyID & 0x0F;   // force black background 
	MyAttrib = getrandom(1, 15);

	do
	{
		// Wait for display to be available, then lock it.
		
		WaitForSingleObject(hScreenMutex, INFINITE);

		// If we still occupy the old screen position, blank it out. 
		ReadConsoleOutputCharacter(hConsoleOut, &OldCell, 1, Old, &Dummy);
		ReadConsoleOutputAttribute(hConsoleOut, &OldAttrib, 1, Old, &Dummy);

		WriteConsoleOutputCharacter(hConsoleOut, &BlankCell, 1, Old, &Dummy);

		// Draw new face, then clear screen lock 
		WriteConsoleOutputCharacter(hConsoleOut, &MyCell, 1,Coords, &Dummy);
		WriteConsoleOutputAttribute(hConsoleOut, &MyAttrib, 1, Coords, &Dummy);
		
		ReleaseMutex(hScreenMutex);

		// Increment the coordinates for next placement of the block. 
		Old.X = Coords.X;
		Old.Y = Coords.Y;
		Coords.X += Delta.X;
		Coords.Y += Delta.Y;

		// If we are about to go off the screen, reverse direction 
		if (Coords.X <= 0 - Delta.X - 1 || Coords.X >= csbiInfo.dwSize.X - Delta.X)
		{
			Delta.X = -Delta.X;
			// Beep( 400, 50 ); // pong!
		}
		if (Coords.Y <= 0 - Delta.Y - 1 || Coords.Y >= csbiInfo.dwSize.Y - Delta.Y)
		{
			Delta.Y = -Delta.Y;
			// Beep( 600, 50 ); // ping!
		}
	}
	// Repeat while RunMutex is still taken. 
	while (WaitForSingleObject(hRunMutex, 15) == WAIT_TIMEOUT);
}

void WriteTitle(int tn)
{
	TCHAR title[50];
	wsprintf(title, L"Потоков запущено: %d", tn);
	SetConsoleTitle(title);
}

void ClearScreen()
{
	DWORD dummy;
	COORD home = { 0, 0 };
	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, home, &dummy);
	//FillConsoleOutputCharacter(hConsoleOut, '#', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, home, &dummy);
}