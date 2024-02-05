#include "CDXFont.h"

CDXFont::CDXFont()
{
	memset(this, 0x00, sizeof(CDXFont));
}

CDXFont::CDXFont(CErrorLog* el, CVideoDevice* d, CWindow* w, const CHAR* face, UINT pitch, UINT bold)
{
	memset(this, 0x00, sizeof(CDXFont));

	errorLog = el;
	videoDevice = d;
	window = w;

	hr = D3DXCreateFont(videoDevice->device, pitch, 0, bold, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, face, &font);

	if (hr < 0)
	{
		errorLog->WriteError("CDXFontManager::MakeDXFont::D3DXCreateFont:%s:%s\n", face, errorLog->GetComErrorMessage(hr));

		font = NULL;

		return;
	}

	hr = font->GetDesc(&desc);

	height = desc.Height;
}

CDXFont::~CDXFont()
{
	if (font)
	{
		font->Release();
	}
}

VOID CDXFont::Draw(const CHAR* text, UINT x, UINT y, CColor* color)
{
	rect.left = x;
	rect.top = y;
	rect.right = window->width;
	rect.bottom = window->height;

	font->DrawTextA(NULL, text, (INT)strlen(text), &rect, DT_TOP | DT_LEFT, D3DCOLOR_XRGB(color->r, color->g, color->b));
}

SIZE CDXFont::GetStringSize(CString* s)
{
	GetTextExtentPoint32(font->GetDC(), s->GetText(), (INT)s->GetLength(), &size);

	return size;
}