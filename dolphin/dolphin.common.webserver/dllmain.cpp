// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "dolphin.common.webserver.h"
#include "HttpServer.h"

BOOL APIENTRY DllMain(HMODULE hModule,
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

DLPN_API int WINAPI DLPN_WebServer_Init()
{
#ifdef WIN32
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return DLPN_ERROR_WEBSERVER_SOCKET_INIT;
	}
#endif
	return 0;
}

DLPN_API int WINAPI DLPN_WebServer_Start(const char* param)
{
	HttpServer::Get()->Start(param);
	return 0;
}

DLPN_API int WINAPI DLPN_WebServer_RegisterUri(const char* uri)
{
	return 0;
}

DLPN_API int WINAPI DLPN_WebServer_Stop()
{
	return 0;
}

DLPN_API int WINAPI DLPN_WebServer_UnInit()
{

#ifdef WIN32
	WSACleanup();
#endif
	return 0;
}