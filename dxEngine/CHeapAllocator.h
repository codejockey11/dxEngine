#ifndef _CHEAPALLOCATOR
#define _CHEAPALLOCATOR

#include "standard.h"

class CHeapAllocator
{
public:

	UINT	count;
	UINT	es;

	CHeapAllocator();

	~CHeapAllocator();
};
#endif