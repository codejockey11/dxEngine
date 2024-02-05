#ifndef _CVERTEXBUFFER
#define _CVERTEXBUFFER

#include "standard.h"

#include "CErrorLog.h"
#include "CIndexBuffer.h"
#include "CVertex.h"
#include "CVideoDevice.h"

class CVertexBuffer
{
public:

	CVertexBuffer();

	CVertexBuffer(CErrorLog* el, CVideoDevice* d, BYTE type, UINT count, VOID* vertices);

	~CVertexBuffer();

	VOID LoadBuffer(VOID* vertices);

	VOID Draw();

	VOID DrawIndexed(CIndexBuffer* ib);

private:

	HRESULT hr;

	CErrorLog* errorLog;
	CVideoDevice* videoDevice;

	IDirect3DVertexBuffer9* buffer;

	INT count;

	BYTE type;

	VOID* heap;
};
#endif