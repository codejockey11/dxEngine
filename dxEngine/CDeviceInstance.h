#ifndef _CDEVICEINSTANCE
#define _CDEVICEINSTANCE

#include "standard.h"

#include "CString.h"

class CDeviceInstance
{
public:

	CString* instanceName;

	GUID guidInstance;

	CDeviceInstance();

	CDeviceInstance(GUID* g, const CHAR* c);

	~CDeviceInstance();
};
#endif