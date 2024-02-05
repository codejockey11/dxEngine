#ifndef _CTEXTURE
#define _CTEXTURE

#include "standard.h"

#include "CErrorLog.h"
#include "CString.h"
#include "CVideoDevice.h"

class CTexture
{
public:

	CString* filename;

	IDirect3DTexture9* image;

	CTexture();

	CTexture(CErrorLog* el, CVideoDevice* d, const CHAR* fn, D3DCOLOR* c);

	~CTexture();

private:

	HRESULT hr;

	CErrorLog* errorLog;
	
	CVideoDevice* videoDevice;
};
#endif