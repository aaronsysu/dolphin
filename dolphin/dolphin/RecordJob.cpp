#include "stdafx.h"
#include "RecordJob.h"
#include "Engine.h"
#include "Archieve.h"

namespace dolphin_storage
{
	RecordJob::RecordJob()
		: _stopFlag(false)
	{
	}


	RecordJob::~RecordJob()
	{
	}

	int RecordJob::Start()
	{
		dolphin_base::Engine::Get()->PostTask([this](void* param){
			RunJob();
		});

		return 0;
	}

	int RecordJob::Stop()
	{
		_stopFlag = true;
		return 0;
	}

	int RecordJob::PushFrame(dolphin_common::Frame::Ptr frame)
	{
		std::unique_lock<std::mutex> autolock(_incomingFramesMutex);
		_incomingFrames.push(frame);

		return 0;
	}

	void RecordJob::RunJob()
	{
		int iError = 0;
		Block bk;
		iError = Archieve::Get()->GetBlock(bk);
		if (iError != 0)
		{
			//TODO:无法获取Block，停止存储
			return;
		}

		std::queue<dolphin_common::Frame::Ptr> outcomingFrames;
		{
			std::unique_lock<std::mutex> autolock(_incomingFramesMutex);
			outcomingFrames.swap(_incomingFrames);
		}

		while (!outcomingFrames.empty())
		{
			dolphin_common::Frame::Ptr frame = outcomingFrames.front();
			bk.Write(frame);
			outcomingFrames.pop();
		}

		if (!_stopFlag)
		{
			dolphin_base::Engine::Get()->PostTask([this](void* param){
				RunJob();
			});
		}
	}
}