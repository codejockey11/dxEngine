#ifndef _CSOUNDMANAGER
#define _CSOUNDMANAGER

#include "standard.h"

#include "CErrorLog.h"
#include "CLinkList.h"
#include "CSound.h"
#include "CSoundDevice.h"

class CSoundManager
{
public:

	CSoundManager();

	CSoundManager(CErrorLog* el, CSoundDevice* d);

	~CSoundManager();

	CSound* MakeSound(const CHAR* fn, BYTE loop);

	CSound* GetSound(const CHAR* sn);

private:

	HRESULT hr;

	CErrorLog* errorLog;
	
	CSoundDevice* soundDevice;

	CLinkList* sounds;
	
	CSound* sound;
};
#endif