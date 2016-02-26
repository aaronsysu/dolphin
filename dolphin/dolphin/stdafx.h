// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#ifdef WIN32
#include <WinSock2.h>
#include <windows.h>
#endif


// TODO: reference additional headers your program requires here
extern "C"
{
#include "stdint.h"
#define __STDC_CONSTANT_MACROS
#include "inttypes.h"
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
};

#pragma comment(lib, "../third/ffmpeg/lib/avformat.lib")
#pragma comment(lib, "../third/ffmpeg/lib/avcodec.lib")
#pragma comment(lib, "../third/ffmpeg/lib/swscale.lib")
#pragma comment(lib, "../third/ffmpeg/lib/avutil.lib")