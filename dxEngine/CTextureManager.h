#ifndef _CTEXTUREMANAGER
#define _CTEXTUREMANAGER

#include "standard.h"

#include "CErrorLog.h"
#include "CLinkList.h"
#include "CTexture.h"
#include "CVideoDevice.h"

class CTextureManager
{
public:

	CTextureManager();

	CTextureManager(CErrorLog* el, CVideoDevice* d);

	~CTextureManager();

	VOID DeleteTexture(const CHAR* fn);

	CTexture* MakeTexture(const CHAR* fn, D3DCOLOR* c);

	CTexture* GetTexture(const CHAR* tn);

private:

	HRESULT hr;

	CErrorLog* errorLog;
	
	CVideoDevice* videoDevice;
	
	CLinkList* textures;
	
	CTexture* texture;
};
#endif