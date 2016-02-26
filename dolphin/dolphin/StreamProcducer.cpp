#include "stdafx.h"
#include "StreamProcducer.h"
#include "PluginMgr.h"

namespace dolphin_media
{
	StreamProcducer::StreamProcducer(std::string param)
		: dolphin_base::Producer(param)
	{
		_plugTag = param;
		_mediaHandle = 0;
	}

	StreamProcducer::~StreamProcducer()
	{
	}

	void StreamProcducer::Start()
	{
		Producer::Start();

		auto plugin = dolphin_plug::PluginMgr::Get()->GetPlug(_plugTag);
		plugin->MediaOpen("", [this](unsigned char* buffer, unsigned int bufferSize){
			OnMedia(buffer, bufferSize); 
			}, 
			&_mediaHandle);
		plugin->MediaStart(_mediaHandle);
	}

	void StreamProcducer::Stop()
	{
		Producer::Stop();

		auto plugin = dolphin_plug::PluginMgr::Get()->GetPlug(_plugTag);
		plugin->MediaStop(_mediaHandle);
		plugin->MediaClose(_mediaHandle);
	}

	void StreamProcducer::OnMedia(unsigned char* buffer, unsigned int bufferSize)
	{
		auto frame = std::make_shared<dolphin_common::Frame>(buffer, bufferSize);
		PushFrameToConsumer(frame);
	}
}