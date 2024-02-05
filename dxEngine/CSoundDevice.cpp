#include "CSoundDevice.h"

CSoundDevice::CSoundDevice()
{
	memset(this, 0x00, sizeof(CSoundDevice));
}

CSoundDevice::CSoundDevice(CErrorLog* el)
{
	memset(this, 0x00, sizeof(CSoundDevice));

	errorLog = el;

	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

	if (hr < 0)
	{
		errorLog->WriteError("CSoundDevice::CSoundDevice::CoInitializeEx:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}

	hr = XAudio2Create(&xAudio2, XAUDIO2_DEBUG_ENGINE, XAUDIO2_DEFAULT_PROCESSOR);

	if (hr < 0)
	{
		errorLog->WriteError("CSoundDevice::CSoundDevice::XAudio2Create:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}

	hr = xAudio2->GetDeviceCount(&deviceCount);

	if (hr < 0)
	{
		errorLog->WriteError("CSoundDevice::CSoundDevice::GetDeviceCount:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}

	hr = xAudio2->GetDeviceDetails(0, &deviceDetails);

	if (hr < 0)
	{
		errorLog->WriteError("CSoundDevice::CSoundDevice::GetDeviceDetails:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}

	errorLog->WriteError("%s\n", WideToMBS(deviceDetails.DisplayName));

	hr = xAudio2->CreateMasteringVoice(&masteringVoice);

	if (hr < 0)
	{
		errorLog->WriteError("CSoundDevice::CSoundDevice::CreateMasteringVoice:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}

	X3DAudioInitialize(deviceDetails.OutputFormat.dwChannelMask, X3DAUDIO_SPEED_OF_SOUND, x3DInstance);
}

CSoundDevice::~CSoundDevice()
{
	if (xAudio2)
	{
		xAudio2->Release();
	}

	CoUninitialize();
}