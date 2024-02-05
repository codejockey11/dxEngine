#include "CTexture.h"

CTexture::CTexture()
{
	memset(this, 0x00, sizeof(CTexture));
}

CTexture::CTexture(CErrorLog* el, CVideoDevice* d, const CHAR* fn, D3DCOLOR* c)
{
	memset(this, 0x00, sizeof(CTexture));

	errorLog = el;
	videoDevice = d;

	filename = new CString(fn);

	// This function supports the following file formats: .bmp, .dds, .dib, .hdr, .jpg, .pfm, .png, .ppm, and .tga.
	// Pool must be D3DPOOL::D3DPOOL_DEFAULT
	hr = D3DXCreateTextureFromFileEx(
		videoDevice->device,		//device
		filename->GetText(),		//pSrcFile
		D3DX_DEFAULT,				//Width
		D3DX_DEFAULT,				//Height
		D3DX_DEFAULT,				//MipLevels
		0,							//Usage
		D3DFMT_UNKNOWN,				//Format
		D3DPOOL::D3DPOOL_DEFAULT,	//Pool
		D3DX_FILTER_LINEAR,			//Filter
		D3DX_FILTER_LINEAR,			//MipFilter
		*c,							//ColorKey
		NULL,						//pSrcInfo
		NULL,						//pPalette
		&image						//ppTexture
	);

	if (hr < 0)
	{
		errorLog->WriteError("CTexture::CTexture::D3DXCreateTextureFromFileEx:%s:%s\n", filename->GetText(), errorLog->GetComErrorMessage(hr));

		image = NULL;
	}
}

CTexture::~CTexture()
{
	delete filename;

	if (image)
	{
		image->Release();
	}
}