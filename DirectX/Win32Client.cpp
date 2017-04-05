#include "Win32Client.h"
#include "GameInit.h"
Win32Client* Win32Client::Instance = nullptr;

Win32Client * Win32Client::GetInstance()
{	
	if (Instance == nullptr)
		Instance = new Win32Client();
	return Instance;

}
Renderer* Win32Client::GetCurrentRenderer()
{
	return m_renderer;
}
void Win32Client::Initialize(int width, int height, std::wstring title, HINSTANCE hInstance)
{
	InitializeWin32(width, height, title, hInstance);
	InitializeRenderer(width, height);	
}

void Win32Client::Run()
{
	ShowWindow(m_hwnd, 10);

	MSG msg = {};
	GameInitalize::GetInstance()->Main();
	while (WM_QUIT != msg.message)
	{
		bool bGotMsg = (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0);

		if (bGotMsg)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			
		}
		else
		{
			
			m_renderer->AllDraw();
		}
	}



}

void Win32Client::InitializeWin32(int width, int height, std::wstring title, HINSTANCE hInstance)
{
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = title.c_str();

	RegisterClass(&wc);

	m_hwnd = CreateWindowEx(
		0,
		title.c_str(),
		L"Learn to Program Windows",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		NULL,
		NULL,
		hInstance,
		NULL
	);

}

void Win32Client::InitializeRenderer(int Width, int Height)
{
	m_renderer = new Renderer(Width, Height, m_hwnd);
}

Win32Client::Win32Client()
{
}

Win32Client::~Win32Client()
{
	delete Instance;
	delete m_renderer;
}

LRESULT Win32Client::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
