// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>



// TODO: reference additional headers your program requires here
#include <Winsock2.h>
#include <dolphin.include.error_code.h>

extern "C"
{
#pragma comment(lib, "./../lib/libevent/libevent.lib")
#pragma comment(lib, "./../lib/libevent/libevent_core.lib")
#pragma comment(lib, "./../lib/libevent/libevent_extras.lib")
}