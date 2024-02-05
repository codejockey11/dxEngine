#ifndef _CINDEXBUFFER
#define _CINDEXBUFFER

#include "standard.h"

#include "CErrorLog.h"
#include "CVideoDevice.h"

class CIndexBuffer
{
public:

	IDirect3DIndexBuffer9* buffer;

	INT count;
	
	INT primitiveCount;

	CIndexBuffer();

	CIndexBuffer(CErrorLog* el, CVideoDevice* d, UINT c, UINT pc, DWORD* i);

	~CIndexBuffer();

	VOID LoadBuffer(VOID* indices);

private:

	HRESULT hr;

	CErrorLog* errorLog;
	CVideoDevice* videoDevice;

	VOID* heap;
};
#endif