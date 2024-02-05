#ifndef _CSOUNDDEVICE
#define _CSOUNDDEVICE

#include "standard.h"

#include "CErrorLog.h"

class CSoundDevice
{
public:

	IXAudio2* xAudio2;
	
	X3DAUDIO_HANDLE x3DInstance;

	IXAudio2MasteringVoice* masteringVoice;
	
	XAUDIO2_DEVICE_DETAILS deviceDetails;

	CSoundDevice();

	CSoundDevice(CErrorLog* el);

	~CSoundDevice();

private:

	HRESULT hr;

	CErrorLog* errorLog;

	UINT32 deviceCount;
};
#endif