#include "stdafx.h"
#include "../Plug.h"
#include "ImageMediaSession.h"

#define CHECK_PARAM_AND_RETURN(x)	if (NULL == (x)) return DLPN_ERROR_PLUG_PARAM;


INF_API int WINAPI MediaOpen(const char* szParam, void** mediaHandle)
{
	ImageMediaSession* pNewMediaSession = new ImageMediaSession;
	pNewMediaSession->Open(szParam);
	*mediaHandle = (void*)pNewMediaSession;
	return 0;
}

INF_API void WINAPI MediaSetCallback(void* mediaHandle, funcRealCallBack pCallback, void* pObject)
{
	ImageMediaSession* pMediaSession = (ImageMediaSession*)mediaHandle;
	pMediaSession->SetMediaCallback(pCallback, pObject);
}

INF_API int WINAPI MediaStart(void* mediaHandle)
{
	ImageMediaSession* pMediaSession = (ImageMediaSession*)mediaHandle;
	pMediaSession->Start();
	return 0;
}

INF_API int WINAPI MediaStop(void* mediaHandle)
{
	ImageMediaSession* pMediaSession = (ImageMediaSession*)mediaHandle;
	pMediaSession->Stop();
	return 0;
}

INF_API int WINAPI MediaClose(void* mediaHandle)
{
	ImageMediaSession* pMediaSession = (ImageMediaSession*)mediaHandle;
	pMediaSession->Close();
	delete pMediaSession;
	pMediaSession = nullptr;
	return 0;
}