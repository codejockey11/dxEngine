#include "CFrametime.h"

CFrametime::CFrametime()
{
	memset(this, 0x00, sizeof(CFrametime));

	startTime = GetTickCount64();
	currTime = GetTickCount64();
}

CFrametime::~CFrametime()
{
}

VOID CFrametime::Frame()
{
	currTime = GetTickCount64();

	if ((currTime - countTime) > 1000)
	{
		countTime = currTime;

		rframeCount = frameCount;

		rframetime = frametime;

		frameCount = 0;
	}

	frameCount++;

	frametime = (FLOAT)((currTime - startTime) / 1000.0F);

	startTime = currTime;
}