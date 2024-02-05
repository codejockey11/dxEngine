#include "CDisplayMode.h"

CDisplayMode::CDisplayMode()
{
	memset(this, 0x00, sizeof(CDisplayMode));
}

CDisplayMode::CDisplayMode(D3DDISPLAYMODE* dm)
{
	memset(this, 0x00, sizeof(CDisplayMode));

	format = dm->Format;
	width = dm->Width;
	height = dm->Height;
	refreshRate = dm->RefreshRate;
}

CDisplayMode::~CDisplayMode()
{
}