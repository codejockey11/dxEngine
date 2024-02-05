#ifndef _CEFFECT
#define _CEFFECT

#include "standard.h"

#include "CErrorLog.h"
#include "CString.h"
#include "CVideoDevice.h"

class CEffect
{
public:

	CString* filename;

	ID3DXEffect* effect;

	D3DXHANDLE htechnique;
			   
	D3DXHANDLE hworld;
	D3DXHANDLE hview;
	D3DXHANDLE hproj;
			   
	D3DXHANDLE hwvp;
			   
	D3DXHANDLE hlightAmbient;
	D3DXHANDLE hmaterial;
			   
	D3DXHANDLE hfogStart;
	D3DXHANDLE hfogEnd;
	D3DXHANDLE hfogDensity;
	D3DXHANDLE hminFog;
	D3DXHANDLE hmaxFog;
	D3DXHANDLE hfogColor;
			   
	D3DXHANDLE hlightCount;
			   
	D3DXHANDLE hlightPosition;
	D3DXHANDLE hlightRadius;
	D3DXHANDLE hlightColor;
	D3DXHANDLE hlightLinear;
	D3DXHANDLE hlightQuadratic;
	D3DXHANDLE hlightIntensity;
			   
	D3DXHANDLE htexture00;
	D3DXHANDLE htexture01;
	D3DXHANDLE htexture02;
	D3DXHANDLE htexture03;
	D3DXHANDLE htexture04;
	D3DXHANDLE htexture05;

	UINT iPass;
	UINT cPasses;

	CEffect();

	CEffect(CErrorLog* el, CVideoDevice* d, const CHAR* fn);

	~CEffect();

	VOID SetWVP();

private:

	HRESULT hr;
	
	CErrorLog* errorLog;
	
	CVideoDevice* videoDevice;

	DWORD dwShaderFlags;

	LPD3DXBUFFER compileErrors;
};
#endif