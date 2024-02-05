#ifndef _CEVENTMANAGER
#define _CEVENTMANAGER

#include "standard.h"

#include "CBillboard.h"
#include "CBrush.h"
#include "CBrushMap.h"
#include "CButton.h"
#include "CCamera.h"
#include "CClient.h"
#include "CCollision.h"
#include "CColor.h"
#include "CConsole.h"
#include "CGlobalObjects.h"
#include "CLine.h"
#include "CLinkList.h"
#include "CMidi.h"
#include "CNamePlate.h"
#include "COrthoLevel.h"
#include "COrthoPlayer.h"
#include "CPacket.h"
#include "CPlayer.h"
#include "CPointLight.h"
#include "CServer.h"
#include "CSound3D.h"
#include "CSprite.h"
#include "CString.h"
#include "CTerrain.h"
#include "CTerrainTile.h"
#include "CTimer.h"

class CEventManager
{
public:

	CClient* client;

	CCamera* currentCamera;

	CTimer* weaponReload;

	BOOL consoleVisible;
	
	BOOL isExiting;
	
	BOOL isRunning;

	SIZE_T pingRate;

	CGlobalObjects* globalObjects;

	CEventManager();

	CEventManager(CGlobalObjects* g, CColor* cc);

	~CEventManager();

	VOID SendEvent(CPacket* p);

	VOID ProcessEvent(CPacket* p);

	VOID Frame(CPacket* p);

private:

	HRESULT hr;

	DWORD rv;

	CBillboard* billboard;

	CBrush* brushMapBrush;

	CBrush* terrainBrush;

	CBrushMap* brushMap;

	CButton* buttonExit;

	CColor* clearColor;

	CConsole* console;

	//CHudImage* middle;

	//CHudImage* spinnyThing;

	CLinkList* orthoPlayers;

	CLinkList* players;

	CMidi* midiSong;

	CNamePlate* namePlate;

	COrthoLevel* orthoLevel;

	COrthoPlayer* orthoPlayer;

	CPlayer* player;

	CPointLight* pointLight;

	CLinkList* projectiles;

	CServer* server;

	CSound3D* sound3D;

	CString* chatText;

	CString* debugText;

	CTerrain* terrain;

	HANDLE hThread;

	UINT receiveThreadId;

	D3DXMATRIX wvp;

	VOID CommandFromConsole();
	VOID ClientConnect(CPacket* p);
	VOID ConsoleInput(CPacket* p);
	VOID Draw2D(CPacket* p);
	VOID Draw3D(CPacket* p);
	VOID DrawDXText(CPacket* p);
	VOID Exit(CPacket* p);
	VOID LoadBrushMap(CPacket* p);
	VOID LoadTerrain(CPacket* p);
	VOID LoadOrthoLevel(CPacket* p);
	VOID PlayerEnter(CPacket* p, FLOAT r);
	VOID PlayerExit(CPacket* p);
	VOID OrthoPlayerEnter(CPacket* p);
	VOID OrthoPlayerExit(CPacket* p);
	VOID SendGlobalChat();
	VOID StartServer();
};
#endif