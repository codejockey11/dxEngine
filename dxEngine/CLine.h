#ifndef _CLINE
#define _CLINE

#include "standard.h"

#include "CGlobalObjects.h"
#include "CVertexBuffer.h"

class CLine
{
public:

	CVertex line[2];

	CLine();

	CLine(CGlobalObjects* g);

	CLine(CLine* l);

	~CLine();

	VOID Load(CVertex* f, CVertex* t);

	VOID Draw();

private:

	CGlobalObjects* globalObjects;

	CVertexBuffer* vertexBuffer;
};
#endif