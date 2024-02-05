#ifndef _CSOUND3D
#define _CSOUND3D

#include "standard.h"

#include "CGlobalObjects.h"
#include "CString.h"
#include "CVertex.h"
#include "CWavLoader.h"

class CSound3D
{
public:

	CString* filename;

	X3DAUDIO_LISTENER listener;
	
	X3DAUDIO_EMITTER emitter;
	
	X3DAUDIO_CONE emitterCone;

	X3DAUDIO_DSP_SETTINGS dspSettings;

	D3DXVECTOR3 listenerPos;
	
	D3DXVECTOR3 emitterPos;

	FLOAT listenerAngle;

	CSound3D();

	CSound3D(CGlobalObjects* g, const CHAR* fn, BYTE loop, CVertex* p, FLOAT r);

	~CSound3D();

	VOID SetListener(CVertex* p, CVertex* l, CVertex* u);

	VOID StartSound();

	VOID StopSound();

	VOID Shutdown();

private:

	HRESULT hr;

	CGlobalObjects* globalObjects;

	CWavLoader* wavLoader;

	IXAudio2SourceVoice* sourceVoice;

	XAUDIO2_BUFFER buffer;

	FLOAT32* matrix;

	DWORD dwCalcFlags;

	CVertex distance;
	
	INT count;
	
	FLOAT range;
};
#endif