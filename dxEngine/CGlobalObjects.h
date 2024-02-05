#ifndef _CGLOBALOBJECTS
#define _CGLOBALOBJECTS

#include "standard.h"

#include "CConfiguration.h"
#include "CDXFontManager.h"
#include "CErrorLog.h"
#include "CEffectManager.h"
#include "CFontManager.h"
#include "CFrameTime.h"
#include "CInputDevice.h"
#include "CKeyboardDevice.h"
#include "CMouseDevice.h"
#include "CSoundDevice.h"
#include "CSoundManager.h"
#include "CString.h"
#include "CTextureManager.h"
#include "CVideoDevice.h"
#include "CWindow.h"

class CGlobalObjects
{
public:

	CConfiguration* config;
	CDXFontManager* fontDXMgr;
	CEffectManager* effectMgr;
	CErrorLog* errorLog;
	CFontManager* fontMgr;
	CFrametime* frametime;
	CInputDevice* inputDevice;
	CKeyboardDevice* keyboard;
	CMouseDevice* mouse;
	CSoundDevice* soundDevice;
	CSoundManager* soundMgr;
	CTextureManager* textureMgr;
	CVideoDevice* videoDevice;
	CWindow* window;

	CString* className;
	CString* title;

	CGlobalObjects();

	CGlobalObjects(HINSTANCE hInstance, const CHAR* cn, const CHAR* t, const CHAR* log, const CHAR* cfg);

	~CGlobalObjects();

	VOID MakeMouseAndKeyboard(const CHAR* mn, const CHAR* kn);
};
#endif