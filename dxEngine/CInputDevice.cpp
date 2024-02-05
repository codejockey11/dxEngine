#include "CInputDevice.h"

CInputDevice::CInputDevice()
{
	memset(this, 0x00, sizeof(CInputDevice));
}

CInputDevice::CInputDevice(CErrorLog* el)
{
	memset(this, 0x00, sizeof(CInputDevice));

	errorLog = el;

	hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID * *)& dinput, NULL);

	if (hr < 0)
	{
		errorLog->WriteError("CInputDevice::CInputDevice::DirectInput8Create:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}

	devices = new CLinkList();
}

CInputDevice::~CInputDevice()
{
	delete devices;

	if (dinput)
	{
		dinput->Release();
	}
}