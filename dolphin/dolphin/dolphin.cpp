// dolphin.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PluginMgr.h"
#include "Engine.h"

#include <windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	dolphin_plug::PluginMgr::Get()->LoadPlugs();

	dolphin_base::Engine::Get()->Start();

	Sleep(10);

	for (int i = 0; i < 1000; i ++)
	{
		dolphin_base::Engine::Get()->PostDelayTask([](void* prama){printf("got time!\r\n"); return true; }, 5);

		Sleep(5);
	}

#ifdef WIN32
	while (true)
	{
		Sleep(10);
	}
#endif

	dolphin_base::Engine::Get()->Stop();
	return 0;
}

