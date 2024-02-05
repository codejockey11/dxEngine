#include "CLine.h"

CLine::CLine()
{
	memset(this, 0x00, sizeof(CLine));
}

CLine::CLine(CGlobalObjects* g)
{
	memset(this, 0x00, sizeof(CLine));

	globalObjects = g;

	vertexBuffer = new CVertexBuffer(globalObjects->errorLog, globalObjects->videoDevice, CVertex::VT_VERTEXLINE, 2, NULL);
}

CLine::CLine(CLine* l)
{
	globalObjects = l->globalObjects;

	line[0] = l->line[0];
	line[1] = l->line[1];

	vertexBuffer = new CVertexBuffer(globalObjects->errorLog, globalObjects->videoDevice, CVertex::VT_VERTEXLINE, 2, NULL);

	vertexBuffer->LoadBuffer(line);
}

CLine::~CLine()
{
	delete vertexBuffer;
}

VOID CLine::Load(CVertex* f, CVertex* t)
{
	line[0].X = f->X;
	line[0].Y = f->Y;
	line[0].Z = f->Z;

	line[1].X = t->X;
	line[1].Y = t->Y;
	line[1].Z = t->Z;

	vertexBuffer->LoadBuffer(line);
}

VOID CLine::Draw()
{
	vertexBuffer->Draw();
}