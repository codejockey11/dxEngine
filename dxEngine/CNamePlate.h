#ifndef _CNAMEPLATE
#define _CNAMEPLATE

#include "standard.h"

#include "CBillboard.h"
#include "CColor.h"
#include "CGlobalObjects.h"
#include "CString.h"

class CNamePlate
{
public:

	CString* name;

	CVertex position;

	CBillboard* billboard;

	CNamePlate();

	CNamePlate(CGlobalObjects* g, const CHAR* f, const CHAR* text, CColor* color, CVertex* p);

	~CNamePlate();

	VOID Draw();

private:

	HRESULT hr;

	CGlobalObjects* globalObjects;

	IDirect3DSurface9* surface;

	IDirect3DSurface9* tempSurf;

	IDirect3DTexture9* texture;

	HDC hdc;

	SIZE size;

	HFONT hFont;

	RECT sr;
};
#endif