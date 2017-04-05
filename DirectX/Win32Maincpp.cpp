#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "Win32Client.h"
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{	
	Win32Client::GetInstance()->Initialize(800, 800, L"Hi~", hInstance);
	Win32Client::GetInstance()->Run();
	return 0;
}

