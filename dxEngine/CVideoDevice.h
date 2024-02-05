#ifndef _CVIDEODEVICE
#define _CVIDEODEVICE

#include "standard.h"

#include "CDisplayMode.h"
#include "CErrorLog.h"
#include "CLinkList.h"
#include "CWindow.h"

class CVideoDevice
{
public:

	IDirect3DDevice9Ex* device;

	CWindow* window;

	D3DCAPS9 caps;

	D3DADAPTER_IDENTIFIER9 ident;

	D3DXMATRIX worldMatrix;

	D3DXMATRIX projMatrix;

	CLinkList* dispModes;

	UINT modeCount;

	CVideoDevice();

	CVideoDevice(CErrorLog* el, CWindow* w);

	~CVideoDevice();

	BOOL CheckDevice();

	VOID InitAdapterModes();

	VOID ResetDevice(BOOL w);

	VOID Resize(UINT width, UINT height);

	VOID SetPresentationParameters(D3DFORMAT fmt);

	VOID ToggleWindowMode();

	VOID SetupPixelFog(DWORD Color, DWORD Mode);

private:

	HRESULT hr;

	CErrorLog* errorLog;

	IDirect3D9Ex* d3d;

	IDirect3DSwapChain9* pSwapChain;

	IDirect3DSurface9* pBackBuffer;

	DWORD pQualityLevels;

	D3DPRESENT_PARAMETERS d3dpp;

	D3DDISPLAYMODEEX dm;

	D3DVIEWPORT9 viewData;

	UINT pwidth;

	UINT pheight;
};
#endif