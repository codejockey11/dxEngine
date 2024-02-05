#ifndef _CINPUTDEVICE
#define _CINPUTDEVICE

#include "standard.h"

#include "CDeviceInstance.h"
#include "CErrorLog.h"
#include "CLinkList.h"

class CInputDevice
{
public:

	IDirectInput8* dinput;

	CLinkList* devices;

	CInputDevice();

	CInputDevice(CErrorLog* el);

	~CInputDevice();

private:

	HRESULT hr;

	CErrorLog* errorLog;
};
#endif