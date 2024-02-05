#include "CSound3D.h"

CSound3D::CSound3D()
{
	memset(this, 0x00, sizeof(CSound3D));
}

CSound3D::CSound3D(CGlobalObjects* g, const CHAR* fn, BYTE loop, CVertex* p, FLOAT r)
{
	memset(this, 0x00, sizeof(CSound3D));

	globalObjects = g;

	range = r;

	filename = new CString(fn);
	wavLoader = new CWavLoader(globalObjects->errorLog, fn);

	hr = globalObjects->soundDevice->xAudio2->CreateSourceVoice(&sourceVoice, &wavLoader->wfx);

	if (hr < 0)
	{
		globalObjects->errorLog->WriteError("CSound3D::CSound3D::CreateSourceVoice:%s\n", globalObjects->errorLog->GetComErrorMessage(hr));

		return;
	}

	buffer.AudioBytes = wavLoader->header.subchunk2Size;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.pAudioData = wavLoader->data;

	if (loop)
	{
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	emitter.Position.x = p->X;
	emitter.Position.y = p->Y;
	emitter.Position.z = p->Z;

	emitter.ChannelCount = 1;
	emitter.CurveDistanceScaler = 1.0F;

	dwCalcFlags = X3DAUDIO_CALCULATE_MATRIX;

	matrix = new FLOAT32[globalObjects->soundDevice->deviceDetails.OutputFormat.Format.nChannels];

	memset(matrix, 0x00, globalObjects->soundDevice->deviceDetails.OutputFormat.Format.nChannels * sizeof(FLOAT32));

	dspSettings.SrcChannelCount = 1;
	dspSettings.DstChannelCount = globalObjects->soundDevice->deviceDetails.OutputFormat.Format.nChannels;
	dspSettings.pMatrixCoefficients = matrix;
}

CSound3D::~CSound3D()
{
	delete filename;
	delete wavLoader;

	if (sourceVoice)
	{
		sourceVoice->Stop(0);
		sourceVoice->FlushSourceBuffers();
		sourceVoice->DestroyVoice();
	}
}

VOID CSound3D::SetListener(CVertex* p, CVertex* l, CVertex* u)
{
	memset(&listener, 0x00, sizeof(X3DAUDIO_LISTENER));

	listener.Position.x = p->X;
	listener.Position.y = p->Y;
	listener.Position.z = p->Z;

	listener.OrientFront.x = l->X;
	listener.OrientFront.y = l->Y;
	listener.OrientFront.z = l->Z;

	listener.OrientTop.x = u->X;
	listener.OrientTop.y = u->Y;
	listener.OrientTop.z = u->Z;

	CVertex lp = CVertex(listener.Position.x, listener.Position.y, listener.Position.z);
	CVertex ep = CVertex(emitter.Position.x, emitter.Position.y, emitter.Position.z);

	distance = lp - ep;

	if (distance.Length() > range)
	{
		count = 0;

		CSound3D::StopSound();
	}
	else if (count == 0)
	{
		count = 1;

		CSound3D::StartSound();
	}

	X3DAudioCalculate(globalObjects->soundDevice->x3DInstance, &listener, &emitter, dwCalcFlags, &dspSettings);

	sourceVoice->SetOutputMatrix(globalObjects->soundDevice->masteringVoice, 1, globalObjects->soundDevice->deviceDetails.OutputFormat.Format.nChannels, dspSettings.pMatrixCoefficients, 0);
}

VOID CSound3D::Shutdown()
{
	sourceVoice->FlushSourceBuffers();
	sourceVoice->DestroyVoice();
}

VOID CSound3D::StartSound()
{
	hr = sourceVoice->SubmitSourceBuffer(&buffer);

	if (hr < 0)
	{
		globalObjects->errorLog->WriteError("CSound3D::StartSound::SubmitSourceBuffer:%s\n", globalObjects->errorLog->GetComErrorMessage(hr));

		return;
	}

	hr = sourceVoice->Start(0);

	if (hr < 0)
	{
		globalObjects->errorLog->WriteError("CSound3D::StartSound::Start:%s\n", globalObjects->errorLog->GetComErrorMessage(hr));

		return;
	}
}

VOID CSound3D::StopSound()
{
	hr = sourceVoice->Stop(0);

	if (hr < 0)
	{
		globalObjects->errorLog->WriteError("CSound3D::StopSound::Stop:%s\n", globalObjects->errorLog->GetComErrorMessage(hr));

		return;
	}
}