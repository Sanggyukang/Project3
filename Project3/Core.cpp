#include "pch.h"
#include "Core.h"
#include "Object.h"
#include "Timer.h"

static Object obj;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

Core::Core()
    : m_hWnd(0),
      m_hDc(0),
      m_memDC(0),
      m_fPoint{},
      m_hBit(0)
{
}
Core::~Core()
{
    ReleaseDC(m_hWnd, m_hDc);
    DeleteDC(m_memDC);
}

HRESULT Core::init(HINSTANCE hInstance)
{
    if(FAILED(SetUpWindow(hInstance)))
        return S_FALSE;
    
    RECT rc;
    if (GetWindowRect(m_hWnd, &rc)) {
        m_fPoint.x = rc.right - rc.left;
        m_fPoint.y = rc.bottom - rc.top;
    }
    rc = { 0,0,m_fPoint.x,m_fPoint.y };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);
    SetWindowPos(m_hWnd, nullptr, 100, 100,rc.right-rc.left, rc.bottom-rc.top, 0);
    
    m_hDc = GetDC(m_hWnd);

    m_hBit = CreateCompatibleBitmap(m_hDc, m_fPoint.x, m_fPoint.y);
    m_memDC = CreateCompatibleDC(m_hDc);
    HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
    DeleteObject(hOldBit);

    obj.SetPos(fPoint(m_fPoint.x/2, m_fPoint.y/2));
    obj.SetScale(fPoint(100, 100));

    Timer::Get_Inst()->Init();

	return S_OK;
}

HRESULT Core::SetUpWindow(HINSTANCE hInstance)
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
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
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

    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
        else
        {
            Update();
            Render();
        }
    }
}

void Core::Update()
{
    Timer::Get_Inst()->Update();

    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        obj.m_pos.x -= 100 * Timer::Get_Inst()->GetfDeltaTime();
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        obj.m_pos.x += 100 * Timer::Get_Inst()->GetfDeltaTime();
    }
}

void Core::Render()
{
    Rectangle(m_memDC, -1, -1, m_fPoint.x+1, m_fPoint.y+1);
    Rectangle(m_memDC, obj.m_pos.x - obj.m_scale.x / 2, obj.m_pos.y - obj.m_scale.y / 2,
        obj.m_pos.x + obj.m_scale.x / 2, obj.m_pos.y + obj.m_scale.y / 2);
    if(SwapBuffers(m_hDc))
        int x = 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    /*switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
    {

    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);*/
    switch (uMsg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
