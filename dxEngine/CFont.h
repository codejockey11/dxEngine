#ifndef _CFONT
#define _CFONT

#include "standard.h"

#include "CBmpImage.h"
#include "CColor.h"
#include "CErrorLog.h"
#include "CEffectManager.h"
#include "CHudImage.h"
#include "CTextureManager.h"
#include "CVideoDevice.h"

class CFont
{
public:

	enum
	{
		MAXFONTCOUNT = 94
	};

	CErrorLog* errorLog;
	CVideoDevice* videoDevice;
	CEffectManager* effectMgr;
	CTextureManager* textureMgr;

	CHudImage* fonts[CFont::MAXFONTCOUNT];

	CBmpImage* bmp;

	CEffect* effect;

	UINT height;

	CFont();

	CFont(CErrorLog* el, CVideoDevice* d, CEffectManager* em, CTextureManager* tm, const CHAR* fn, CVertex2* sz);

	~CFont();

	VOID Draw(const CHAR* text, UINT x, UINT y, CColor* color);

	HRESULT hr;
};
#endif