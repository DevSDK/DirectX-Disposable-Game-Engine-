#pragma once
#define UNICODE
#include<Windows.h>
#include <d3d11_2.h>
#include <wrl\client.h>
#include "Renderer.h"
#include <string>
#pragma comment(lib, "d3d11.lib")

class Win32Client
{
public:
	static Win32Client* GetInstance();

	void Initialize(int width, int height, std::wstring title, HINSTANCE hInstance);
	void Run();

private:
	
	Renderer* m_renderer;

	void InitializeWin32(int width, int height, std::wstring title, HINSTANCE hInstance);
	void InitializeRenderer(int Width, int Height);
	Renderer* GetCurrentRenderer();
	Win32Client();
	~Win32Client();

	static Win32Client* Instance;
private:

	HWND m_hwnd;


protected:

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



};





