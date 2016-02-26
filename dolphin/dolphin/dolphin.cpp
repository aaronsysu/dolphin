// dolphin.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PluginMgr.h"
#include "Engine.h"
#include "MediaMgr.h"
#include "DolphinWebService.h"
#include "File.h"

#include "ThreadPool.h"
#include "AsyncFile.h"

#include "Archieve.h"
#include "IOThreadPool.h"
#include "TCPServer.h"

int _tmain(int argc, _TCHAR* argv[])
{
	dolphin_storage::Archieve::Get()->CreateArchive(1);
#ifdef WIN32
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return 0;
	}
#endif
	dolphin_common::IOThreadPool::Get()->Start();

	dolphin_common::TCPServer tcpServer;
	tcpServer.Start("", 8999);

	dolphin_plug::PluginMgr::Get()->LoadPlugs();

	dolphin_base::Engine::Get()->Start();

	dolphin_web::DolphinWebService webService;
	webService.Start();

	Sleep(10);

	for (int i = 0; i < 1000; i++)
	{
		dolphin_base::Engine::Get()->PostDelayTask(1000, [i](void* prama){
			printf("index:%d,got time!%d\r\n", i, std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())); 
		});
		Sleep(1000);
	}

#ifdef WIN32
	while (true)
	{
		Sleep(10);
	}
#endif

	dolphin_base::Engine::Get()->Stop();

	dolphin_plug::PluginMgr::Get()->UnloadPlugs();

#ifdef WIN32
	WSACleanup();
#endif
	return 0;
}

