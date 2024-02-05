#include "CIndexBuffer.h"

CIndexBuffer::CIndexBuffer()
{
	memset(this, 0x00, sizeof(CIndexBuffer));
}

CIndexBuffer::CIndexBuffer(CErrorLog* el, CVideoDevice* d, UINT c, UINT pc, DWORD* i)
{
	memset(this, 0x00, sizeof(CIndexBuffer));

	errorLog = el;
	videoDevice = d;

	count = c;
	primitiveCount = pc;

	hr = videoDevice->device->CreateIndexBuffer(count * sizeof(DWORD), NULL, D3DFORMAT::D3DFMT_INDEX32, _D3DPOOL::D3DPOOL_DEFAULT, &buffer, NULL);

	if (hr < 0)
	{
		errorLog->WriteError("CIndexBuffer::CIndexBuffer::CreateIndexBuffer:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}

	if (i)
	{
		CIndexBuffer::LoadBuffer((VOID*)i);
	}
}

CIndexBuffer::~CIndexBuffer()
{
	if (buffer)
	{
		buffer->Release();
	}
}

VOID CIndexBuffer::LoadBuffer(VOID* indices)
{
	hr = buffer->Lock(0, count * sizeof(DWORD), (VOID * *)& heap, 0);

	if (hr < 0)
	{
		errorLog->WriteError("CIndexBuffer::LoadBuffer::Lock:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}

	memcpy(heap, indices, count * sizeof(DWORD));

	hr = buffer->Unlock();

	if (hr < 0)
	{
		errorLog->WriteError("CIndexBuffer::LoadBuffer::Unlock:%s\n", errorLog->GetComErrorMessage(hr));

		return;
	}
}