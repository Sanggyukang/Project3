#include "pch.h"
#include "Core.h"
#include "Object.h"
#include "Timer.h"


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
Core::Core()
    : m_hWnd(0),
      m_hDc(0),
      m_memDC(0),
      m_fPoint{},
      m_hBit(0),
      m_dT(0),
      m_fT(0)
{
}
Core::~Core()
{
    ReleaseDC(m_hWnd, m_hDc);
    DeleteDC(m_memDC);
}

void Core::VectorToBit()
{
    vector<POINT> snake = Object::Get_Inst()->GetSnakePoint();
    for (int i = 0; i < snake.size(); ++i) {
        m_map2x2[snake[i].y][snake[i].x] = 2;
    }
    POINT apple = Object::Get_Inst()->GetApplePoint();
    m_map2x2[apple.y][apple.x] = 1;

    int vecx = 0;
    int vecy = 0;
    int pitch = m_fPoint.x * 4;
    uint8_t* row = (uint8_t*)bitmapMemory;
    for (int y = 0; y < m_fPoint.y; ++y) {
        uint8_t* pixel = (uint8_t*)row;
        for (int x = 0; x < m_fPoint.x; ++x) {
            if (m_map2x2[vecy][vecx] == 1) {
                // Apple
                //blue
                *pixel = 0;
                ++pixel;

                //green
                *pixel = 255;
                ++pixel;

                //red
                *pixel = 0;
                ++pixel;

                *pixel = 0;
                ++pixel;
            }
            else if (m_map2x2[vecy][vecx] == 2) {
                // snake
                //blue
                *pixel = 0;
                ++pixel;

                //green
                *pixel = 0;
                ++pixel;

                //red
                *pixel = 255;
                ++pixel;

                *pixel = 0;
                ++pixel;
            }
            else {
                //blue
                *pixel = 0;
                ++pixel;

                //green
                *pixel = 0;
                ++pixel;

                //red
                *pixel = 0;
                ++pixel;

                *pixel = 0;
                ++pixel;
                // move along
                //++Pixel;
                //++Pixel;
                //++Pixel;
                //++Pixel;
            }
            vecx = x / 10;
        }
        row += pitch;
        vecy = y / 10;
    }
    for (int i = 0; i < snake.size(); ++i) {
        m_map2x2[snake[i].y][snake[i].x] = 0;
    }
    m_map2x2[apple.y][apple.x] = 0;
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

    Timer::Get_Inst()->Init();

    memset(&bitmapinfo, 0, sizeof(BITMAPINFO));

    if (bitmapMemory) {
        VirtualFree(bitmapMemory, 0, MEM_RELEASE);
    }
    bitmapinfo.bmiHeader.biSize = sizeof(bitmapinfo.bmiHeader);
    bitmapinfo.bmiHeader.biWidth = m_fPoint.x;
    bitmapinfo.bmiHeader.biHeight = m_fPoint.y;
    bitmapinfo.bmiHeader.biPlanes = 1;
    bitmapinfo.bmiHeader.biBitCount = 32;
    bitmapinfo.bmiHeader.biCompression = BI_RGB;
    bitmapinfo.bmiHeader.biSizeImage = 0;
    bitmapinfo.bmiHeader.biXPelsPerMeter = 0;
    bitmapinfo.bmiHeader.biYPelsPerMeter = 0;
    bitmapinfo.bmiHeader.biClrUsed = 0;
    bitmapinfo.bmiHeader.biClrImportant = 0;

    int BitmapMemorySize = (m_fPoint.x * m_fPoint.y) * 4;
    bitmapMemory = VirtualAlloc(0, BitmapMemorySize, MEM_COMMIT, PAGE_READWRITE);


    int blocksperwidth = m_fPoint.x / 10;
    int blocksperheight = m_fPoint.y / 10;

    m_map2x2.resize(blocksperheight, vector<int>(blocksperwidth, 0));
 
    Object::Get_Inst()->Init(blocksperwidth, blocksperheight);
    Object::Get_Inst()->reset();


    VectorToBit();

	return S_OK;
}

HRESULT Core::SetUpWindow(HINSTANCE hInstance)
{
    const wchar_t GAME_NAME[] = L"Simple SnakeGame ";

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
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
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
    Timer::Get_Inst()->Update(&m_dT,&m_fT);
    
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        Object::Get_Inst()->SetDirection(Object::Direction::LEFT);
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        Object::Get_Inst()->SetDirection(Object::Direction::RIGHT);
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        Object::Get_Inst()->SetDirection(Object::Direction::UP);
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        Object::Get_Inst()->SetDirection(Object::Direction::DOWN);
    }
    if (0.007 <= m_dT) {
        Object::Get_Inst()->Update();
        VectorToBit();
    }
}

void Core::Render()
{
    StretchDIBits(m_hDc,
        //X, Y, Width, Height, X, Y, Width, Height,
        0, 0, m_fPoint.x, m_fPoint.y,
        0, m_fPoint.y+1, m_fPoint.x,-m_fPoint.y,
        bitmapMemory,
        &bitmapinfo,
        DIB_RGB_COLORS, SRCCOPY);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
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
