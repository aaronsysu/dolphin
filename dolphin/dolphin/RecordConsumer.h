#pragma once
#include "Consumer.h"
#include "RecordJob.h"
namespace dolphin_storage
{
	class RecordConsumer :
		public dolphin_base::Consumer
	{
	public:
		RecordConsumer(std::string param);
		~RecordConsumer();
		virtual void Start();
		virtual void Stop();
		virtual void ProcessFrame(dolphin_common::Frame::Ptr frame);
	private:
		std::shared_ptr<RecordJob> _recordJob;
	};
}
