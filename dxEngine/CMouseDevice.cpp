#include "CMouseDevice.h"

CMouseDevice::CMouseDevice()
{
	memset(this, 0x00, sizeof(CMouseDevice));
}

CMouseDevice::CMouseDevice(CErrorLog* el, CWindow* w, CInputDevice* id, FLOAT ms, const CHAR* dn)
{
	memset(this, 0x00, sizeof(CMouseDevice));

	errorLog = el;
	window = w;
	sensitivity = ms;
	inputDevice = id;

	for (UINT k = 0; k < 4; k++)
	{
		keyMap[k] = new CKeyMap();
	}

	CMouseDevice::SetKeyMap(CMouseDevice::RMB, CMouseDevice::KR_REPEATER, CPacket::PT_GLOBAL, CPacket::PT_ATTACK);

	CMouseDevice::MakeMouse(dn);
}

CMouseDevice::~CMouseDevice()
{
	for (UINT k = 0; k < 4; k++)
	{
		delete keyMap[k]->packet;

		delete keyMap[k];
	}
}

VOID CMouseDevice::MakeMouse(const CHAR* m)
{
	CLinkListNode* lln = inputDevice->devices->Search(m);

	if (lln == NULL)
	{
		return;
	}

	CDeviceInstance* di = (CDeviceInstance*)lln->element;

	hr = inputDevice->dinput->CreateDevice(di->guidInstance, &device, NULL);

	if (hr < 0)
	{
		errorLog->WriteError("CMouseDevice::MakeMouse::CreateDevice:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}

	hr = device->SetCooperativeLevel(window->hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	if (hr < 0)
	{
		errorLog->WriteError("CMouseDevice::MakeMouse::SetCooperativeLevel:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}

	hr = device->SetDataFormat(&c_dfDIMouse);

	if (hr < 0)
	{
		errorLog->WriteError("CMouseDevice::MakeMouse::SetDataFormat:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}

	hr = device->Acquire();

	if (hr < 0)
	{
		errorLog->WriteError("CMouseDevice::MakeMouse::Acquire:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}
}

VOID CMouseDevice::GetState()
{
	hr = device->GetDeviceState(sizeof(DIMOUSESTATE), &state);

	if (hr < 0)
	{
		errorLog->WriteError("CMouseDevice::GetState::GetDeviceState:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}

	GetCursorPos(&pos);

	position.X = (FLOAT)pos.x;
	position.Y = (FLOAT)pos.y;

	if (window->windowed)
	{
		ScreenToClient(window->hWnd, &pos);

		position.X = (FLOAT)pos.x;
		position.Y = (FLOAT)pos.y + window->returnFromFullscreen;
	}

	for (UINT k = 0; k < 4; k++)
	{
		if (state.rgbButtons[k])
		{
			keyMap[k]->nbr = k;
			keyMap[k]->count++;
		}
		else
		{
			keyMap[k]->count = 0;
		}
	}
}

VOID CMouseDevice::SetKeyMap(UINT n, BOOL ot, BYTE a, BYTE t)
{
	keyMap[n]->nbr = n;
	keyMap[n]->count = 0;
	keyMap[n]->repeater = ot;

	keyMap[n]->packet = new CPacket(0, 0, a, t, t, 1);
}