#ifndef _CKEYBOARDDEVICE
#define _CKEYBOARDDEVICE

#include "standard.h"

#include "CErrorLog.h"
#include "CInputDevice.h"
#include "CKeyMap.h"
#include "CLinkList.h"
#include "CPacket.h"
#include "CWindow.h"

class CKeyboardDevice
{
public:

	CHAR keys[256];
		
	CKeyMap* keyMap[256];

	CKeyboardDevice();
	
	CKeyboardDevice(CErrorLog* el, CWindow* w, CInputDevice* id, const CHAR* dn);

	~CKeyboardDevice();

	VOID GetState();
	
	VOID SetKeyMap(UINT n, BYTE ot, BYTE t, BYTE a);
	
	VOID MakeKeyboard(const CHAR* dn);

	enum
	{
		KR_ONESHOT = 1,
		KR_REPEATER,
		
		MAXKEYREPEAT = 0xFF
	};

private:

	HRESULT hr;
	
	CErrorLog* errorLog;
	
	CInputDevice* inputDevice;
	
	CWindow* window;

	IDirectInputDevice8* device;
};
#endif