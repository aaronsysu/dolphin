#include "stdafx.h"
#include "Consumer.h"
#include "Engine.h"

namespace dolphin_base
{
	Consumer::Consumer(std::string param)
		: _param(param)
		, _stopFlag(false){
	}


	Consumer::~Consumer(){
	}

	void Consumer::PushFrame(dolphin_common::Frame::Ptr frame)
	{
		auto elem =	dolphin_common::QueueElement<dolphin_common::Frame::Ptr>::CreateNewElem();
		elem->SetObj(frame);
		_blockingQueue.EnQueue(elem);
	}

	dolphin_common::Frame::Ptr Consumer::PopFrame(){
		std::shared_ptr<dolphin_common::QueueElement<dolphin_common::Frame::Ptr>> elem =
			_blockingQueue.DeQueueBlocking(10);
		if (elem == nullptr){
			return nullptr;
		}
		dolphin_common::Frame::Ptr frame = (dolphin_common::Frame::Ptr)elem->GetObj();
		return frame;
	}

	void Consumer::RunCircle(){
		if (_stopFlag)
		{
			_stopEvent.notify_all();
			return;
		}

		do 
		{
			dolphin_common::Frame::Ptr frame = PopFrame();
			if (frame == nullptr){
				break;
			}
			ProcessFrame(frame);
		} while (0);

		Engine::Get()->PostTask([this](void* param){
			RunCircle();
		});
	}

	void Consumer::Start()
	{
		RunCircle();
	}

	void Consumer::Stop()
	{
		_stopFlag = true;
		
		std::unique_lock<std::mutex> autolock(_stopMutex);
		_stopEvent.wait(autolock);
	}
}