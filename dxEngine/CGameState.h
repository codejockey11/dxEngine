#ifndef _CGAMESTATE
#define _CGAMESTATE

#include "standard.h"

class CGameState
{
public:

	BYTE state;

	CGameState();
	
	~CGameState();

	enum
	{
		GS_TITLESCREEN = 1,
		GS_LOBBY,
		GS_MAINMENU,
		GS_RUNNING,
		GS_CONNECTING,
		GS_DISCONNECTING,
		GS_EXITING,
		
		MAXGAMESTATE = 0xFF
	};
};
#endif