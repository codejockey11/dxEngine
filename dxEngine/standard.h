#define WIN32_LEAN_AND_MEAN
#define DIRECTINPUT_VERSION 0x0800
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <windowsx.h>
#include <comdef.h>
#include <iphlpapi.h>
#include <malloc.h>
#include <memory.h>
#include <mmsystem.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <strsafe.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Ws2_32.lib")

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <dinput.h>
#include <d3dcompiler.h>

#include <DirectXMath.h>

using namespace DirectX;

#pragma comment(lib, "d3d9.lib")

#ifdef _DEBUG
#pragma comment(lib, "d3dx9d.lib")
#else
#pragma comment(lib, "d3dx9.lib")
#endif

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

#pragma comment(lib, "d3dcompiler.lib")


#include <XAudio2.h>
#include <XAudio2fx.h>
#include <X3DAudio.h>

#include <xapofx.h>

#pragma comment(lib, "X3DAudio.lib")
// comment out for XAPOFX
//#pragma comment(lib, "XAudio2.lib")
#pragma comment(lib, "XAPOFX.lib")

#ifndef _GLOBALDEFINES
#define _GLOBALDEFINES

#define PiDiv180 0.0174532925f

__declspec(dllexport) WCHAR* MBSToWide(const CHAR* str);

__declspec(dllexport) CHAR* WideToMBS(const WCHAR* str);

#endif
