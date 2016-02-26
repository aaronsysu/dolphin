#pragma once
#include <queue>
#include <mutex>
#include "FramePtr.h"
namespace dolphin_storage
{
	class RecordJob
	{
	public:
		RecordJob();
		~RecordJob();
		int Start();
		int Stop();
		int PushFrame(dolphin_common::Frame::Ptr frame);
	private:
		void RunJob();

		bool _stopFlag;
		std::mutex _incomingFramesMutex;
		std::queue<dolphin_common::Frame::Ptr> _incomingFrames;
	};
}