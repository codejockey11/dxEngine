#ifndef _CMOUSEDEVICE
#define _CMOUSEDEVICE

#include "standard.h"

#include "CDeviceInstance.h"
#include "CErrorLog.h"
#include "CInputDevice.h"
#include "CKeyMap.h"
#include "CPacket.h"
#include "CWindow.h"
#include "CVertex.h"

class CMouseDevice
{
public:

	DIMOUSESTATE state;
	
	CVertex2 position;

	CKeyMap* keyMap[4];

	FLOAT sensitivity;

	CMouseDevice();

	CMouseDevice(CErrorLog* el, CWindow* w, CInputDevice* id, FLOAT ms, const CHAR* dn);

	~CMouseDevice();

	VOID MakeMouse(const CHAR* m);

	VOID GetState();

	VOID SetKeyMap(UINT n, BOOL ot, BYTE t, BYTE a);

	enum
	{
		LMB = 0,
		RMB,
		MMB,
		SCR
	};

	enum
	{
		KR_ONESHOT = 0,
		KR_REPEATER,

		MAXKEYREPEAT = 0xFF
	};

private:

	HRESULT hr;

	CErrorLog* errorLog;
	
	CWindow* window;
	
	CInputDevice* inputDevice;

	IDirectInputDevice8* device;

	POINT pos;
};
#endif