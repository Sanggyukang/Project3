#include "pch.h"
#include "Core.h"


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

Core::Core()
    : m_hWnd(0)
{
}
Core::~Core()
{
}

HRESULT Core::init(HINSTANCE hInstance)
{
	const wchar_t GAME_NAME[] = L"Simple Tetris ";

	WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = GAME_NAME;

    RegisterClass(&wc);

    m_hWnd = CreateWindowEx(
        0,
        GAME_NAME,
        L"Tetris",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (m_hWnd == NULL)
        return S_FALSE;

	return S_OK;
}

void Core::process()
{
    ShowWindow(m_hWnd, true);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
