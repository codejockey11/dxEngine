#ifndef _CFRAMETIME
#define _CFRAMETIME

#include "standard.h"

class CFrametime
{
public:

	FLOAT frametime;

	INT rframeCount;
	
	FLOAT rframetime;

	ULONGLONG currTime;

	CFrametime();
	
	~CFrametime();

	VOID Frame();

private:

	ULONGLONG startTime;
	
	ULONGLONG countTime;

	INT frameCount;
};
#endif