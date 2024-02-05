#ifndef _CWINDOW
#define _CWINDOW

#include "standard.h"

class CWindow
{
public:

	UINT posX;
	UINT posY;

	UINT width;
	UINT height;

	HWND hWnd;

	HINSTANCE instance;

	BYTE windowed;

	POINT middle;

	RECT windowRect;
	RECT clientRect;

	POINT clientToScreen;

	UINT returnFromFullscreen;

	CWindow();

	CWindow(HINSTANCE i, BYTE m, UINT w, UINT h, const CHAR* className, const CHAR* title);

	~CWindow();

	RECT GetWindowRectangle();

	RECT GetClientRectangle();

	POINT GetClientToScreen();
};
#endif