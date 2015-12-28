#pragma once
#include <memory>
#include <mutex>
#include "FramePtr.h"
#include "Queue.h"
namespace dolphin_base
{
	class Consumer
	{
	public:
		Consumer();
		~Consumer();
		void PushFrame(dolphin_common::Frame::Ptr frame);
	protected:
		virtual void ProcFrame(dolphin_common::Frame::Ptr frame) = 0;
		virtual void RunCircle();
		dolphin_common::Frame::Ptr PopFrame();
	protected:
		dolphin_common::BlockingQueue _blockingQueue;
	};

}