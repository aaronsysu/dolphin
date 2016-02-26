// dolphin.test.webserver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../../dolphin.common.webserver/dolphin.common.webserver.h"

int _tmain(int argc, _TCHAR* argv[])
{
	DLPN_WebServer_Init();
	DLPN_WebServer_Start("httpAddr=127.0.0.1;httpPort=8080;");
	while (true)
	{
		Sleep(10);
	}
	return 0;
}

