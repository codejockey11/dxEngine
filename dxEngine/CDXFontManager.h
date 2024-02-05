#ifndef _CDXFONTMANAGER
#define _CDXFONTMANAGER

#include "standard.h"

#include "CDXFont.h"
#include "CLinkList.h"
#include "CVideoDevice.h"
#include "CWindow.h"

class CDXFontManager
{
public:

	CLinkList* fonts;

	CDXFontManager();

	CDXFontManager(CErrorLog* el, CVideoDevice* d, CWindow* w);

	~CDXFontManager();

	VOID DeleteDXFont(const CHAR* fn);

	CDXFont* MakeDXFont(const CHAR* face, UINT pitch, UINT bold);

	CDXFont* GetFont(const CHAR* face);

private:

	HRESULT hr;

	CErrorLog* errorLog;
	
	CVideoDevice* videoDevice;
	
	CWindow* window;

	CDXFont* font;
};
#endif