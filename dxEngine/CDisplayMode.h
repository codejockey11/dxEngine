#ifndef _CDISPLAYMODE
#define _CDISPLAYMODE

#include "standard.h"

class CDisplayMode
{
public:
		
	D3DFORMAT format;

	UINT width;
	UINT height;
	UINT refreshRate;

	CDisplayMode();
	
	CDisplayMode(D3DDISPLAYMODE* dm);

	~CDisplayMode();
};
#endif