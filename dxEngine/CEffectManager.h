#ifndef _CEFFECTMANAGER
#define _CEFFECTMANAGER

#include "standard.h"

#include "CEffect.h"
#include "CErrorLog.h"
#include "CLinkList.h"
#include "CVideoDevice.h"

class CEffectManager
{
public:

	CLinkList* effects;

	CEffectManager();

	CEffectManager(CErrorLog* el, CVideoDevice* d);

	~CEffectManager();

	CEffect* MakeEffect(const CHAR* fn);

	CEffect* GetEffect(const CHAR* fn);

	VOID DeleteEffect(const CHAR* fn);

private:

	HRESULT hr;

	CErrorLog* errorLog;

	CVideoDevice* videoDevice;
	
	CEffect* effect;
};
#endif