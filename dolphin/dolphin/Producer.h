#pragma once
#include <memory>
#include <vector>
#include "FramePtr.h"
#include "Consumer.h"
namespace dolphin_base
{
	typedef std::shared_ptr<Consumer> ConsumerPtr;
	class Producer
	{
	public:
		Producer();
		~Producer();
		void AttachConsumer(ConsumerPtr consumer){
			_consumers.push_back(consumer);
		}
	protected:
		virtual void PushFrameToConsumer(dolphin_common::Frame::Ptr frame);
	private:
		std::mutex _consumerMutex;
		std::vector<ConsumerPtr> _consumers;
	};
}
