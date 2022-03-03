#pragma once


class Core
{
	SINGLE(Core);
private:
	HWND	m_hWnd;
	HDC		m_hDc;
	HDC		m_memDC;
	POINT	m_fPoint;
	HBITMAP	m_hBit;
public:
	HRESULT	init(HINSTANCE);
	HRESULT SetUpWindow(HINSTANCE);
	void process();
public:
	void Update();
	void Render();
public:
	HWND GetHwnd() { return m_hWnd; }
};

