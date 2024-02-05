#include "CErrorLog.h"

CErrorLog::CErrorLog()
{
	memset(this, 0x00, sizeof(CErrorLog));

	comError = new CComError();
}

CErrorLog::CErrorLog(const CHAR* f)
{
	memset(this, 0x00, sizeof(CErrorLog));

	fopen_s(&fp, f, "w");

	comError = new CComError();
	wsError = new CWinsockError();
}

CErrorLog::~CErrorLog()
{
	delete comError;
	delete wsError;

	if (fp)
	{
		fclose(fp);
	}
}

VOID CErrorLog::WriteError(const CHAR* format, ...)
{
	GetLocalTime(&st);

	sprintf_s(timeText, 24, "%02d:%02d:%02d - ", st.wHour, st.wMinute, st.wSecond);

#ifdef _DEBUG
	OutputDebugStringA(timeText);
#endif

	va_start(argptr, format);

	vsprintf_s(text, 1024, format, argptr);

	va_end(argptr);

#ifdef _DEBUG
	OutputDebugStringA(text);
#endif

	if (fp)
	{
		fwrite(timeText, strlen(timeText), 1, fp);

		fwrite(text, strlen(text), 1, fp);

#ifdef _DEBUG
		fflush(fp);
#endif
	}
}

CHAR* CErrorLog::GetComErrorMessage(HRESULT hr)
{
	return comError->GetComErrorMessage(hr);
}

CWinsockErrorItem* CErrorLog::GetWinsockErrorMessage(UINT e)
{
	return wsError->GetWinsockError(e);
}