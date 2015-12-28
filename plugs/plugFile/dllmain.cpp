// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#pragma once
#if (defined(_WIN32))	//windows
#define WINAPI __stdcall
#pragma warning(disable:4068)
#if (defined(_USRDLL))	//DLL implement
#define INF_API  extern "C" __declspec(dllexport)
#else
#define INF_API	 extern "C" __declspec(dllimport)
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

INF_API int WINAPI MediaOpen(const char* szMediaSession)
{
	return 0;
}

INF_API int WINAPI MediaStart()
{
	return 0;
}

INF_API int WINAPI MediaStop()
{
	return 0;
}

INF_API int WINAPI MediaClose()
{
	return 0;
}