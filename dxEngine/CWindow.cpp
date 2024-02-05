#include "CWindow.h"

CWindow::CWindow()
{
	memset(this, 0x00, sizeof(CWindow));
}

CWindow::CWindow(HINSTANCE i, BYTE m, UINT w, UINT h, const CHAR* className, const CHAR* title)
{
	memset(this, 0x00, sizeof(CWindow));

	instance = i;
	windowed = m;

	width = w;
	height = h;

	posX = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
	posY = ((GetSystemMetrics(SM_CYSCREEN) - h) / 2) - 20;

	if (windowed)
	{
		hWnd = CreateWindowEx(NULL, className, title, WS_TILEDWINDOW, posX, posY, width, height, NULL, NULL, instance, NULL);
	}
	else
	{
		hWnd = CreateWindowEx(NULL, className, title, WS_POPUP, 0, 0, width, height, NULL, NULL, instance, NULL);
	}
}

CWindow::~CWindow()
{
	if (hWnd)
	{
		DestroyWindow(hWnd);
	}
}

RECT CWindow::GetClientRectangle()
{
	GetClientRect(hWnd, &clientRect);

	return clientRect;
}

RECT CWindow::GetWindowRectangle()
{
	GetWindowRect(hWnd, &windowRect);

	return windowRect;
}

POINT CWindow::GetClientToScreen()
{
	ClientToScreen(hWnd, &clientToScreen);

	return clientToScreen;
}