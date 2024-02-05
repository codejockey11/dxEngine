#ifndef _CSOUND
#define _CSOUND

#include "standard.h"

#include "CErrorLog.h"
#include "CSoundDevice.h"
#include "CString.h"
#include "CWavLoader.h"

class CSound
{
public:

	CString* filename;

	BYTE initialized;

	CSound();

	CSound(CErrorLog* el, CSoundDevice* d, const CHAR* fn, BYTE loop);

	~CSound();

	VOID SetEffectParameters();

	VOID ToggleEffect(BYTE e);

	VOID StartSound();

	VOID StopSound();

	VOID Shutdown();

	enum
	{
		SE_ECHO = 0,
		SE_REVERB,
		SE_REVERBXAPO,

		MAXSOUNDEFFECT = 0xFF
	};

private:

	HRESULT hr;

	CErrorLog* errorLog;

	CSoundDevice* soundDevice;

	CWavLoader* wavLoader;

	XAUDIO2_EFFECT_DESCRIPTOR effectDesc[3];

	XAUDIO2_EFFECT_CHAIN effectChain;

	IXAudio2SourceVoice* sourceVoice[16];

	XAUDIO2_BUFFER buffer;

	XAUDIO2_VOICE_STATE vs;

	BYTE isOn[3];

	IUnknown* xapoEffect[3];

	XAUDIO2FX_REVERB_PARAMETERS	reverbParameters;

	FXECHO_PARAMETERS xapoEcho;

	FXREVERB_PARAMETERS xapoReverb;

	VOID SetEffectChain();
};
#endif