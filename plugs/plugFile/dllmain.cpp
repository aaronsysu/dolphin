// dllmain.cpp : Defines the entry point for the DLL application.
#pragma once
#include "stdafx.h"
#include "Plug.h"
#include "MediaSession.h"

#define CHECK_PARAM_AND_RETURN(x)	if (NULL == (x)) return DLPN_PLUG_PARAM_ERROR;

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

INF_API int WINAPI MediaOpen(const char* szParam, long long* mediaHandle)
{
	CHECK_PARAM_AND_RETURN(szParam);
	MediaSession* pNewMediaSession = MediaSession::CreateMediaSession(std::string(szParam));
	mediaHandle = (long long*)pNewMediaSession;
	return 0;
}

INF_API void WINAPI MediaSetCallback(long long mediaHandle, funcRealCallBack pCallback, void* pObject)
{
	MediaSession* pMediaSession = (MediaSession*)&mediaHandle;
	pMediaSession->SetMediaCallback(pCallback, pObject);
}

INF_API int WINAPI MediaStart(long long mediaHandle)
{
	MediaSession* pMediaSession = (MediaSession*)&mediaHandle;
	return pMediaSession->Start();
}

INF_API int WINAPI MediaStop(long long mediaHandle)
{
	MediaSession* pMediaSession = (MediaSession*)&mediaHandle;
	return pMediaSession->Stop();
}

INF_API int WINAPI MediaClose(long long mediaHandle)
{
	MediaSession* pMediaSession = (MediaSession*)&mediaHandle;
	delete pMediaSession;
	pMediaSession = nullptr;
	return 0;
}