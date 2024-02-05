#ifndef _CSPRITE
#define _CSPRITE

#include "standard.h"

#include "CBoundBox.h"
#include "CGlobalObjects.h"
#include "CIndexBuffer.h"
#include "CTexture.h"
#include "CVertexBuffer.h"

class CSprite
{
public:

	CVertex2 scaleSize;
			 
	CVertex2 position;

	CBoundBox* box;

	CSprite();

	CSprite(CGlobalObjects* g, CTexture* tc, CVertex2* ss, CVertex2* wh, CVertex2* coord, CVertex2* s, CVertex2* p);

	CSprite(CGlobalObjects* g, CTexture* tc, CVertex2* wh, CVertex2* p);

	CSprite(CSprite* s);

	~CSprite();

	VOID UpdatePosition();

	VOID Draw();

private:

	HRESULT hr;

	CGlobalObjects* globalObjects;

	CTexture* texture;

	CVertex2 sheetSize;
	
	CVertex2 cellSize;

	CVertex2d vertices[4];

	CVertexBuffer* vertexBuffer;
	
	CIndexBuffer* indexBuffer;

	DWORD color;

	DWORD index[6];

	FLOAT cl;
	
	FLOAT ct;
	
	FLOAT cr;
	
	FLOAT cb;
};
#endif