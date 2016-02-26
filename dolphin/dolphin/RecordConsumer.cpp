#include "stdafx.h"
#include "RecordConsumer.h"


namespace dolphin_storage
{
	RecordConsumer::RecordConsumer(std::string param)
		: dolphin_base::Consumer(param)
		, _recordJob(nullptr)
	{
	}


	RecordConsumer::~RecordConsumer()
	{
	}

	void RecordConsumer::Start()
	{
		_recordJob = std::make_shared<RecordJob>();
		_recordJob->Start();

		dolphin_base::Consumer::Start();
	}

	void RecordConsumer::Stop()
	{
		dolphin_base::Consumer::Stop();
		if (_recordJob != nullptr)
		{
			_recordJob->Stop();
		}
	}

	void RecordConsumer::ProcessFrame(dolphin_common::Frame::Ptr frame)
	{
		if (_recordJob != nullptr)
		{
			_recordJob->PushFrame(frame);
		}
	}
}