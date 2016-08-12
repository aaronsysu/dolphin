// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "MediaManager.h"

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

extern "C" void _stdcall AvCode_Init()
{
	MediaManager::Init();
}

extern "C" void _stdcall AvCode_UnInit()
{
	MediaManager::UnInit();
}

extern "C" void _stdcall AvCode_Start()
{
	MediaManager::Get()->Start();
}

extern "C" void _stdcall AVCode_Stop()
{
	MediaManager::Get()->Stop();
}