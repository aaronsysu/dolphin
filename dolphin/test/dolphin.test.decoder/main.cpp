#include "stdafx.h"

#if defined(_WIN32)
#include <tchar.h>
#elif defined(__linux__)
#include <unistd.h>
#endif

#include "MediaManager.h"

int main(int argc, char** argv)
{
	MediaManager::Init();
	MediaManager::Get()->Start();
	MediaManager::Get()->Run();
	MediaManager::Get()->Stop();
	MediaManager::UnInit();

	return 0;
}