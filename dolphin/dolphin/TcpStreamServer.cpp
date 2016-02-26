#include "stdafx.h"
#include "TcpStreamServer.h"


namespace dolphin_media
{
	TcpStreamServer::TcpStreamServer(std::string param)
		: dolphin_base::Consumer(param)
	{
	}


	TcpStreamServer::~TcpStreamServer()
	{
	}

	void TcpStreamServer::Start()
	{
		dolphin_base::Consumer::Start();
	}

	void TcpStreamServer::Stop()
	{
		dolphin_base::Consumer::Stop();
	}

	void TcpStreamServer::ProcessFrame(dolphin_common::Frame::Ptr frame)
	{

	}
}