#ifndef _CKEYMAP
#define _CKEYMAP

#include "standard.h"

#include "CPacket.h"

class CKeyMap
{
public:

	INT nbr;

	INT count;

	BYTE repeater;

	CPacket* packet;

	CKeyMap();

	~CKeyMap();
};
#endif