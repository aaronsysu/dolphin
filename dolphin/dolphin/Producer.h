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
		Producer(std::string param);
		~Producer();
		virtual void Start();
		virtual void Stop();
		void AttachConsumer(ConsumerPtr consumer){
			_consumers.push_back(consumer);
		}
	protected:
		virtual void PushFrameToConsumer(dolphin_common::Frame::Ptr frame);
	protected:
		std::string _param;
	private:
		std::mutex _consumerMutex;
		std::vector<ConsumerPtr> _consumers;
	};
}
