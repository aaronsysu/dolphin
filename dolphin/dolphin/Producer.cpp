#include "stdafx.h"
#include "Producer.h"

namespace dolphin_base
{
	Producer::Producer(std::string param)
	:_param(param){
	}


	Producer::~Producer(){
	}

	void Producer::PushFrameToConsumer(dolphin_common::Frame::Ptr frame)
	{
		std::unique_lock<std::mutex> autolock(_consumerMutex);
		for (auto &it : _consumers){
			it->PushFrame(frame);
		}
	}

	void Producer::Start()
	{

	}

	void Producer::Stop()
	{
		for (auto &it : _consumers){
			it->Stop();
		}
	}
}