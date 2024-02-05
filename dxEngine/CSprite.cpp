#include "CSprite.h"

CSprite::CSprite()
{
	memset(this, 0x00, sizeof(CSprite));
}

CSprite::CSprite(CGlobalObjects* g, CTexture* tc, CVertex2* ss, CVertex2* wh, CVertex2* coord, CVertex2* s, CVertex2* p)
{
	memset(this, 0x00, sizeof(CSprite));

	globalObjects = g;
	texture = tc;

	sheetSize = *ss;
	cellSize = *wh;
	scaleSize = *s;
	position = *p;

	if (coord->X == 0)
	{
		cl = (1.0F / sheetSize.X) * 0.0F;
		cr = (1.0F / sheetSize.X) * cellSize.X;
	}
	else
	{
		cl = (1.0F / sheetSize.X) * (cellSize.X * coord->X);
		cr = cl + (1.0F / sheetSize.X) * cellSize.X;
	}

	if (coord->Y == 0)
	{
		ct = (1.0F / sheetSize.Y) * 0.0F;
		cb = (1.0F / sheetSize.Y) * cellSize.Y;
	}
	else
	{
		ct = (1.0F / sheetSize.Y) * (cellSize.Y * coord->Y);
		cb = ct + (1.0F / sheetSize.Y) * cellSize.Y;
	}

	vertices[0].X = 0.0F;
	vertices[0].Y = 0.0F;
	vertices[0].Z = 0.0F;
	vertices[0].W = 1.0F;

	vertices[0].U = cl;
	vertices[0].V = ct;

	vertices[1].X = scaleSize.X;
	vertices[1].Y = 0.0F;
	vertices[1].Z = 0.0F;
	vertices[1].W = 1.0F;

	vertices[1].U = cr;
	vertices[1].V = ct;

	vertices[2].X = scaleSize.X;
	vertices[2].Y = scaleSize.Y;
	vertices[2].Z = 0.0F;
	vertices[2].W = 1.0F;

	vertices[2].U = cr;
	vertices[2].V = cb;

	vertices[3].X = 0.0F;
	vertices[3].Y = scaleSize.Y;
	vertices[3].Z = 0.0F;
	vertices[3].W = 1.0F;

	vertices[3].U = cl;
	vertices[3].V = cb;

	vertexBuffer = new CVertexBuffer(globalObjects->errorLog, globalObjects->videoDevice, CVertex::VT_VERTEX2D, 4, (VOID*)vertices);

	index[0] = 0;
	index[1] = 2;
	index[2] = 3;
	index[3] = 0;
	index[4] = 1;
	index[5] = 2;

	indexBuffer = new CIndexBuffer(globalObjects->errorLog, globalObjects->videoDevice, 6, 2, index);

	CVertex v1(vertices[0].X, vertices[0].Y, 0.0F);

	CVertex v2(vertices[2].X, vertices[2].Y, 0.0F);

	box = new CBoundBox(&v1, &v2);

	CSprite::UpdatePosition();
}

CSprite::CSprite(CGlobalObjects* g, CTexture* tc, CVertex2* wh, CVertex2* p)
{
	memset(this, 0x00, sizeof(CSprite));

	globalObjects = g;
	texture = tc;

	scaleSize = *wh;
	position = *p;

	vertices[0].X = 0.0F;
	vertices[0].Y = 0.0F;
	vertices[0].Z = 0.0F;
	vertices[0].W = 1.0F;

	vertices[0].U = 0.0F;
	vertices[0].V = 0.0F;

	vertices[1].X = scaleSize.X;
	vertices[1].Y = 0.0F;
	vertices[1].Z = 0.0F;
	vertices[1].W = 1.0F;

	vertices[1].U = 1.0F;
	vertices[1].V = 0.0F;

	vertices[2].X = scaleSize.X;
	vertices[2].Y = scaleSize.Y;
	vertices[2].Z = 0.0F;
	vertices[2].W = 1.0F;

	vertices[2].U = 1.0F;
	vertices[2].V = 1.0F;

	vertices[3].X = 0.0F;
	vertices[3].Y = scaleSize.Y;
	vertices[3].Z = 0.0F;
	vertices[3].W = 1.0F;

	vertices[3].U = 0.0F;
	vertices[3].V = 1.0F;

	vertexBuffer = new CVertexBuffer(globalObjects->errorLog, globalObjects->videoDevice, CVertex::VT_VERTEX2D, 4, (VOID*)vertices);

	index[0] = 0;
	index[1] = 1;
	index[2] = 2;
	index[3] = 0;
	index[4] = 2;
	index[5] = 3;

	indexBuffer = new CIndexBuffer(globalObjects->errorLog, globalObjects->videoDevice, 6, 2, index);

	CVertex v1(vertices[0].X, vertices[0].Y, 0.0F);

	CVertex v2(vertices[2].X, vertices[2].Y, 0.0F);

	box = new CBoundBox(&v1, &v2);

	CSprite::UpdatePosition();
}

CSprite::CSprite(CSprite* s)
{
	memset(this, 0x00, sizeof(CSprite));

	globalObjects = s->globalObjects;

	texture = s->texture;
	position = s->position;
	sheetSize = s->sheetSize;
	cellSize = s->cellSize;
	scaleSize = s->scaleSize;

	for (UINT x = 0; x < 4; x++)
	{
		vertices[x] = s->vertices[x];
	}

	vertexBuffer = new CVertexBuffer(globalObjects->errorLog, globalObjects->videoDevice, CVertex::VT_VERTEX2D, 4, (VOID*)vertices);

	for (UINT i = 0; i < 6; i++)
	{
		index[i] = s->index[i];
	}

	indexBuffer = new CIndexBuffer(globalObjects->errorLog, globalObjects->videoDevice, 6, 2, index);

	cl = s->cl;
	ct = s->ct;
	cr = s->cr;
	cb = s->cb;

	box = new CBoundBox(s->box);

	CSprite::UpdatePosition();
}

CSprite::~CSprite()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete box;
}

VOID CSprite::UpdatePosition()
{
	vertices[0].X = position.X - (scaleSize.X / 2.0F);
	vertices[1].X = position.X + (scaleSize.X / 2.0F);
	vertices[2].X = position.X + (scaleSize.X / 2.0F);
	vertices[3].X = position.X - (scaleSize.X / 2.0F);

	vertices[0].Y = position.Y - (scaleSize.Y / 2.0F);
	vertices[1].Y = position.Y - (scaleSize.Y / 2.0F);
	vertices[2].Y = position.Y + (scaleSize.Y / 2.0F);
	vertices[3].Y = position.Y + (scaleSize.Y / 2.0F);

	if ((vertices[1].X < 0.0F) || (vertices[3].Y < 0.0F) || (vertices[0].X > globalObjects->window->width) || (vertices[1].Y > globalObjects->window->height))
	{
		return;
	}

	CVertex v1(vertices[0].X, vertices[0].Y, 0.0F);

	CVertex v2(vertices[2].X, vertices[2].Y, 0.0F);

	box->Update(&v1, &v2);

	vertexBuffer->LoadBuffer((VOID*)vertices);
}

VOID CSprite::Draw()
{
	hr = globalObjects->videoDevice->device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	hr = globalObjects->videoDevice->device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	hr = globalObjects->videoDevice->device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	hr = globalObjects->videoDevice->device->SetTexture(0, texture->image);

	vertexBuffer->DrawIndexed(indexBuffer);
}