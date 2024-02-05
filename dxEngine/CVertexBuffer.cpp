#include "CVertexBuffer.h"

CVertexBuffer::CVertexBuffer()
{
	memset(this, 0x00, sizeof(CVertexBuffer));
}

CVertexBuffer::CVertexBuffer(CErrorLog* el, CVideoDevice* d, BYTE t, UINT c, VOID* vertices)
{
	memset(this, 0x00, sizeof(CVertexBuffer));

	errorLog = el;
	videoDevice = d;

	type = t;
	count = c;

	switch (type)
	{
	case CVertex::VT_VERTEXNT:
	{
		hr = videoDevice->device->CreateVertexBuffer(count * sizeof(CVertexNT), D3DUSAGE_DYNAMIC, D3DFVF_VERTEXNT, D3DPOOL::D3DPOOL_DEFAULT, &buffer, NULL);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::CVertexBuffer::CreateVertexBuffer::CVertex::VT_VERTEXNT:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		break;
	}

	case CVertex::VT_VERTEX:
	{
		hr = videoDevice->device->CreateVertexBuffer(count * sizeof(CVertex), D3DUSAGE_DYNAMIC, D3DFVF_VERTEX, D3DPOOL::D3DPOOL_DEFAULT, &buffer, NULL);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::CVertexBuffer::CreateVertexBuffer::CVertex::VT_VERTEX:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		break;
	}

	case CVertex::VT_VERTEXT:
	{
		hr = videoDevice->device->CreateVertexBuffer(count * sizeof(CVertexT), D3DUSAGE_DYNAMIC, D3DFVF_VERTEXT, D3DPOOL::D3DPOOL_DEFAULT, &buffer, NULL);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::CVertexBuffer::CreateVertexBuffer::CVertex::VT_VERTEXT:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		break;
	}

	case CVertex::VT_VERTEX2D:
	{
		hr = videoDevice->device->CreateVertexBuffer(count * sizeof(CVertex2d), D3DUSAGE_DYNAMIC, D3DFVF_VERTEX2D, D3DPOOL::D3DPOOL_DEFAULT, &buffer, NULL);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::CVertexBuffer::CreateVertexBuffer::CVertex::VT_VERTEX2D:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		break;
	}

	case CVertex::VT_VERTEXLINE:
	{
		hr = videoDevice->device->CreateVertexBuffer(count * sizeof(CVertexT), D3DUSAGE_DYNAMIC, D3DFVF_VERTEX, D3DPOOL::D3DPOOL_DEFAULT, &buffer, NULL);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::CVertexBuffer::CreateVertexBuffer::CVertex::VT_VERTEXLINE:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		break;
	}

	default:
	{
		break;
	}
	}

	if (vertices)
	{
		CVertexBuffer::LoadBuffer(vertices);
	}
}

CVertexBuffer::~CVertexBuffer()
{
	if (buffer)
	{
		buffer->Release();
	}
}

VOID CVertexBuffer::LoadBuffer(VOID* vertices)
{
	switch (type)
	{
	case CVertex::VT_VERTEXNT:
	{
		hr = buffer->Lock(0, count * sizeof(CVertexNT), (VOID**)&heap, 0);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::LoadBuffer::CVertex::VT_VERTEXNT::Lock:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		memcpy(heap, vertices, count * sizeof(CVertexNT));

		hr = buffer->Unlock();

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::LoadBuffer::CVertex::VT_VERTEXNT::Unlock:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		break;
	}

	case CVertex::VT_VERTEX:
	{
		hr = buffer->Lock(0, count * sizeof(CVertex), (VOID * *)& heap, 0);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::LoadBuffer::CVertex::VT_VERTEX::Lock:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		memcpy(heap, vertices, count * sizeof(CVertex));

		hr = buffer->Unlock();

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::LoadBuffer::CVertex::VT_VERTEX::Unlock:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		break;
	}

	case CVertex::VT_VERTEXT:
	{
		hr = buffer->Lock(0, count * sizeof(CVertexT), (VOID * *)& heap, 0);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::LoadBuffer::CVertex::VT_VERTEXT::Lock:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		memcpy(heap, vertices, count * sizeof(CVertexT));

		hr = buffer->Unlock();

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::LoadBuffer::CVertex::VT_VERTEXT::Unlock:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		break;
	}

	case CVertex::VT_VERTEX2D:
	{
		hr = buffer->Lock(0, count * sizeof(CVertex2d), (VOID * *)& heap, 0);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::LoadBuffer::CVertex::VT_VERTEX2D::Lock:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		memcpy(heap, vertices, count * sizeof(CVertex2d));

		hr = buffer->Unlock();

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::LoadBuffer::CVertex::VT_VERTEX2D::Unlock:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		break;
	}

	case CVertex::VT_VERTEXLINE:
	{
		hr = buffer->Lock(0, count * sizeof(CVertex), (VOID * *)& heap, 0);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::LoadBuffer::CVertex::VT_VERTEXLINE::Lock:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		memcpy(heap, vertices, count * sizeof(CVertex));

		hr = buffer->Unlock();

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::LoadBuffer::CVertex::VT_VERTEXLINE::Unlock:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		break;
	}

	default:
	{
		break;
	}
	}
}

VOID CVertexBuffer::Draw()
{
	switch (type)
	{
	case CVertex::VT_VERTEXNT:
	{
		hr = videoDevice->device->SetStreamSource(0, buffer, 0, sizeof(CVertexNT));

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::Draw::CVertex::VT_VERTEXNT::SetStreamSource:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		hr = videoDevice->device->SetFVF(D3DFVF_VERTEXNT);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::Draw::CVertex::VT_VERTEXNT::SetFVF:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		hr = videoDevice->device->DrawPrimitive(D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST, 0, count);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::Draw::CVertex::VT_VERTEXNT::DrawPrimitive:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		break;
	}

	case CVertex::VT_VERTEX:
	{
		hr = videoDevice->device->SetStreamSource(0, buffer, 0, sizeof(CVertex));

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::Draw::CVertex::VT_VERTEX::SetStreamSource:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		hr = videoDevice->device->SetFVF(D3DFVF_VERTEX);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::Draw::CVertex::VT_VERTEX::SetFVF:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		hr = videoDevice->device->DrawPrimitive(D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST, 0, count);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::Draw::CVertex::VT_VERTEX::DrawPrimitive:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		break;
	}

	case CVertex::VT_VERTEXT:
	{
		hr = videoDevice->device->SetStreamSource(0, buffer, 0, sizeof(CVertexT));

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::Draw::CVertex::VT_VERTEXT::SetStreamSource:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		hr = videoDevice->device->SetFVF(D3DFVF_VERTEXT);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::Draw::CVertex::VT_VERTEXT::SetFVF:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		hr = videoDevice->device->DrawPrimitive(D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST, 0, count);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::Draw::CVertex::VT_VERTEXT::DrawPrimitive:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		break;
	}

	case CVertex::VT_VERTEX2D:
	{
		hr = videoDevice->device->SetStreamSource(0, buffer, 0, sizeof(CVertex2d));

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::Draw::CVertex::VT_VERTEX2D::SetStreamSource:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		hr = videoDevice->device->SetFVF(D3DFVF_VERTEX2D);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::Draw::CVertex::VT_VERTEX2D::SetFVF:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		hr = videoDevice->device->DrawPrimitive(D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST, 0, count);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::Draw::CVertex::VT_VERTEX2D::DrawPrimitive:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		break;
	}

	case CVertex::VT_VERTEXLINE:
	{
		hr = videoDevice->device->SetStreamSource(0, buffer, 0, sizeof(CVertex));

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::Draw::CVertex::VT_VERTEXLINE::SetStreamSource:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		hr = videoDevice->device->SetFVF(D3DFVF_VERTEX);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::Draw::CVertex::VT_VERTEXLINE::SetFVF:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		hr = videoDevice->device->DrawPrimitive(D3DPRIMITIVETYPE::D3DPT_LINELIST, 0, count / 2);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::Draw::CVertex::VT_VERTEXLINE::DrawPrimitive:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		break;
	}

	default:
	{
		break;
	}
	}
}

VOID CVertexBuffer::DrawIndexed(CIndexBuffer* ib)
{
	switch (type)
	{
	case CVertex::VT_VERTEXNT:
	{
		hr = videoDevice->device->SetStreamSource(0, buffer, 0, sizeof(CVertexNT));

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::DrawIndexed::CVertex::VT_VERTEXNT::SetStreamSource:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		hr = videoDevice->device->SetFVF(D3DFVF_VERTEXNT);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::DrawIndexed::CVertex::VT_VERTEXNT::SetFVF:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		hr = videoDevice->device->SetIndices(ib->buffer);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::DrawIndexed::CVertex::VT_VERTEXNT::SetIndices:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		hr = videoDevice->device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, ib->count, 0, ib->primitiveCount);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::DrawIndexed::CVertex::VT_VERTEXNT::DrawIndexedPrimitive:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		break;
	}

	case CVertex::VT_VERTEX2D:
	{
		hr = videoDevice->device->SetStreamSource(0, buffer, 0, sizeof(CVertex2d));

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::DrawIndexed::CVertex::VT_VERTEX2D::SetStreamSource:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		hr = videoDevice->device->SetFVF(D3DFVF_VERTEX2D);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::DrawIndexed::CVertex::VT_VERTEX2D::SetFVF:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		hr = videoDevice->device->SetIndices(ib->buffer);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::DrawIndexed::CVertex::VT_VERTEX2D::SetIndices:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		hr = videoDevice->device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, ib->count, 0, ib->primitiveCount);

		if (hr < 0)
		{
			errorLog->WriteError("CVertexBuffer::DrawIndexed::CVertex::VT_VERTEX2D::DrawIndexedPrimitive:%s\n", errorLog->GetComErrorMessage(hr));

			return;
		}

		break;
	}

	default:
	{
		break;
	}
	}
}