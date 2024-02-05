#ifndef _CVERTEX
#define _CVERTEX

#include "standard.h"

#define D3DFVF_VERTEX		D3DFVF_XYZ
#define D3DFVF_VERTEXRGBA	D3DFVF_XYZ		|	D3DFVF_DIFFUSE
#define D3DFVF_VERTEXT		D3DFVF_XYZ		|	D3DFVF_TEX1
#define D3DFVF_VERTEX2D		D3DFVF_XYZRHW	|	D3DFVF_TEX1
#define D3DFVF_VERTEXNT		D3DFVF_XYZ		|	D3DFVF_NORMAL	| D3DFVF_TEX1

class CVertex
{
public:

	FLOAT	X;
	FLOAT	Y;
	FLOAT	Z;

	CVertex();

	CVertex(FLOAT p1, FLOAT p2, FLOAT p3);

	~CVertex();

	VOID operator += (CONST CVertex& v);

	VOID operator -= (CONST CVertex& v);

	VOID operator *= (FLOAT v);

	VOID operator /= (FLOAT v);

	CVertex operator + (CONST CVertex& v);

	CVertex operator - (CONST CVertex& v);

	CVertex operator * (FLOAT v);

	CVertex operator / (FLOAT v);

	BOOL operator == (CONST CVertex v);

	BOOL operator != (CONST CVertex v);

	FLOAT Length();

	VOID Normalize();

	VOID RadiusNormalize();

	FLOAT Dot(CVertex v);

	CVertex Cross(CVertex v);

	CVertex CalculateNormal(CVertex* a, CVertex* b, CVertex* c);

	CVertex RotateAngleByAxis(const FLOAT AngleInRad, const CVertex ReferenceAxis);

	enum
	{
		VT_VERTEXRGBA = 0,
		VT_VERTEX,
		VT_VERTEXT,
		VT_VERTEX2D,
		VT_VERTEXNT,
		VT_VERTEXLINE,

		VT_MAXVERTEXTYPE = 0xFF
	};
};

class CVertexRGBA : public CVertex
{
public:

	FLOAT	R;
	FLOAT	G;
	FLOAT	B;
	FLOAT	A;

	CVertexRGBA();

	~CVertexRGBA();
};

class CVertexT : public CVertex
{
public:

	FLOAT	U;
	FLOAT	V;

	CVertexT();

	~CVertexT();
};

class CVertexNT : public CVertex
{
public:

	CVertex	n;

	FLOAT	U;
	FLOAT	V;

	CVertexNT();

	~CVertexNT();
};

class CVertex2d
{
public:

	FLOAT		X;
	FLOAT		Y;
	FLOAT		Z;
	FLOAT		W;

	FLOAT		U;
	FLOAT		V;

	CVertex2d();

	~CVertex2d();
};

class CVertex2
{
public:

	FLOAT		X;
	FLOAT		Y;

	CVertex2();

	CVertex2(FLOAT p1, FLOAT p2);

	~CVertex2();

	VOID RadiusNormalize();
};
#endif