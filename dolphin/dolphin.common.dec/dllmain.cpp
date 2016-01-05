// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#if (defined(_WIN32))
#include <WinSock2.h>
#include <windows.h>
#define WINAPI __stdcall
#pragma warning(disable:4068)
#if (defined(_USRDLL))
#define DLPN_API  extern "C" __declspec(dllexport)
#else
#define DLPN_API	 extern "C" __declspec(dllimport)
#endif
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

DLPN_API int WINAPI Decode_Open(const char* szParam, long long* decodeHandle)
{
	return 0;
}

DLPN_API int WINAPI Decode_Begin(long long decodeHandle)
{
	return 0;
}

DLPN_API int WINAPI Decode_End(const char* szParam, long long* decodeHandle)
{
	return 0;
}

DLPN_API int WINAPI Decode_Close(long long decodeHandle)
{
	return 0;
}
