#pragma once
#include "Consumer.h"
namespace dolphin_media
{
	class TcpStreamServer :
		public dolphin_base::Consumer
	{
	public:
		TcpStreamServer(std::string param);
		~TcpStreamServer();
		void Start();
		void Stop();
		virtual void ProcessFrame(dolphin_common::Frame::Ptr frame);
	};

}