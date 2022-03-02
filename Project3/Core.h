#pragma once


class Core
{
	SINGLE(Core);
private:
	HWND m_hWnd;
public:
	HRESULT	init(HINSTANCE);
	void process();
};

