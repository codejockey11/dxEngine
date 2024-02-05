#include "CPacket.h"

CPacket::CPacket()
{
	memset(this, 0x00, sizeof(CPacket));
}

CPacket::CPacket(UINT fc, UINT tc, BYTE a, BYTE t)
{
	memset(this, 0x00, sizeof(CPacket));

	fromClient = fc;
	toClient = tc;
	audience = a;
	type = t;
}

CPacket::CPacket(UINT fc, UINT tc, BYTE a, BYTE t, BYTE d, UINT l)
{
	memset(this, 0x00, sizeof(CPacket));

	fromClient = fc;
	toClient = tc;
	audience = a;
	type = t;
	length = l;

	data[0] = d;
}

CPacket::CPacket(UINT fc, UINT tc, BYTE a, BYTE t, BYTE* d, UINT l)
{
	memset(this, 0x00, sizeof(CPacket));

	fromClient = fc;
	toClient = tc;
	audience = a;
	type = t;

	length = l;

	if (length > CPacket::MAXPACKETLEN)
	{
		length = CPacket::MAXPACKETLEN;
	}

	memcpy(data, d, length);
}

CPacket::CPacket(UINT fc, UINT tc, BYTE a, BYTE t, const CHAR* d, UINT l)
{
	memset(this, 0x00, sizeof(CPacket));

	fromClient = fc;
	toClient = tc;
	audience = a;
	type = t;

	length = l;

	if (length > CPacket::MAXPACKETLEN)
	{
		length = CPacket::MAXPACKETLEN;
	}

	if (type == CPacket::PT_CHAT)
	{
		length -= 1;
	}

	memcpy(data, d, length);
}

CPacket::~CPacket()
{
}

VOID CPacket::Clear()
{
	memset(data, 0x00, CPacket::MAXPACKETLEN);
}