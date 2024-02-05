#include <SDKDDKVer.h>

#include "standard.h"
#include "resource.h"

#include "CConfiguration.h"
#include "CErrorLog.h"
#include "CEventManager.h"
#include "CFrameTime.h"
#include "CGlobalObjects.h"
#include "CInputDevice.h"
#include "CKeyboardDevice.h"
#include "CLinkList.h"
#include "CMouseDevice.h"
#include "CPacket.h"
#include "CSoundDevice.h"
#include "CVideoDevice.h"

CGlobalObjects* globalObjects;

CEventManager* eventManager;

CLinkList* events;

HRESULT				hr;

MSG					msg;

WNDCLASSEX			wcex;

VOID RunFrame();

bool CALLBACK InputEnumCallback(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	CDeviceInstance* deviceInstance = new CDeviceInstance((GUID*)&lpddi->guidInstance, lpddi->tszInstanceName);

	globalObjects->inputDevice->devices->Add(deviceInstance, deviceInstance->instanceName->GetText());

	return DIENUM_CONTINUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);

		return 0;
	}

	case WM_KEYDOWN:
	{
		if (eventManager->consoleVisible)
		{
			if ((wParam == VK_PRIOR) || (wParam == VK_NEXT))
			{
				CPacket* packet = new CPacket(0, 0, CPacket::PT_LOCAL, CPacket::PT_CONSOLEPAGING, (BYTE)wParam, sizeof(BYTE));

				eventManager->SendEvent(packet);

				delete packet;
			}
		}

		return 0;
	}

	case WM_CHAR:
	{
		if (eventManager->consoleVisible)
		{
			CPacket* packet = new CPacket(0, 0, CPacket::PT_LOCAL, CPacket::PT_CONSOLEINPUT, (BYTE)wParam, sizeof(BYTE));

			eventManager->SendEvent(packet);

			delete packet;
		}

		return 0;
	}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

INT APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ INT nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	memset(&wcex, 0x00, sizeof(WNDCLASSEX));

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DXENGINE));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	//wcex.lpszMenuName		= MAKEINTRESOURCE(IDC_DXENGINE);
	wcex.lpszClassName = "dxEngineClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassEx(&wcex);



	globalObjects = new CGlobalObjects(hInstance, "dxEngineClass", "dxEngine", "errorLog.txt", "config.txt");

	if (!globalObjects->window->hWnd)
	{
		delete globalObjects;

		UnregisterClass("dxEngineClass", hInstance);

		return 0;
	}


	globalObjects->inputDevice->dinput->EnumDevices(DI8DEVCLASS_ALL, (LPDIENUMDEVICESCALLBACK)InputEnumCallback, NULL, DIEDFL_ATTACHEDONLY);

	globalObjects->MakeMouseAndKeyboard("Mouse", "Keyboard");



	ShowWindow(globalObjects->window->hWnd, nCmdShow);
	UpdateWindow(globalObjects->window->hWnd);
	SetActiveWindow(globalObjects->window->hWnd);

	ShowCursor(TRUE);

	SetCursorPos(globalObjects->window->middle.x, globalObjects->window->middle.y);



	D3DCOLOR c = D3DCOLOR_XRGB(255, 0, 255);

	globalObjects->textureMgr->MakeTexture("billboard.png", &c);
	globalObjects->textureMgr->MakeTexture("blue.png", &c);
	globalObjects->textureMgr->MakeTexture("bunker.jpg", &c);
	globalObjects->textureMgr->MakeTexture("console.jpg", &c);
	globalObjects->textureMgr->MakeTexture("dirt_01_d.tga", &c);
	globalObjects->textureMgr->MakeTexture("dungeonTileset.png", &c);
	globalObjects->textureMgr->MakeTexture("exit.png", &c);
	globalObjects->textureMgr->MakeTexture("exitO.png", &c);
	globalObjects->textureMgr->MakeTexture("front.png", &c);
	globalObjects->textureMgr->MakeTexture("dgrass_01_d.tga", &c);
	globalObjects->textureMgr->MakeTexture("grass_01_d.tga", &c);
	globalObjects->textureMgr->MakeTexture("grass_03_d.tga", &c);
	globalObjects->textureMgr->MakeTexture("key.png", &c);
	globalObjects->textureMgr->MakeTexture("lightmap.bmp", &c);
	globalObjects->textureMgr->MakeTexture("lock.png", &c);
	globalObjects->textureMgr->MakeTexture("mask1.bmp", &c);
	globalObjects->textureMgr->MakeTexture("mask2.bmp", &c);
	globalObjects->textureMgr->MakeTexture("middle.tga", &c);
	globalObjects->textureMgr->MakeTexture("nameplate.bmp", &c);
	globalObjects->textureMgr->MakeTexture("red.bmp", &c);
	globalObjects->textureMgr->MakeTexture("red.png", &c);
	globalObjects->textureMgr->MakeTexture("rock_01_d.tga", &c);
	globalObjects->textureMgr->MakeTexture("rocks.jpg", &c);
	globalObjects->textureMgr->MakeTexture("seafloor.bmp", &c);
	globalObjects->textureMgr->MakeTexture("stone_giant.png", &c);
	globalObjects->textureMgr->MakeTexture("stoneWall.tga", &c);
	globalObjects->textureMgr->MakeTexture("stoneWallao.tga", &c);
	globalObjects->textureMgr->MakeTexture("stoneWallnm.tga", &c);

	globalObjects->fontDXMgr->MakeDXFont("Consolas", 14, FW_NORMAL);
	globalObjects->fontDXMgr->MakeDXFont("Verdana", 14, FW_BOLD);
	globalObjects->fontDXMgr->MakeDXFont("Tahoma", 14, FW_BOLD);
	globalObjects->fontDXMgr->MakeDXFont("Calibri", 18, FW_NORMAL);

	globalObjects->soundMgr->MakeSound("button2.wav", FALSE);
	globalObjects->soundMgr->MakeSound("chimes.wav", FALSE);
	globalObjects->soundMgr->MakeSound("shotgun.wav", FALSE);

	globalObjects->effectMgr->MakeEffect("blend.fx");
	globalObjects->effectMgr->MakeEffect("brush.fx");
	globalObjects->effectMgr->MakeEffect("line.fx");
	globalObjects->effectMgr->MakeEffect("normalMap.fx");
	globalObjects->effectMgr->MakeEffect("terrain.fx");
	globalObjects->effectMgr->MakeEffect("text.fx");
	globalObjects->effectMgr->MakeEffect("texture.fx");

	CVertex2 v1(1.0F, 1.0F);

	globalObjects->fontMgr->MakeCustomFont("CalibriBold", &v1);
	globalObjects->fontMgr->MakeCustomFont("LucidaConsole", &v1);


	eventManager = new CEventManager(globalObjects, &CornflowerBlue);

	events = new CLinkList();


	memset(&msg, 0x00, sizeof(MSG));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			RunFrame();
		}
	}

	delete events;
	delete eventManager;

	delete globalObjects;

	UnregisterClass("dxEngineClass", hInstance);

	return (INT)msg.wParam;
}

VOID RunFrame()
{
	if (eventManager->isExiting)
	{
		return;
	}

	if (globalObjects->videoDevice == 0)
	{
		return;
	}

	if (globalObjects->videoDevice->device == 0)
	{
		return;
	}

	if (!globalObjects->videoDevice->CheckDevice())
	{
		return;
	}

	globalObjects->frametime->Frame();

	//SetCursorPos(videoDevice->middle.x, videoDevice->middle.y);

	globalObjects->mouse->GetState();

	UINT clientNbr = 0;

	if (eventManager->client)
	{
		clientNbr = eventManager->client->clientNbr;

		if (eventManager->client->connectionState == CClient::CS_NOTCONNECTED)
		{
			clientNbr = 0;
		}
	}


	for (UINT k = 0; k < 4; k++)
	{
		if ((globalObjects->mouse->keyMap[k]->count > 0) && (globalObjects->mouse->keyMap[k]->repeater == CMouseDevice::KR_REPEATER))
		{
			CPacket* packet = new CPacket(clientNbr, 0, globalObjects->mouse->keyMap[k]->packet->audience, globalObjects->mouse->keyMap[k]->packet->type, globalObjects->mouse->keyMap[k]->packet->type, 1);

			events->Add(packet, NULL);
		}
	}


	globalObjects->keyboard->GetState();

	for (UINT k = 0; k < 256; k++)
	{
		if ((globalObjects->keyboard->keyMap[k]->count == 1) && (globalObjects->keyboard->keyMap[k]->repeater == CKeyboardDevice::KR_ONESHOT))
		{
			if (globalObjects->keyboard->keyMap[k]->packet->type == CPacket::PT_CONNECT)
			{
				CPacket* packet = new CPacket(clientNbr, 0, globalObjects->keyboard->keyMap[k]->packet->audience, globalObjects->keyboard->keyMap[k]->packet->type, globalObjects->keyboard->keyMap[k]->packet->type, 1);

				memcpy(packet->data, "127.0.0.1:26105\0", 16);

				packet->length = 15;

				events->Add(packet, NULL);
			}
			else if (globalObjects->keyboard->keyMap[k]->packet)
			{
				CPacket* packet = new CPacket(clientNbr, 0, globalObjects->keyboard->keyMap[k]->packet->audience, globalObjects->keyboard->keyMap[k]->packet->type, globalObjects->keyboard->keyMap[k]->packet->type, 1);

				events->Add(packet, NULL);
			}
		}
		else if ((globalObjects->keyboard->keyMap[k]->count > 0) && (globalObjects->keyboard->keyMap[k]->repeater == CKeyboardDevice::KR_REPEATER))
		{
			if (!eventManager->consoleVisible)
			{
				CPacket* packet = new CPacket(clientNbr, 0, globalObjects->keyboard->keyMap[k]->packet->audience, globalObjects->keyboard->keyMap[k]->packet->type, globalObjects->keyboard->keyMap[k]->packet->type, 1);

				events->Add(packet, NULL);
			}
		}
	}


	CPacket* packet = new CPacket(clientNbr, clientNbr, CPacket::PT_SINGLE, CPacket::PT_FRAME, CPacket::PT_FRAME, 1);

	events->Add(packet, NULL);



	CLinkListNode* lln = events->list;

	while (lln->element)
	{
		eventManager->SendEvent((CPacket*)lln->element);

		lln = lln->next;
	}

	events->Clear();

	// wait here for the servers draw frame command
	//while (!eventManager->timeToDraw)
	//{
	//}

	//CPacket* packet = new CPacket(clientNbr, clientNbr, CPacket::PT_SINGLE, CPacket::PT_FRAME, CPacket::PT_FRAME, 1);

	//eventManager->Frame(packet);

	//delete packet;


	if (eventManager->isRunning)
	{
		Sleep(50);
	}
}