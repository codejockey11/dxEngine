#include "CVideoDevice.h"

CVideoDevice::CVideoDevice()
{
	memset(this, 0x00, sizeof(CVideoDevice));
}

CVideoDevice::CVideoDevice(CErrorLog* el, CWindow* w)
{
	memset(this, 0x00, sizeof(CVideoDevice));

	errorLog = el;
	window = w;

	hr = Direct3DCreate9Ex(D3D_SDK_VERSION, &d3d);

	hr = d3d->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &ident);

	errorLog->WriteError("%s\n", ident.Description);

	hr = d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE::D3DDEVTYPE_HAL, &caps);

	CVideoDevice::SetPresentationParameters(D3DFORMAT::D3DFMT_X8R8G8B8);

	dm.Format = D3DFORMAT::D3DFMT_X8R8G8B8;
	dm.Width = window->width;
	dm.Height = window->height;
	dm.Size = sizeof(D3DDISPLAYMODEEX);
	dm.RefreshRate = D3DPRESENT_RATE_DEFAULT;
	dm.ScanLineOrdering = D3DSCANLINEORDERING_UNKNOWN;

	if (window->windowed)
	{
		hr = d3d->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window->hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, NULL, &device);
	}
	else
	{
		hr = d3d->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window->hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &dm, &device);
	}

	if (hr < 0)
	{
		errorLog->WriteError("CVideoDevice::CVideoDevice::CreateDeviceEx:%s\n", errorLog->GetComErrorMessage(hr));

		if (d3d)
		{
			d3d->Release();
		}

		return;
	}

	CVideoDevice::Resize(window->width, window->height);

	D3DXMatrixPerspectiveFovLH(&projMatrix, 45.0F, (FLOAT)window->width / window->height, 1.0F, 50000.0F);

	D3DXMatrixIdentity(&worldMatrix);

	hr = device->SetTransform(D3DTS_WORLD, &worldMatrix);
	hr = device->SetTransform(D3DTRANSFORMSTATETYPE::D3DTS_PROJECTION, &projMatrix);

	if (window->windowed)
	{
		hr = device->CreateAdditionalSwapChain(&d3dpp, &pSwapChain);

		if (hr < 0)
		{
			errorLog->WriteError("CVideoDevice::CVideoDevice::CreateAdditionalSwapChain:%s\n", errorLog->GetComErrorMessage(hr));

			if (d3d)
			{
				d3d->Release();
			}

			return;
		}

		hr = pSwapChain->GetBackBuffer(0, D3DBACKBUFFER_TYPE::D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);

		if (hr < 0)
		{
			errorLog->WriteError("CVideoDevice::CVideoDevice::GetBackBuffer:windowed:%s\n", errorLog->GetComErrorMessage(hr));

			if (d3d)
			{
				d3d->Release();
			}

			return;
		}
	}
	else
	{
		hr = device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE::D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);

		if (hr < 0)
		{
			errorLog->WriteError("CVideoDevice::CVideoDevice::GetBackBuffer:%s\n", errorLog->GetComErrorMessage(hr));

			if (d3d)
			{
				d3d->Release();
			}

			return;
		}

		hr = device->CreateRenderTarget(window->width, window->height, D3DFORMAT::D3DFMT_X8R8G8B8, D3DMULTISAMPLE_TYPE::D3DMULTISAMPLE_NONE, 0, FALSE, &pBackBuffer, NULL);

		if (hr < 0)
		{
			errorLog->WriteError("CVideoDevice::CVideoDevice::CreateRenderTarget:%s\n", errorLog->GetComErrorMessage(hr));

			if (d3d)
			{
				d3d->Release();
			}

			return;
		}
	}

	CVideoDevice::InitAdapterModes();

	hr = device->SetRenderState(D3DRS_CULLMODE, D3DCULL::D3DCULL_CCW);
	hr = device->SetRenderState(D3DRS_ZENABLE, D3DZBUFFERTYPE::D3DZB_USEW);
	hr = device->SetRenderState(D3DRS_LIGHTING, FALSE);
}

CVideoDevice::~CVideoDevice()
{
	delete dispModes;

	if (pBackBuffer)
	{
		pBackBuffer->Release();
	}

	if (pSwapChain)
	{
		pSwapChain->Release();
	}

	if (device)
	{
		device->Release();
	}

	if (d3d)
	{
		d3d->Release();
	}
}

VOID CVideoDevice::Resize(UINT width, UINT height)
{
	if (device == 0)
	{
		return;
	}

	viewData = { 0, 0, (ULONG)width, (ULONG)height, 0.0F, 1.0F };

	hr = device->SetViewport(&viewData);

	if (hr < 0)
	{
		errorLog->WriteError("CVideoDevice::Resize::SetViewport:%s\n", errorLog->GetComErrorMessage(hr));
	}

	POINT pt = window->GetClientToScreen();

	window->middle.x = pt.x + width / 2;
	window->middle.y = pt.y + height / 2;
}

VOID CVideoDevice::InitAdapterModes()
{
	if (d3d == 0)
	{
		return;
	}

	errorLog->WriteError("CVideoDevice::InitAdapterModes::D3DFORMAT::D3DFMT_X8R8G8B8\n");

	modeCount = d3d->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFORMAT::D3DFMT_X8R8G8B8);

	dispModes = new CLinkList();

	for (UINT i = 0; i < modeCount; i++)
	{
		D3DDISPLAYMODE d;

		d3d->EnumAdapterModes(D3DADAPTER_DEFAULT, D3DFORMAT::D3DFMT_X8R8G8B8, i, &d);

		CDisplayMode* dMode = new CDisplayMode(&d);

		dispModes->Add(dMode, NULL);

		if ((dMode->width != pwidth) || (dMode->height != pheight))
		{
			pwidth = dMode->width;
			pheight = dMode->height;

			errorLog->WriteError("Width:%04d Height:%04d\n", dMode->width, dMode->height);
		}
	}
}

VOID CVideoDevice::ResetDevice(BOOL w)
{
	window->windowed = w;

	CVideoDevice::SetPresentationParameters(D3DFORMAT::D3DFMT_X8R8G8B8);

	hr = device->Reset(&d3dpp);

	if (hr < 0)
	{
		errorLog->WriteError("CVideoDevice::ResetDevice::Reset:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}

	if (window->windowed)
	{
		if (pSwapChain)
		{
			pSwapChain->Release();
		}

		hr = device->CreateAdditionalSwapChain(&d3dpp, &pSwapChain);

		if (hr < 0)
		{
			errorLog->WriteError("CVideoDevice::CVideoDevice::CreateAdditionalSwapChain:%s\n", errorLog->GetComErrorMessage(hr));

			if (d3d)
			{
				d3d->Release();
			}

			return;
		}

		hr = pSwapChain->GetBackBuffer(0, D3DBACKBUFFER_TYPE::D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);

		if (hr < 0)
		{
			errorLog->WriteError("CVideoDevice::CVideoDevice::GetBackBuffer:windowed:%s\n", errorLog->GetComErrorMessage(hr));

			if (d3d)
			{
				d3d->Release();
			}

			return;
		}
	}
}

BOOL CVideoDevice::CheckDevice()
{
	hr = device->CheckDeviceState(window->hWnd);

	if (hr < 0)
	{
		errorLog->WriteError("CVideoDevice::CheckDevice::CheckDeviceState:%s\n", errorLog->GetComErrorMessage(hr));

		return FALSE;
	}

	return TRUE;
}

VOID CVideoDevice::SetPresentationParameters(D3DFORMAT fmt)
{
	memset(&d3dpp, 0x00, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.BackBufferFormat = fmt;
	d3dpp.SwapEffect = D3DSWAPEFFECT::D3DSWAPEFFECT_FLIP;
	d3dpp.hDeviceWindow = window->hWnd;
	d3dpp.Windowed = window->windowed;
	d3dpp.Flags = D3DPRESENTFLAG_DEVICECLIP;
	d3dpp.BackBufferCount = 1;
	//value must be D3DMULTISAMPLE_NONE unless SwapEffect has been set to D3DSWAPEFFECT_DISCARD
	d3dpp.MultiSampleType = D3DMULTISAMPLE_TYPE::D3DMULTISAMPLE_NONE;
	//For windowed mode, the refresh rate must be 0
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;


	hr = d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE::D3DDEVTYPE_HAL, fmt, window->windowed, D3DMULTISAMPLE_TYPE::D3DMULTISAMPLE_NONE, &pQualityLevels);

	if (hr < 0)
	{
		errorLog->WriteError("CVideoDevice::SetPresentationParameters::CheckDeviceMultiSampleType::D3DMULTISAMPLE_TYPE::D3DMULTISAMPLE_NONE:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}

	d3dpp.MultiSampleQuality = pQualityLevels - 1;

	hr = d3d->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE::D3DDEVTYPE_HAL, fmt, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D24S8);

	if (hr < 0)
	{
		errorLog->WriteError("CVideoDevice::SetPresentationParameters::CheckDeviceFormat::D3DFORMAT::D3DFMT_D16:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}
	else
	{
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFORMAT::D3DFMT_D24S8;
	}

	if (!window->windowed)
	{
		d3dpp.BackBufferWidth = window->width;
		d3dpp.BackBufferHeight = window->height;
	}
}

VOID CVideoDevice::ToggleWindowMode()
{
	if (window->windowed)
	{
		window->returnFromFullscreen = 0;

		window->windowed = FALSE;

		CVideoDevice::ResetDevice(window->windowed);

		CVideoDevice::Resize(window->width, window->height);
	}
	else
	{
		window->windowed = TRUE;

		CVideoDevice::ResetDevice(window->windowed);

		SetWindowPos(window->hWnd, NULL, window->posX, window->posY, window->width, window->height, 0);

		CVideoDevice::Resize(window->width, window->height);

		window->returnFromFullscreen = (window->GetWindowRectangle().bottom - window->GetWindowRectangle().top) - (window->GetClientRectangle().bottom - window->GetClientRectangle().top);
	}
}

VOID CVideoDevice::SetupPixelFog(DWORD color, DWORD mode)
{
	FLOAT start = 0.5F;
	FLOAT end = 0.8f;
	FLOAT density = 0.66F;

	device->SetRenderState(D3DRS_FOGENABLE, TRUE);

	device->SetRenderState(D3DRS_FOGCOLOR, color);

	if (mode == D3DFOG_LINEAR)
	{
		device->SetRenderState(D3DRS_FOGTABLEMODE, mode);
		device->SetRenderState(D3DRS_FOGSTART, (DWORD)start);
		device->SetRenderState(D3DRS_FOGEND, (DWORD)end);
	}
	else
	{
		device->SetRenderState(D3DRS_FOGTABLEMODE, mode);
		device->SetRenderState(D3DRS_FOGDENSITY, (DWORD)density);
	}
}