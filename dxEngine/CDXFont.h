#ifndef _CDXFONT
#define _CDXFONT

#include "standard.h"

#include "CColor.h"
#include "CErrorLog.h"
#include "CVideoDevice.h"
#include "CWindow.h"

class CDXFont
{
public:

	LPD3DXFONT font;
	
	D3DXFONT_DESC desc;

	SIZE size;

	UINT height;

	CDXFont();

	CDXFont(CErrorLog* el, CVideoDevice* d, CWindow* w, const CHAR* face, UINT pitch, UINT bold);

	~CDXFont();

	VOID Draw(const CHAR* text, UINT x, UINT y, CColor* color);

	SIZE GetStringSize(CString* s);

private:

	HRESULT hr;

	CErrorLog* errorLog;
	
	CVideoDevice* videoDevice;
	
	CWindow* window;

	RECT rect;
};
#endif