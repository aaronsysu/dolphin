#ifndef _PLUG_H
#define _PLUG_H

#if (defined(_WIN32))
#include <WinSock2.h>
#include <windows.h>
#define WINAPI __stdcall
#pragma warning(disable:4068)
#if (defined(_USRDLL))
#define INF_API  extern "C" __declspec(dllexport)
#else
#define INF_API	 extern "C" __declspec(dllimport)
#endif
#endif

typedef void (__stdcall *funcRealCallBack)(unsigned char* pBuffer, int nBuffer, void* pObject);

#endif