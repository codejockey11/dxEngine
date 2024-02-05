#include "CKeyboardDevice.h"

CKeyboardDevice::CKeyboardDevice()
{
	memset(this, 0x00, sizeof(CKeyboardDevice));
}

CKeyboardDevice::CKeyboardDevice(CErrorLog* el, CWindow* w, CInputDevice* id, const CHAR* dn)
{
	memset(this, 0x00, sizeof(CKeyboardDevice));

	errorLog = el;
	window = w;
	inputDevice = id;

	for (UINT k = 0; k < 256; k++)
	{
		keyMap[k] = new CKeyMap();
	}

	CKeyboardDevice::SetKeyMap(DIK_F1, CKeyboardDevice::KR_ONESHOT, CPacket::PT_LOCAL, CPacket::PT_STARTSERVER);
	CKeyboardDevice::SetKeyMap(DIK_F2, CKeyboardDevice::KR_ONESHOT, CPacket::PT_LOCAL, CPacket::PT_STOPSERVER);
	CKeyboardDevice::SetKeyMap(DIK_F3, CKeyboardDevice::KR_ONESHOT, CPacket::PT_LOCAL, CPacket::PT_CONNECT);
	CKeyboardDevice::SetKeyMap(DIK_F4, CKeyboardDevice::KR_ONESHOT, CPacket::PT_LOCAL, CPacket::PT_DISCONNECT);

	CKeyboardDevice::SetKeyMap(DIK_F8, CKeyboardDevice::KR_ONESHOT, CPacket::PT_LOCAL, CPacket::PT_LOADBRUSHMAP);
	CKeyboardDevice::SetKeyMap(DIK_F9, CKeyboardDevice::KR_ONESHOT, CPacket::PT_LOCAL, CPacket::PT_LOADTERRAIN);
	CKeyboardDevice::SetKeyMap(DIK_F10, CKeyboardDevice::KR_ONESHOT, CPacket::PT_LOCAL, CPacket::PT_LOADORTHOLEVEL);
	CKeyboardDevice::SetKeyMap(DIK_F11, CKeyboardDevice::KR_ONESHOT, CPacket::PT_LOCAL, CPacket::PT_TOGGLECONSOLE);
	CKeyboardDevice::SetKeyMap(DIK_EQUALS, CKeyboardDevice::KR_ONESHOT, CPacket::PT_LOCAL, CPacket::PT_WINDOWMODE);

	CKeyboardDevice::SetKeyMap(DIK_UP, CKeyboardDevice::KR_REPEATER, CPacket::PT_GLOBAL, CPacket::PT_MOVE_UP);
	CKeyboardDevice::SetKeyMap(DIK_LEFT, CKeyboardDevice::KR_REPEATER, CPacket::PT_GLOBAL, CPacket::PT_MOVE_LEFT);
	CKeyboardDevice::SetKeyMap(DIK_RIGHT, CKeyboardDevice::KR_REPEATER, CPacket::PT_GLOBAL, CPacket::PT_MOVE_RIGHT);
	CKeyboardDevice::SetKeyMap(DIK_DOWN, CKeyboardDevice::KR_REPEATER, CPacket::PT_GLOBAL, CPacket::PT_MOVE_DOWN);

	CKeyboardDevice::SetKeyMap(DIK_ESCAPE, CKeyboardDevice::KR_ONESHOT, CPacket::PT_LOCAL, CPacket::PT_EXIT);

	CKeyboardDevice::SetKeyMap(DIK_W, CKeyboardDevice::KR_REPEATER, CPacket::PT_GLOBAL, CPacket::PT_FORWARD);
	CKeyboardDevice::SetKeyMap(DIK_S, CKeyboardDevice::KR_REPEATER, CPacket::PT_GLOBAL, CPacket::PT_BACKWARD);
	CKeyboardDevice::SetKeyMap(DIK_A, CKeyboardDevice::KR_REPEATER, CPacket::PT_GLOBAL, CPacket::PT_STRAFELEFT);
	CKeyboardDevice::SetKeyMap(DIK_D, CKeyboardDevice::KR_REPEATER, CPacket::PT_GLOBAL, CPacket::PT_STRAFERIGHT);

	CKeyboardDevice::MakeKeyboard(dn);
}

CKeyboardDevice::~CKeyboardDevice()
{
	for (UINT k = 0; k < 256; k++)
	{
		delete keyMap[k]->packet;

		delete keyMap[k];
	}
}

VOID CKeyboardDevice::MakeKeyboard(const CHAR* dn)
{
	CLinkListNode* lln = inputDevice->devices->Search(dn);

	if (lln == NULL)
	{
		return;
	}

	CDeviceInstance* di = (CDeviceInstance*)lln->element;

	hr = inputDevice->dinput->CreateDevice(di->guidInstance, &device, NULL);

	if (hr < 0)
	{
		errorLog->WriteError("CKeyboardDevice::MakeKeyboard::CreateDevice:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}

	hr = device->SetCooperativeLevel(window->hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	if (hr < 0)
	{
		errorLog->WriteError("CKeyboardDevice::MakeKeyboard::SetCooperativeLevel:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}

	hr = device->SetDataFormat(&c_dfDIKeyboard);

	if (hr < 0)
	{
		errorLog->WriteError("CKeyboardDevice::MakeKeyboard::SetDataFormat:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}

	hr = device->Acquire();

	if (hr < 0)
	{
		errorLog->WriteError("CKeyboardDevice::MakeKeyboard::Acquire:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}
}

VOID CKeyboardDevice::GetState()
{
	hr = device->GetDeviceState(256, &keys);

	if (hr < 0)
	{
		errorLog->WriteError("CKeyboardDevice::GetStateData::GetDeviceState:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}

	for (UINT k = 0; k < 256; k++)
	{
		if (keys[k])
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

VOID CKeyboardDevice::SetKeyMap(UINT n, BYTE ot, BYTE a, BYTE t)
{
	keyMap[n]->nbr = n;
	keyMap[n]->count = 0;
	keyMap[n]->repeater = ot;

	keyMap[n]->packet = new CPacket(0, 0, a, t, t, 1);
}