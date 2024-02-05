#include "CNamePlate.h"

CNamePlate::CNamePlate()
{
	memset(this, 0x00, sizeof(CNamePlate));
}

CNamePlate::~CNamePlate()
{
	delete name;
	delete billboard;

	if (texture)
	{
		texture->Release();
	}
}

CNamePlate::CNamePlate(CGlobalObjects* g, const CHAR* f, const CHAR* text, CColor* color, CVertex* p)
{
	memset(this, 0x00, sizeof(CNamePlate));

	globalObjects = g;
	position = *p;

	name = new CString(text);

	hFont = CreateFont(48, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, VARIABLE_PITCH, f);

	hr = globalObjects->videoDevice->device->CreateOffscreenPlainSurface(1, 1, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &surface, NULL);

	if (hr < 0)
	{
		globalObjects->errorLog->WriteError("CNamePlate::CNamePlate::CreateOffscreenPlainSurface:%s:%s\n", text, globalObjects->errorLog->GetComErrorMessage(hr));

		return;
	}

	hr = surface->GetDC(&hdc);

	if (hr < 0)
	{
		globalObjects->errorLog->WriteError("CNamePlate::CNamePlate::GetDC:%s\n", globalObjects->errorLog->GetComErrorMessage(hr));

		return;
	}

	SelectObject(hdc, hFont);

	GetTextExtentPoint32(hdc, name->GetText(), (INT)name->GetLength(), &size);

	hr = surface->ReleaseDC(hdc);

	if (hr < 0)
	{
		globalObjects->errorLog->WriteError("CNamePlate::CNamePlate::ReleaseDC:%s\n", globalObjects->errorLog->GetComErrorMessage(hr));

		return;
	}

	if (surface)
	{
		surface->Release();
	}

	hr = globalObjects->videoDevice->device->CreateOffscreenPlainSurface(size.cx, size.cy, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &surface, NULL);

	if (hr < 0)
	{
		globalObjects->errorLog->WriteError("CNamePlate::CNamePlate::CreateOffscreenPlainSurface:%s\n", globalObjects->errorLog->GetComErrorMessage(hr));

		return;
	}

	sr.left = 0;
	sr.top = 0;
	sr.right = size.cx;
	sr.bottom = size.cy;

	hr = globalObjects->videoDevice->device->ColorFill(surface, &sr, D3DCOLOR_XRGB(0, 0, 0));

	if (hr < 0)
	{
		globalObjects->errorLog->WriteError("CNamePlate::CNamePlate::ColorFill:%s\n", globalObjects->errorLog->GetComErrorMessage(hr));

		return;
	}

	hr = surface->GetDC(&hdc);

	if (hr < 0)
	{
		globalObjects->errorLog->WriteError("CNamePlate::CNamePlate::GetDC:%s\n", globalObjects->errorLog->GetComErrorMessage(hr));

		return;
	}

	SelectObject(hdc, hFont);

	SetTextColor(hdc, RGB(color->r, color->g, color->b));

	SetBkMode(hdc, TRANSPARENT);

	TextOut(hdc, 0, 0, name->GetText(), (INT)name->GetLength());

	hr = surface->ReleaseDC(hdc);

	if (hr < 0)
	{
		globalObjects->errorLog->WriteError("CNamePlate::CNamePlate::ReleaseDC:%s\n", globalObjects->errorLog->GetComErrorMessage(hr));

		return;
	}

	hr = D3DXCreateTexture(globalObjects->videoDevice->device, size.cx, size.cy, 0, D3DX_DEFAULT, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &texture);

	if (hr < 0)
	{
		globalObjects->errorLog->WriteError("CNamePlate::CNamePlate::D3DXCreateTexture:%s\n", globalObjects->errorLog->GetComErrorMessage(hr));

		return;
	}

	hr = texture->GetSurfaceLevel(0, &tempSurf);

	if (hr < 0)
	{
		globalObjects->errorLog->WriteError("CNamePlate::CNamePlate::GetSurfaceLevel:%s\n", globalObjects->errorLog->GetComErrorMessage(hr));

		return;
	}

	hr = D3DXLoadSurfaceFromSurface(tempSurf, NULL, NULL, surface, NULL, NULL, D3DX_FILTER_BOX, D3DCOLOR_ARGB(255, 0, 0, 0));

	if (hr < 0)
	{
		globalObjects->errorLog->WriteError("CNamePlate::CNamePlate::D3DXLoadSurfaceFromSurface:%s\n", globalObjects->errorLog->GetComErrorMessage(hr));

		return;
	}

	DeleteObject(hFont);

	if (surface)
	{
		surface->Release();
	}

	CVertex2 v(2.0F, 1.0F);

	billboard = new CBillboard(globalObjects, "nameplate.bmp", &v, &position, CBillboard::BT_NAMEPLATE);

	billboard->texture->image = texture;
}

VOID CNamePlate::Draw()
{
	billboard->Draw();
}