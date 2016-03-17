// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "./../Plug.h"
#include "MediaSession.h"

#define CHECK_PARAM_AND_RETURN(x)	if (NULL == (x)) return DLPN_ERROR_PLUG_PARAM;

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

INF_API int WINAPI MediaOpen(const char* szParam, void** mediaHandle)
{
	CHECK_PARAM_AND_RETURN(szParam);
	BasicTaskScheduler* scheduler = BasicTaskScheduler::createNew();
	BasicUsageEnvironment* env = BasicUsageEnvironment::createNew(*scheduler);
	ourRTSPClient* pNewMediaSession = ourRTSPClient::createNew(*env, "RTSP://10.82.13.15/1/h264major", 1, "testRTSP");
	*mediaHandle = (void*)pNewMediaSession;
	return 0;
}

INF_API void WINAPI MediaSetCallback(void* mediaHandle, funcRealCallBack pCallback, void* pObject)
{
	ourRTSPClient* pMediaSession = (ourRTSPClient*)mediaHandle;
	pMediaSession->SetMediaCallback(pCallback, pObject);
}

INF_API int WINAPI MediaStart(void* mediaHandle)
{
	ourRTSPClient* pMediaSession = (ourRTSPClient*)mediaHandle;
	return pMediaSession->Start();
}

INF_API int WINAPI MediaStop(void* mediaHandle)
{
	ourRTSPClient* pMediaSession = (ourRTSPClient*)mediaHandle;
	return pMediaSession->Stop();
}

INF_API int WINAPI MediaClose(void* mediaHandle)
{
	PlugMediaSession* pMediaSession = (PlugMediaSession*)mediaHandle;
	//delete pMediaSession;
	pMediaSession = nullptr;
	return 0;
}