#include "CGlobalObjects.h"

CGlobalObjects::CGlobalObjects()
{
	memset(this, 0x00, sizeof(CGlobalObjects));
}

CGlobalObjects::CGlobalObjects(HINSTANCE hInstance, const CHAR* cn, const CHAR* t, const CHAR* log, const CHAR* cfg)
{
	memset(this, 0x00, sizeof(CGlobalObjects));

	className = new CString(cn);
	title = new CString(t);
	errorLog = new CErrorLog(log);
	config = new CConfiguration(cfg);

	CLinkListNode* wlln = config->items->Search("windowed");

	CConfigurationItem* wm = (CConfigurationItem*)wlln->element;

	CLinkListNode* swln = config->items->Search("screenWidth");

	CConfigurationItem* sw = (CConfigurationItem*)swln->element;

	CLinkListNode* shln = config->items->Search("screenHeight");

	CConfigurationItem* sh = (CConfigurationItem*)shln->element;

	if (wlln)
	{
		if (wm->value == 1.0F)
		{
			window = new CWindow(hInstance, TRUE, (UINT)sw->value, (UINT)sh->value, className->GetText(), className->GetText());

		}
		else
		{
			window = new CWindow(hInstance, FALSE, (UINT)sw->value, (UINT)sh->value, className->GetText(), className->GetText());
		}
	}

	if (!window->hWnd)
	{
		return;
	}

	videoDevice = new CVideoDevice(errorLog, window);
	soundDevice = new CSoundDevice(errorLog);
	inputDevice = new CInputDevice(errorLog);
	textureMgr = new CTextureManager(errorLog, videoDevice);
	fontDXMgr = new CDXFontManager(errorLog, videoDevice, window);
	soundMgr = new CSoundManager(errorLog, soundDevice);
	effectMgr = new CEffectManager(errorLog, videoDevice);
	fontMgr = new CFontManager(errorLog, videoDevice, window, effectMgr, textureMgr);
	frametime = new CFrametime();
}

CGlobalObjects::~CGlobalObjects()
{
	delete textureMgr;
	delete fontDXMgr;
	delete soundMgr;
	delete effectMgr;
	delete config;
	delete frametime;
	delete keyboard;
	delete mouse;
	delete inputDevice;
	delete soundDevice;
	delete videoDevice;
	delete errorLog;
	delete window;
	delete className;
	delete title;
}

VOID CGlobalObjects::MakeMouseAndKeyboard(const CHAR* mn, const CHAR* kn)
{
	CLinkListNode* mslln = config->items->Search("mouseSensitivity");

	CConfigurationItem* ms = (CConfigurationItem*)mslln->element;

	mouse = new CMouseDevice(errorLog, window, inputDevice, ms->value, mn);
	
	keyboard = new CKeyboardDevice(errorLog, window, inputDevice, kn);

	errorLog->WriteError("Enumerated Input Devices\n");

	CLinkListNode* d = inputDevice->devices->list;

	while (d->element)
	{
		CDeviceInstance* di = (CDeviceInstance*)d->element;

		errorLog->WriteError("%s\n", di->instanceName->GetText());

		d = d->next;
	}
}