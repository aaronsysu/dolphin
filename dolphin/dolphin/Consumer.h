#pragma once
#include <memory>
#include <mutex>
#include "FramePtr.h"
#include "Queue.h"
namespace dolphin_base
{
	class Consumer
	{
		friend class Producer;
	public:
		Consumer(std::string param);
		~Consumer();
		virtual void Start();
		virtual void Stop();
	protected:
		void PushFrame(dolphin_common::Frame::Ptr frame);
	protected:
		virtual void ProcessFrame(dolphin_common::Frame::Ptr frame) = 0;
		virtual void RunCircle();
		dolphin_common::Frame::Ptr PopFrame();
	protected:
		std::string _param;
		//Ugly designed
		bool _stopFlag;
		std::mutex _stopMutex;
		std::condition_variable _stopEvent;

		dolphin_common::BlockingQueue<dolphin_common::Frame::Ptr> _blockingQueue;
	};

}