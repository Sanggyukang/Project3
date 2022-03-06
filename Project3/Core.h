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
private:
	vector<vector<int>> m_map2x2;
	void* bitmapMemory;
	BITMAPINFO  bitmapinfo;
	void VectorToBit();
	double m_dT;
	float m_fT;
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

