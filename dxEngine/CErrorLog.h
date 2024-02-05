#ifndef _CERRORLOG
#define _CERRORLOG

#include "standard.h"

#include "CComError.h"
#include "CWinsockError.h"

class CErrorLog
{
public:

	CErrorLog();

	CErrorLog(const CHAR* f);

	~CErrorLog();

	VOID WriteError(const CHAR* format, ...);

	CHAR* GetComErrorMessage(HRESULT hr);

	CWinsockErrorItem* GetWinsockErrorMessage(UINT e);

private:

	CComError* comError;
	
	CWinsockError* wsError;

	FILE* fp;

	CHAR timeText[24];

	CHAR text[1024];

	va_list argptr;

	SYSTEMTIME st;
};
#endif