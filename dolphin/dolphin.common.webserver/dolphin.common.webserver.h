#pragma once

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

DLPN_API int WINAPI DLPN_WebServer_Init();

DLPN_API int WINAPI DLPN_WebServer_Start(const char* param);

DLPN_API int WINAPI DLPN_WebServer_RegisterUri(const char* uri);

DLPN_API int WINAPI DLPN_WebServer_Stop();

DLPN_API int WINAPI DLPN_WebServer_UnInit();